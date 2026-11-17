#[externally-modified] Cursor was used to help format the file header, clean up comments, 
# and structure the console menu logic ported from ConsoleUI.cpp.
#[original] everythign else was done by the team
"""
main_window.py

This file handles the menu and user interface for the SAIT Enrollment Management System.
It is based on PartB ConsoleUI.cpp. 

It contains:
- MainWindow class with the main menu loop
- Methods to add, view, search, modify, remove, sort, and filter students
- Methods to show statistics and save changes to the CSV file
"""

import input_validation as validation  
from student import Program           
import student_dialog as dialog        


class MainWindow:
    def __init__(self, manager, storage=None):
        self.manager = manager   # EnrollmentManager with the student dict
        self.storage = storage   # CsvStorage, or None if --no-persist

    def save_changes(self):
        if self.storage == None:
            return  
        ok = self.storage.save(self.manager) 
        if not ok:
            print("Warning: could not save data to", self.storage.file_path + ".")

    def print_menu(self):
        print()
        print("===== SAIT Enrollment Management System =====")
        print("1. Add student")
        print("2. View all students")
        print("3. Search students by name")
        print("4. Modify student")
        print("5. Remove student")
        print("6. View students sorted")
        print("7. Filter students by program")
        print("8. Show statistics")
        print("0. Exit")

    def print_student_list(self, heading, students):
        print()
        print("---", heading, "(" + str(len(students)) + ") ---")  
        if len(students) == 0:
            print("No students to display.")
            return
        for s in students:
            print(s.describe()) 

    def get_students_sorted_by_id(self):
        result = []
        for key in sorted(self.manager.students.keys()):  # sort ids lowest to highest
            result.append(self.manager.students[key])
        return result

    def is_duplicate_other(self, first_name, last_name, dob, ignore_id):
        for s in self.manager.students.values():
            if s.student_id == ignore_id:
                continue  
            # names compared lowercase so "Mike" == "mike"
            if (s.first_name.lower() == first_name.lower()
                    and s.last_name.lower() == last_name.lower()
                    and s.date_of_birth == dob):
                return True
        return False

    def prompt_existing_student(self):
        student_id = validation.parse_int(dialog.read_line("Enter student ID: "))
        if student_id == None:
            print("Error: Invalid ID. Please enter a number.")
            return None 
        student = self.manager.find_student(student_id)  # None if id not in dict
        if student == None:
            print("Error: No student found with ID", student_id)
        return student

    def run(self):
        try:
            running = True
            while running:  # keep looping until Exit
                self.print_menu()
                choice = dialog.prompt_menu_choice("Enter your choice: ", 0, 8)
                if choice == 1:
                    self.add_student()
                elif choice == 2:
                    self.view_all_students()
                elif choice == 3:
                    self.search_students()
                elif choice == 4:
                    self.modify_student()
                elif choice == 5:
                    self.remove_student()
                elif choice == 6:
                    self.sort_students()
                elif choice == 7:
                    self.filter_by_program()
                elif choice == 8:
                    self.show_statistics()
                elif choice == 0:
                    running = False  # break out of the while loop
            print("Goodbye!")
        except EOFError:
            print()
            print("End of input. Exiting program.")

    def add_student(self):
        print()
        print("--- Add Student ---")
        first_name = dialog.prompt_name("First name: ")
        last_name = dialog.prompt_name("Last name: ")
        dob = dialog.prompt_date_of_birth("Date of birth (YYYY-MM-DD): ")

        # stop early if this person is already enrolled
        if self.manager.exists_duplicate(first_name, last_name, dob):
            print("Error: A student with the same name and date of birth already exists.")
            print("Student was not added.")
            return

        gender = dialog.prompt_gender()
        gpa = dialog.prompt_gpa()
        semester = dialog.prompt_semester()
        program = dialog.prompt_program()
        courses = dialog.prompt_number_of_courses()

        # add_student returns the new id that was assigned
        new_id = self.manager.add_student(
            first_name, last_name, dob, gender, gpa, semester, program, courses
        )
        print("Student added successfully with ID:", new_id)
        self.save_changes()  # write to the CSV file right away

    def view_all_students(self):
        self.print_student_list("All Students", self.get_students_sorted_by_id())

    def search_students(self):
        text = dialog.read_line("Enter name to search for: ").strip()
        if text == "":
            print("Error: Search text cannot be empty.")
            return
        results = self.manager.search_by_name(text)  # partial name match
        self.print_student_list("Search Results", results)

    def modify_student(self):
        print()
        print("--- Modify Student ---")
        student = self.prompt_existing_student()
        if student == None:
            return  # id was invalid or not found

        editing = True
        while editing:  # stay here until they pick Done (0)
            print()
            print("Current record:")
            print(student.describe()) 
            print("Which field do you want to modify?")
            print("  1. First name")
            print("  2. Last name")
            print("  3. Date of birth")
            print("  4. Gender")
            print("  5. GPA")
            print("  6. Current semester")
            print("  7. Program")
            print("  8. Number of courses")
            print("  0. Done")

            choice = dialog.prompt_menu_choice("Enter your choice: ", 0, 8)
            changed = False  
            if choice == 1:
                new_first = dialog.prompt_name("New first name: ")
                if self.is_duplicate_other(new_first, student.last_name, student.date_of_birth, student.student_id):
                    print("Error: A student with the same name and date of birth already exists.")
                else:
                    student.set_first_name(new_first)
                    print("First name updated.")
                    changed = True
            elif choice == 2:
                new_last = dialog.prompt_name("New last name: ")
                if self.is_duplicate_other(student.first_name, new_last, student.date_of_birth, student.student_id):
                    print("Error: A student with the same name and date of birth already exists.")
                else:
                    student.set_last_name(new_last)
                    print("Last name updated.")
                    changed = True
            elif choice == 3:
                new_dob = dialog.prompt_date_of_birth("New date of birth (YYYY-MM-DD): ")
                if self.is_duplicate_other(student.first_name, student.last_name, new_dob, student.student_id):
                    print("Error: A student with the same name and date of birth already exists.")
                else:
                    student.set_date_of_birth(new_dob)
                    print("Date of birth updated.")
                    changed = True
            elif choice == 4:
                student.set_gender(dialog.prompt_gender())
                print("Gender updated.")
                changed = True
            elif choice == 5:
                student.set_gpa(dialog.prompt_gpa())
                print("GPA updated.")
                changed = True
            elif choice == 6:
                student.set_current_semester(dialog.prompt_semester())
                print("Current semester updated.")
                changed = True
            elif choice == 7:
                student.set_program(dialog.prompt_program())
                print("Program updated.")
                changed = True
            elif choice == 8:
                student.set_number_of_courses(dialog.prompt_number_of_courses())
                print("Number of courses updated.")
                changed = True
            elif choice == 0:
                editing = False  # leave the modify loop

            if changed:
                self.save_changes()  # save after each field change

        print("Modification finished.")

    def remove_student(self):
        print()
        print("--- Remove Student ---")
        student = self.prompt_existing_student()
        if student == None:
            return
        print(student.describe())  
        student_id = student.student_id 
        if not dialog.prompt_yes_no("Are you sure you want to remove this student? (y/n): "):
            print("Removal cancelled.")
            return 
        self.manager.remove_student(student_id)
        print("Student", student_id, "removed.")
        self.save_changes()

    def sort_students(self):
        print()
        print("Sort by:")
        print("  1. GPA (highest first)")
        print("  2. Last name (A-Z)")
        choice = dialog.prompt_menu_choice("Enter choice (1-2): ", 1, 2)
        if choice == 1:
            # uses partners sort_by_gpa_descending
            self.print_student_list("Students Sorted by GPA", self.manager.sort_by_gpa_descending())
        else:
            self.print_student_list("Students Sorted by Last Name", self.manager.sorted_by_last_name())

    def filter_by_program(self):
        program = dialog.prompt_program()  # numbered menu of programs
        filtered = self.manager.filter_by_program(program)
        self.print_student_list("Students in " + program.value, filtered)

    def show_statistics(self):
        print()
        print("--- Statistics ---")
        if self.manager.student_count() == 0:
            print("No students enrolled.")
            return
        print("Total students:", self.manager.student_count())
        print("Average GPA:", round(self.manager.average_gpa(), 2)) 
        print("Students per program:")
        for program in Program:  # loop through every program in the enum
            count = self.manager.count_in_program(program)
            print(" ", program.value + ":", count)