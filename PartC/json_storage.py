#  # [EXTERNAL-MODIFIED] First time converting CsvStorage to JSON in Python, 
# so I used Cursor to assist with the JSON serialization and file-handling logic
"""
json_storage.py

This file saves and loads students from a JSON file for the SAIT Enrollment Management System.
It is based on PartB CsvStorage.cpp but uses JSON instead of CSV.

It contains:
- LoadResult class to track how many students were loaded or skipped
- Helper functions to convert between Student objects and JSON
- JsonStorage class with save() and load() methods
"""

import json
import os
from datetime import date

import input_validation as validation
from person import Gender
from student import Program, Student


class LoadResult:
    def __init__(self):
        self.file_found = False
        self.loaded = 0
        self.skipped = 0


def find_gender(text):
    for g in Gender:
        if g.value == text:
            return g
    return None


def find_program(text):
    for p in Program:
        if p.value == text:
            return p
    return None


def student_from_json(record):
    # turn one json object into a Student object, or return None if invalid
    try:
        student_id = int(record["id"])
        first_name = str(record["firstName"])
        last_name = str(record["lastName"])
        dob = date.fromisoformat(str(record["dateOfBirth"]))
        gender = find_gender(str(record["gender"]))
        gpa = float(record["previousGpa"])
        semester = int(record["currentSemester"])
        program = find_program(str(record["program"]))
        courses = int(record["numberOfCourses"])
    except:
        return None

    if student_id < 1 or gender is None or program is None:
        return None

    # use partners validation functions
    if validation.validate_name(first_name) != None:
        return None
    if validation.validate_name(last_name) != None:
        return None
    if validation.validate_gpa(gpa) != None:
        return None
    if validation.validate_semester(semester) != None:
        return None
    if validation.validate_number_of_courses(courses) != None:
        return None

    return Student(
        first_name=first_name,
        last_name=last_name,
        date_of_birth=dob,
        gender=gender,
        student_id=student_id,
        gpa=gpa,
        current_semester=semester,
        program=program,
        number_of_courses=courses,
    )


def student_to_json(student):
    # convert student back to the camelCase json keys
    return {
        "id": student.student_id,
        "firstName": student.first_name,
        "lastName": student.last_name,
        "dateOfBirth": student.date_of_birth.isoformat(),
        "gender": student.gender.value,
        "previousGpa": student.gpa,
        "currentSemester": student.current_semester,
        "program": student.program.value,
        "numberOfCourses": student.number_of_courses,
    }


class JsonStorage:
    def __init__(self, file_path):
        self.file_path = file_path

    def save(self, manager):
        # write to temp file first then rename
        temp_path = self.file_path + ".tmp"
        students_list = []
        for sid in sorted(manager.students.keys()):
            students_list.append(student_to_json(manager.students[sid]))

        data = {
            "nextStudentId": manager.next_student_id,
            "students": students_list,
        }

        try:
            f = open(temp_path, "w", encoding="utf-8")
            json.dump(data, f, indent=2, sort_keys=True)
            f.write("\n")
            f.close()
            os.replace(temp_path, self.file_path)
            return True
        except:
            # try clean up temp file
            if os.path.exists(temp_path):
                try:
                    os.remove(temp_path)
                except:
                    pass
            return False

    def load(self, manager):
        result = LoadResult()

        try:
            f = open(self.file_path, encoding="utf-8")
            data = json.load(f)
            f.close()
        except FileNotFoundError:
            return result
        except:
            result.file_found = True
            return result

        result.file_found = True

        saved_next_id = 0
        if "nextStudentId" in data and type(data["nextStudentId"]) == int:
            saved_next_id = data["nextStudentId"]
        else:
            result.skipped = result.skipped + 1

        if "students" not in data:
            return result

        for record in data["students"]:
            student = student_from_json(record)
            if student is None:
                result.skipped = result.skipped + 1
                continue

            # skip if id already there or duplicate name/dob
            if student.student_id in manager.students:
                result.skipped = result.skipped + 1
                continue
            if manager.exists_duplicate(student.first_name, student.last_name, student.date_of_birth):
                result.skipped = result.skipped + 1
                continue

            manager.students[student.student_id] = student
            if student.student_id >= manager.next_student_id:
                manager.next_student_id = student.student_id + 1
            result.loaded = result.loaded + 1

        if saved_next_id > manager.next_student_id:
            manager.next_student_id = saved_next_id

        return result
