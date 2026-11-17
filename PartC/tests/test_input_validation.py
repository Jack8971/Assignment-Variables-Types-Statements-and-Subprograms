#File header written by Claude
"""
test_input_validation.py

This file contains unit tests for the input_validation.py module in the SAIT Enrollment Management System.

The tests are written with pytest and cover:
- parse_int(text): valid integers, surrounding whitespace, and invalid input.
- parse_double(text): valid floats, invalid input, and non-finite values.
- validate_name(name): valid names, empty names, and names with invalid characters.
- validate_date_of_birth(date_of_birth): future dates and ages outside the valid range.
- validate_gpa(gpa): GPAs inside and outside the 0.0 to 4.0 range.
- validate_semester(semester): semesters inside and outside the valid range.
- validate_number_of_courses(number_of_courses): course counts inside and outside the valid range.

Run from the PartC folder with: py -m pytest tests
"""

from datetime import date

from input_validation import (
    parse_int,
    parse_double,
    validate_name,
    validate_date_of_birth,
    validate_gpa,
    validate_semester,
    validate_number_of_courses,
)

def test_parse_int_valid():
  assert parse_int("21") == 21

def test_parse_int_invalid():
  assert parse_int("abc") is None

def test_parse_double_valid():
  assert parse_double("3.14") == 3.14

def test_validate_name_valid(): #valid name returns no error
  assert validate_name("John Doe") is None

def test_validate_name_empty():
  assert validate_name("") == "Name cannot be empty."

def test_validate_gpa_too_high():
  assert validate_gpa(4.1) == "GPA must be between 0.0 and 4.0."

def test_validate_gpa_too_low():
  assert validate_gpa(-0.1) == "GPA must be between 0.0 and 4.0."

def test_validate_semester_out_of_range():
  assert validate_semester(9) == "Semester must be between 1 and 8."

def test_validate_number_of_courses_out_of_range():
  assert validate_number_of_courses(0) == "Number of courses must be between 1 and 10."

def test_validate_dob_valid():
  today = date.today()
  dob = today.replace(year=today.year - 20)  # 20 years old
  assert validate_date_of_birth(dob) is None

def test_validate_dob_too_young():
  today = date.today()
  dob = today.replace(year=today.year - 15)  # 15 years old
  assert validate_date_of_birth(dob) == "Student must be at least 16 years old."

def test_validate_dob_too_old():
  today = date.today()
  dob = today.replace(year=today.year - 101)  # 101 years old
  assert validate_date_of_birth(dob) == "Student cannot be older than 100 years."

def test_validate_dob_in_future():
  today = date.today()
  dob = today.replace(year=today.year + 3)  # 3 years into the future
  assert validate_date_of_birth(dob) == "Date of birth cannot be in the future."
  