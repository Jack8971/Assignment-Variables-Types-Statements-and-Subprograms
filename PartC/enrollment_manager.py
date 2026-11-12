#Enrollment_manager
# Manages student enrollments in a course.

class EnrollmentManger:

  def __init__(self):
      self.students = {}  # Dictionary to store student information
      self.next_student_id = 1001 # Counter for generating unique student IDs
      
  def add_student(self, first_name, last_name, date_of_birth, gender, gpa, current_semester, program, number_of_courses):
    student = {
        "id": self.next_student_id,
        "first_name": first_name,
        "last_name": last_name,
        "date_of_birth": date_of_birth,
        "gender": gender,
        "gpa": gpa,
        "current_semester": current_semester,
        "program": program,
        "number_of_courses": number_of_courses
    }

    #Assign a unique student ID
    student["id"] = self.next_student_id
    #Increment the ID for the next student
    self.next_student_id += 1
    #Store the student in the dictionary using the unique ID as the key
    self.students[student["id"]] = student

    return student["id"]  #Return the assigned ID
    
  def remove_student(self, student):
    student_id = student["id"]
    if student_id in self.students:
        del self.students[student_id]
        return True  #Student removed successfully
    else:
        return False  #Student not found


  def modify_student(self, old_student, new_student):
    pass #for now

  def find_student(self, student):
    pass  #for now

  def exists_duplicate(self, student):
    pass  #for now

  def search_by_name(self, name):
    pass  #for now

  def filter_by_program(self, program):
    pass  #for now

  def sort_by_gpa_descending(self):
    pass  #for now

  def sorted_by_last_name(self):
    pass  #for now

  def student_count(self):
    pass  #for now

  def average_gpa(self):
    pass  #for now

  def count_in_program(self, program):
    pass  #for now

