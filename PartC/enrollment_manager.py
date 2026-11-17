# [Original] Copilot used for comments
"""
enrollment_manager.py

This file defines the EnrollmentManager class for the SAIT Enrollment Management System.

It contains:
- EnrollmentManager class with methods to manage student enrollment.
- Methods to add, remove, modify, search, count, and average for students.
"""
from student import Student


class EnrollmentManager:

    def __init__(self):
        #Stores all students using student_id as the key and Student object as the value
        self.students = {}
        #Next unique student ID to assign when adding a new student
        self.next_student_id = 1001

    def add_student(self, first_name, last_name, date_of_birth, gender, gpa, current_semester, program, number_of_courses,
    ):
        #Create a new Student object using the next available ID
        student = Student(
            student_id=self.next_student_id,
            first_name=first_name,
            last_name=last_name,
            date_of_birth=date_of_birth,
            gender=gender,
            gpa=gpa,
            current_semester=current_semester,
            program=program,
            number_of_courses=number_of_courses,
        )
        #Store the student in the enrollment system
        self.students[student.student_id] = student 
        #Increment the ID for the next student
        self.next_student_id += 1 
        #Return the assigned student ID
        return student.student_id

    def remove_student(self, student_id):
        #Remove the student if the ID exists 
        if student_id in self.students:
            del self.students[student_id]
            return True
        return False

    def modify_student(self, student_id, new_student):
        #Replace an existing student while keeping the same ID
        if student_id in self.students:
            new_student.student_id = student_id  #Ensure the student ID remains the same
            self.students[student_id] = new_student
            return True
        return False

    def find_student(self, student_id):
        #Return the student associated with the ID
        return self.students.get(student_id)

    def exists_duplicate(self, first_name, last_name, date_of_birth):
        #Check for students with the same name and date of birth
        for student in self.students.values():
            if (
                student.first_name.lower() == first_name.lower()
                and student.last_name.lower() == last_name.lower()
                and student.date_of_birth == date_of_birth
            ):
                return True

        return False

    def search_by_name(self, name):
        #Perform a case-insensitive search first or last name.
        name = name.lower()
        return [
            student
            for student in self.students.values()
            if name in student.full_name().lower()
        ]

    def filter_by_program(self, program):
        #Return all students enrolled in the specified program
        program_name = program.value if hasattr(program, "value") else program
        return [
            student
            for student in self.students.values()
            if student.program.value.lower() == program_name.lower()
        ]

    def sort_by_gpa_descending(self):
        #Return students ordered from highest GPA to lowest
        return sorted(
            self.students.values(), key=lambda student: (-student.gpa, student.last_name.lower(), student.first_name.lower(), student.student_id)
        )

    def sorted_by_last_name(self):
        #Return students sorted by last name
        return sorted(self.students.values(), key=lambda student: (student.last_name.lower(), student.first_name.lower(), student.student_id))

    def student_count(self):
        return len(self.students)

    def average_gpa(self):
        #Avoid division by zero when no students exist
        if not self.students:
            return 0
        total_gpa = sum(student.gpa for student in self.students.values())
        return total_gpa / len(self.students)

    def count_in_program(self, program):
        #Count how many students belong to the specified program
        return len(self.filter_by_program(program))