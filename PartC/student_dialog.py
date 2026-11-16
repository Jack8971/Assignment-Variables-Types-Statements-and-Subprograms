# Cursor was used to help format the file header, clean up comments,
"""
student_dialog.py

This file asks the user for student information and keeps asking until the input is valid.
It is based on the prompt helpers inside PartB ConsoleUI.cpp.

It contains:
- Functions to prompt for name, date of birth, gender, GPA, semester, and program
- Functions for menu choices and yes/no questions
"""
from datetime import date
import input_validation as validation
from person import Gender
from student import Program


def read_line(prompt):
    return input(prompt)


def prompt_menu_choice(prompt, low, high):
    # keep asking until they enter a number between low and high
    while True:
        choice = validation.parse_int(read_line(prompt))
        if choice != None and choice >= low and choice <= high:
            return choice
        print("Error: Invalid choice. Please enter a number from", low, "to", high)


def prompt_yes_no(prompt):
    # only accepts y or n
    while True:
        answer = read_line(prompt).strip()
        if answer == "y" or answer == "Y":
            return True
        if answer == "n" or answer == "N":
            return False
        print("Error: Please answer y or n.")


def prompt_name(prompt):
    while True:
        name = read_line(prompt).strip()
        error = validation.validate_name(name)
        if error == None:
            return name
        print("Error:", error)


def prompt_date_of_birth(prompt):
    # date has to be YYYY-MM-DD
    while True:
        text = read_line(prompt).strip()
        try:
            dob = date.fromisoformat(text)
        except:
            print("Error: Invalid date. Use the format YYYY-MM-DD (e.g. 2005-01-19).")
            continue
        error = validation.validate_date_of_birth(dob)
        if error == None:
            return dob
        print("Error:", error)


def prompt_gender():
    print("Gender:")
    genders = list(Gender)
    i = 1
    for g in genders:
        print(" ", str(i) + ".", g.value)
        i = i + 1
    choice = prompt_menu_choice("Enter choice (1-" + str(len(genders)) + "): ", 1, len(genders))
    return genders[choice - 1]


def prompt_program():
    print("Program:")
    programs = list(Program)
    i = 1
    for p in programs:
        print(" ", str(i) + ".", p.value)
        i = i + 1
    choice = prompt_menu_choice("Enter choice (1-" + str(len(programs)) + "): ", 1, len(programs))
    return programs[choice - 1]


def prompt_gpa():
    # gpa must be a float between 0.0 and 4.0
    while True:
        parsed = validation.parse_double(read_line("GPA from previous institution (0.0 - 4.0): "))
        if parsed == None:
            print("Error: Invalid number. Please enter a decimal such as 3.5.")
            continue
        error = validation.validate_gpa(parsed)
        if error == None:
            return parsed
        print("Error:", error)


def prompt_semester():
    # semester is a whole number 1-8
    while True:
        parsed = validation.parse_int(read_line("Current semester (1 - 8): "))
        if parsed == None:
            print("Error: Invalid number. Please enter a whole number.")
            continue
        error = validation.validate_semester(parsed)
        if error == None:
            return parsed
        print("Error:", error)


def prompt_number_of_courses():
    # number of courses 1-10
    while True:
        parsed = validation.parse_int(read_line("Number of courses (1 - 10): "))
        if parsed == None:
            print("Error: Invalid number. Please enter a whole number.")
            continue
        error = validation.validate_number_of_courses(parsed)
        if error == None:
            return parsed
        print("Error:", error)
