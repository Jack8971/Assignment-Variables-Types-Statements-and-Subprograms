// [EXTERNAL-MODIFIED] All the code was written by me but I had copilot to auto complete and add proper concise comments to the code
#include "Student.h"

#include <iomanip>
#include <sstream>
#include <utility>

//To change the enum class to string for the program enum class.
std::string toString(Program program) {
    switch (program) {
        case Program::SoftwareDevelopment:   return "Software Development";
        case Program::ComputerScience:       return "Computer Science";
        case Program::InformationSystems:    return "Information Systems";
        case Program::CloudComputing:        return "Cloud Computing";
        case Program::ArtificialIntelligence: return "Artificial Intelligence";
        case Program::NetworkAdministration: return "Network Administration";
    }
    return "Unknown"; // unreachable in case a new program is added to the enum class and not handled here.
}

// Base-class part is built first through the member initializer list.
Student::Student(int studentId,
                 std::string firstName, std::string lastName,
                 Date dateOfBirth, Gender gender,
                 double gpa, int currentSemester,
                 Program program, int numberOfCourses)
    : Person(std::move(firstName), std::move(lastName), dateOfBirth, gender),
      studentId_(studentId),
      gpa_(gpa),
      currentSemester_(currentSemester),
      program_(program),
      numberOfCourses_(numberOfCourses) {}


//All the gettersof the student class to output the private data also no reference here because ints and double are cheap to copy and not worth it
int Student::studentId() const { return studentId_; }
double Student::gpa() const { return gpa_; }
int Student::currentSemester() const { return currentSemester_; }
Program Student::program() const { return program_; }
int Student::numberOfCourses() const { return numberOfCourses_; }

//Settersfor the class excluding the studentId because it should never change once assigned.
void Student::setGpa(double gpa) { gpa_ = gpa; }
void Student::setCurrentSemester(int currentSemester) { currentSemester_ = currentSemester; }
void Student::setProgram(Program program) { program_ = program; }
void Student::setNumberOfCourses(int numberOfCourses) { numberOfCourses_ = numberOfCourses; }

//Used to output all student data in a single string. Used ostringstream to format the output and setprecision to format the gpa to 2 decimal places.
std::string Student::describe() const {
    std::ostringstream out;
    out << "ID: " << studentId_
        << " | " << fullName()                       // inherited from Person
        << " | DOB: " << dateOfBirth().toString()
        << " | Gender: " << toString(gender())
        << " | GPA: " << std::fixed << std::setprecision(2) << gpa_
        << " | Semester: " << currentSemester_
        << " | Program: " << toString(program_)
        << " | Courses: " << numberOfCourses_;
    return out.str();
}