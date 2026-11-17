
"""
student.py

This file defines the Student class used by the SAIT Enrollment
Management System.

It contains:
- Program enum with all available SAIT programs.
- Student dataclass inheriting from Person.
- Getter and setter methods for student information.
- A describe method to display student information.
"""

from dataclasses import dataclass
from enum import Enum

from person import Person, Gender


# Defines the available programs in the system.
class Program(str, Enum):
    SOFTWARE_DEVELOPMENT = "Software Development"
    COMPUTER_SCIENCE = "Computer Science"
    INFORMATION_SYSTEMS = "Information Systems"
    CLOUD_COMPUTING = "Cloud Computing"
    ARTIFICIAL_INTELLIGENCE = "Artificial Intelligence"
    NETWORK_ADMINISTRATION = "Network Administration"


# Stores student information and inherits personal details from Person.
@dataclass
class Student(Person):
    student_id: int
    gpa: float
    current_semester: int
    program: Program
    number_of_courses: int

    # Returns the student's ID.
    def get_student_id(self) -> int:
        return self.student_id

    # Returns the student's GPA.
    def get_gpa(self) -> float:
        return self.gpa

    # Returns the student's current semester.
    def get_current_semester(self) -> int:
        return self.current_semester

    # Returns the student's program.
    def get_program(self) -> Program:
        return self.program

    # Returns the number of courses the student takes.
    def get_number_of_courses(self) -> int:
        return self.number_of_courses

    # Updates the student's GPA.
    def set_gpa(self, gpa: float) -> None:
        self.gpa = gpa

    # Updates the student's current semester.
    def set_current_semester(self, current_semester: int) -> None:
        self.current_semester = current_semester

    # Updates the student's program.
    def set_program(self, program: Program) -> None:
        self.program = program

    # Updates the student's number of courses.
    def set_number_of_courses(self, number_of_courses: int) -> None:
        self.number_of_courses = number_of_courses

    # Returns all student information in the same format as C++ describe().
    def describe(self) -> str:
        return (
            f"ID: {self.student_id}"
            f" | {self.full_name()}"
            f" | DOB: {self.date_of_birth.isoformat()}"
            f" | Gender: {self.gender.value}"
            f" | GPA: {self.gpa:.2f}"
            f" | Semester: {self.current_semester}"
            f" | Program: {self.program.value}"
            f" | Courses: {self.number_of_courses}"
        )
