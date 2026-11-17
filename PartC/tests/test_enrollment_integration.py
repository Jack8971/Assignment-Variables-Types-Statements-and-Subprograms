#File header and comments written by Claude
"""
test_enrollment_integration.py

Integration test for the SAIT Enrollment Management System.
Checks that EnrollmentManager, Student, and Person work together
when adding, finding, searching, filtering, and removing students.

"""
from datetime import date
from enrollment_manager import EnrollmentManager
from person import Gender
from student import Program


def test_enrollment_workflow():
    
    manager = EnrollmentManager()

    student_id = manager.add_student(
        "John",
        "Doe",
        date(2000, 1, 1),
        Gender.MALE,  
        1.0,
        1,
        Program.COMPUTER_SCIENCE,
        3,
    )

    # Verify the student was added
    found_student = manager.find_student(student_id)
    assert found_student is not None
    assert found_student.get_first_name() == "John"
    assert found_student.get_last_name() == "Doe"
    assert found_student.get_gpa() == 1.0
    assert found_student.get_program() == Program.COMPUTER_SCIENCE
    assert found_student.get_student_id() == student_id

    # Search for students by name
    search_results = manager.search_by_name("John")
    assert len(search_results) == 1
    assert search_results[0].get_first_name() == "John"

    # Filter students by Program
    filtered_students = manager.filter_by_program(Program.COMPUTER_SCIENCE)
    assert len(filtered_students) == 1
    assert filtered_students[0].get_program() == Program.COMPUTER_SCIENCE

    # Remove the student from the enrollment manager
    manager.remove_student(student_id)

    # Verify the student was removed
    found_student_after_removal = manager.find_student(student_id)
    assert found_student_after_removal is None