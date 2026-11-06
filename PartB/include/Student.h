// [EXTERNAL-MODIFIED] All the code was written by me but I had copilot to auto complete and add proper concise comments to the code
#ifndef STUDENT_H
#define STUDENT_H

#include <array>
#include <string>

#include "Person.h"

// Programs a student can be enrolled in and in enum class to avoid any implicit conversions.
enum class Program {
    SoftwareDevelopment,
    ComputerScience,
    InformationSystems,
    CloudComputing,
    ArtificialIntelligence,
    NetworkAdministration
};

// All choices in one fixed-size array, so menus can loop over them.
inline constexpr std::array<Program, 6> kAllPrograms = {
    Program::SoftwareDevelopment, Program::ComputerScience,
    Program::InformationSystems,  Program::CloudComputing,
    Program::ArtificialIntelligence, Program::NetworkAdministration};

// Display text for a Program (e.g. "Software Development").
std::string toString(Program program);

// A student is a Person plus enrollment information ("is-a" inheritance).
class Student : public Person {
public:
    Student(int studentId,
            std::string firstName, std::string lastName,
            Date dateOfBirth, Gender gender,
            double gpa, int currentSemester,
            Program program, int numberOfCourses);

    int studentId() const;
    double gpa() const;
    int currentSemester() const;
    Program program() const;
    int numberOfCourses() const;

    // No setter for studentId: an ID never changes once assigned.
    void setGpa(double gpa);
    void setCurrentSemester(int currentSemester);
    void setProgram(Program program);
    void setNumberOfCourses(int numberOfCourses);

    // Overrides Person::describe(); selected at run time via the base type.
    std::string describe() const override;

private:
    int studentId_;
    double gpa_;
    int currentSemester_;
    Program program_;
    int numberOfCourses_;
};

#endif // STUDENT_H