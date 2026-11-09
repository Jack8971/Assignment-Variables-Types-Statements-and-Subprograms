// [ORIGINAL] 
// [EXTERNAL-MODIFIED] most comments were written by Claude.
#ifndef ENROLLMENT_MANAGER_H
#define ENROLLMENT_MANAGER_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "Student.h"

// Business logic layer: owns every student record and knows nothing
// about the console. Records are kept in a std::map keyed by student ID,
// so lookup/insert/erase are O(log n) and iteration is already ordered by ID.
class EnrollmentManager {
public:
    // Creates a student, assigns the next ID and stores it. Returns the new ID.
    int addStudent(std::string firstName, std::string lastName,
                   Date dateOfBirth, Gender gender, double gpa,
                   int currentSemester, Program program, int numberOfCourses);

    // Returns true if a record was removed, false if the ID does not exist.
    bool removeStudent(int studentId);

    // Pointer return: nullptr means "not found". Two overloads so a
    // const manager only hands out const access.
    Student* findStudent(int studentId);
    const Student* findStudent(int studentId) const;

    // True if another student (different ID) has the same name and date of birth.
    // Pass ignoreId when checking an existing student being modified.
    bool existsDuplicate(const std::string& firstName, const std::string& lastName,
                         const Date& dateOfBirth, int ignoreId = -1) const;

    // Queries. Results are non-owning pointers into the map and stay valid
    // only until a student is added or removed.
    std::vector<const Student*> allStudents() const;
    std::vector<const Student*> searchByName(const std::string& text) const;
    std::vector<const Student*> filterByProgram(Program program) const;
    std::vector<const Student*> sortedByGpaDescending() const;
    std::vector<const Student*> sortedByLastName() const;

    // Statistics
    std::size_t studentCount() const;
    double averageGpa() const;
    std::size_t countInProgram(Program program) const;
    
    //Persistence methods
    bool restoreStudent(Student student);
    int nextStudentId() const;
    void setNextStudentId(int nextId);

private:
    std::map<int, Student> students_;
    int nextStudentId_ = 1001;
};

#endif // ENROLLMENT_MANAGER_H