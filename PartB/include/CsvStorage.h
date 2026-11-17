// [EXTERNAL-MODIFIED] First time working with CSVS in C++ so I used claude for this section
#ifndef CSV_STORAGE_H
#define CSV_STORAGE_H

#include <cstddef>
#include <string>

#include "EnrollmentManager.h"

// What happened when a file was loaded.
struct LoadResult {
    bool fileFound = false;      // false on a first run (no file yet)
    std::size_t loaded = 0;      // records restored
    std::size_t skipped = 0;     // lines rejected as invalid or duplicate
};

// Persistence layer: saves and loads the manager's records as a CSV text file.
//
// File format (one student per line, no quoting needed because validated
// names cannot contain commas):
//   nextStudentId=1006
//   id,firstName,lastName,dateOfBirth,gender,gpa,currentSemester,program,numberOfCourses
//   1001,Ethan,Smith,2005-01-19,Male,3.5,2,Software Development,5
class CsvStorage {
public:
    explicit CsvStorage(std::string filePath);

    const std::string& filePath() const;

    // Writes every record. Returns false if the file could not be written.
    bool save(const EnrollmentManager& manager) const;

    // Restores records into 'manager' (the manager is passed by reference
    // and modified). Invalid lines are skipped and counted, never fatal.
    LoadResult load(EnrollmentManager& manager) const;

private:
    std::string filePath_;
};

#endif // CSV_STORAGE_H