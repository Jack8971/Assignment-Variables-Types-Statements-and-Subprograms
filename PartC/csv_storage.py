# [Original] code was created by a team member
# [externally-modified] comments were created by claude code
"""
csv_storage.py

This file saves and loads students from a CSV file for the SAIT Enrollment
Management System. It is the Python version of PartB CsvStorage.cpp and uses
the exact same file format, so the C++ and Python programs can read each
other's files.

File format (one student per line, no quoting needed because validated
names cannot contain commas):
  nextStudentId=1006
  id,firstName,lastName,dateOfBirth,gender,gpa,currentSemester,program,numberOfCourses
  1001,Ethan,Smith,2005-01-19,Male,3.5,2,Software Development,5

It contains:
- LoadResult class to track how many students were loaded or skipped
- Helper functions to convert between CSV lines and Student objects
- CsvStorage class with save() and load() methods
"""

import os
import re
from datetime import date

import input_validation as validation
from person import Gender
from student import Program, Student

NEXT_ID_PREFIX = "nextStudentId="
COLUMN_HEADER = "id,firstName,lastName,dateOfBirth,gender,gpa,currentSemester,program,numberOfCourses"
FIELD_COUNT = 9


# What happened when a file was loaded.
class LoadResult:
    def __init__(self):
        self.file_found = False  # False on a first run (no file yet)
        self.loaded = 0          # records restored
        self.skipped = 0         # lines rejected as invalid or duplicate


# Finds the enum member whose display text equals 'text', or None.
def find_option(text, enum_class):
    for option in enum_class:
        if option.value == text:
            return option
    return None


# Strict YYYY-MM-DD, like Date::parse in C++. Returns None if invalid.
def parse_date(text):
    if not re.fullmatch(r"\d{4}-\d{2}-\d{2}", text):
        return None
    try:
        return date.fromisoformat(text)
    except ValueError:
        return None


# Turns one CSV line into a Student, or None if anything is invalid.
def parse_student(line):
    fields = line.split(",")
    if len(fields) != FIELD_COUNT:
        return None

    student_id = validation.parse_int(fields[0])
    date_of_birth = parse_date(fields[3])
    gender = find_option(fields[4], Gender)
    gpa = validation.parse_double(fields[5])
    semester = validation.parse_int(fields[6])
    program = find_option(fields[7], Program)
    courses = validation.parse_int(fields[8])

    if (student_id is None or student_id < 1 or date_of_birth is None
            or gender is None or gpa is None or semester is None
            or program is None or courses is None):
        return None
    if (validation.validate_name(fields[1]) is not None
            or validation.validate_name(fields[2]) is not None
            or validation.validate_gpa(gpa) is not None
            or validation.validate_semester(semester) is not None
            or validation.validate_number_of_courses(courses) is not None):
        return None

    return Student(
        first_name=fields[1],
        last_name=fields[2],
        date_of_birth=date_of_birth,
        gender=gender,
        student_id=student_id,
        gpa=gpa,
        current_semester=semester,
        program=program,
        number_of_courses=courses,
    )


# Turns a Student into one CSV line (same text the C++ program writes).
def student_to_line(student):
    # '.15g' matches C++ setprecision(15): 3.5 -> "3.5", 3.0 -> "3"
    return ",".join([
        str(student.student_id),
        student.first_name,
        student.last_name,
        student.date_of_birth.isoformat(),
        student.gender.value,
        format(student.gpa, ".15g"),
        str(student.current_semester),
        student.program.value,
        str(student.number_of_courses),
    ])


# Persistence layer: saves and loads the manager's records as a CSV text file.
class CsvStorage:
    def __init__(self, file_path):
        self.file_path = file_path

    # Writes every record. Returns False if the file could not be written.
    def save(self, manager):
        # Write to a temporary file first, then swap it in, so a crash
        # mid-write cannot leave a half-written data file behind.
        temp_path = self.file_path + ".tmp"
        try:
            with open(temp_path, "w", encoding="utf-8", newline="\n") as file:
                file.write(NEXT_ID_PREFIX + str(manager.next_student_id) + "\n")
                file.write(COLUMN_HEADER + "\n")
                for student_id in sorted(manager.students.keys()):
                    file.write(student_to_line(manager.students[student_id]) + "\n")
            os.replace(temp_path, self.file_path)
            return True
        except OSError:
            if os.path.exists(temp_path):
                try:
                    os.remove(temp_path)
                except OSError:
                    pass
            return False

    # Restores records into 'manager' (modified in place). Invalid lines are
    # skipped and counted, never fatal.
    def load(self, manager):
        result = LoadResult()
        try:
            with open(self.file_path, encoding="utf-8", newline="") as file:
                lines = file.read().split("\n")
        except OSError:
            return result  # first run: nothing saved yet
        result.file_found = True

        saved_next_id = 0
        for line in lines:
            line = line.rstrip("\r")  # tolerate Windows line endings
            if line == "" or line == COLUMN_HEADER:
                continue
            if line.startswith(NEXT_ID_PREFIX):
                next_id = validation.parse_int(line[len(NEXT_ID_PREFIX):])
                if next_id is not None:
                    saved_next_id = next_id
                else:
                    result.skipped += 1
                continue

            student = parse_student(line)
            if (student is None
                    or student.student_id in manager.students
                    or manager.exists_duplicate(student.first_name, student.last_name,
                                                student.date_of_birth)):
                result.skipped += 1
                continue

            manager.students[student.student_id] = student
            if student.student_id >= manager.next_student_id:
                manager.next_student_id = student.student_id + 1
            result.loaded += 1

        if saved_next_id > manager.next_student_id:
            manager.next_student_id = saved_next_id
        return result