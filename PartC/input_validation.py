"""
input_validation.py
This file contains functions for validating user input in the SAIT Enrollment Management System.
Functions:
  parse_int(text): Parses a string to an integer, returning None if the input is not a valid integer.
  parse_double(text): Parses a string to a float, returning None if the input is not
- validate_name(name): Validates that the name is a non-empty string containing only alphabetic characters.
- validate_date_of_birth(dob): Validates that the date of birth isn't in the future and a inside the valid age range.
- validate_gpa(gpa): Validates that the GPA is a float between 0.0 and 4.0.
- validate_semester(semester): Validates that the semester is in the correct format and betweem min and max semester. 
- validate_number_of_courses(num_courses): Validates that the number of courses is a positive integer.
"""
from datetime import date

#Validation Constants so messages and checks can never disagree.
MAX_NAME_LENGTH = 50
MIN_GPA = 0.0
MAX_GPA = 4.0
MIN_SEMESTER = 1
MAX_SEMESTER = 8
MIN_COURSES = 1
MAX_COURSES = 10
MIN_AGE = 16
MAX_AGE = 100

#Parsing Functions
def parse_int(text):
  try:
    return int(text.strip())
  #Return None instead of throwing an error
  except ValueError:
    return None

def parse_double(text):
  try:
    return float(text.strip())
  #Return None instead of throwing an error
  except ValueError:
    return None

#Name Validation
def validate_name(name):
  if not name:
    return "Name can not be empty."
  if len(name) > MAX_NAME_LENGTH:
        return f"Name cannot be longer than {MAX_NAME_LENGTH} characters."
  for char in name:
    if not all(char.isalpha() or char in [" ", "-","'"]):
        return "Name can only contain letters, spaces, apostrophes and hyphens. "
  return None
    
    
    
#Date of Birth Validation
def validate_date_of_birth(date_of_birth):

  today = date.today()

  if date_of_birth > today:
    return "Date of birth cannot be a future date."

  age = (today.year - date_of_birth.year - ( today.month, today.day) < (date_of_birth.month, date_of_birth.day))
  if age < MIN_AGE:
    return (f"Student must be at least {MIN_AGE} years old.")
  if age > MAX_AGE:
    return (f"Student cannot be older than {MAX_AGE} years.")
  return None

#Validate GPA
def validate_gpa(gpa):
  if gpa < MIN_GPA or gpa > MAX_GPA:
    return f"GPA must be between {MIN_GPA} and {MAX_GPA}."
  return None

#Semester Validation
def validate_semester(semester):
  if semester < MIN_SEMESTER or semester > MAX_SEMESTER:
    return f"Semester must be between {MIN_SEMESTER} and {MAX_SEMESTER}."
  return None
          
#Course Validation
def validate_number_of_courses(number_of_courses):
  if number_of_courses > MAX_COURSES:
   return f"You can only have up to {MAX_COURSES}."
  if number_of_courses < MIN_COURSES:
    return f"You must have at least {MIN_COURSES}."
  return None

