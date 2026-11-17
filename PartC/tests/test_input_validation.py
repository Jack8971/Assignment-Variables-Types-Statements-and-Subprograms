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
