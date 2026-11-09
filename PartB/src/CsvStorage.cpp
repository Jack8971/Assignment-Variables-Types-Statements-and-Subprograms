// [EXTERNAL-MODIFIED] First time working with CSVS in C++ so I used claude for this section
#include "CsvStorage.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <system_error>
#include <utility>
#include <vector>

#include "InputValidation.h"

namespace {
    const std::string kNextIdPrefix = "nextStudentId=";
    const std::string kColumnHeader =
        "id,firstName,lastName,dateOfBirth,gender,gpa,currentSemester,program,numberOfCourses";
    constexpr std::size_t kFieldCount = 9;

    std::vector<std::string> splitFields(const std::string& line) {
        std::vector<std::string> fields;
        std::string current;
        for (char ch : line) {
            if (ch == ',') {
                fields.push_back(current);
                current.clear();
            } else {
                current += ch;
            }
        }
        fields.push_back(current);
        return fields;
    }

    // Finds the enum value whose display text equals 'text'.
    template <typename Option, std::size_t N>
    std::optional<Option> parseOption(const std::string& text,
                                    const std::array<Option, N>& options) {
        for (Option option : options) {
            if (toString(option) == text) {
                return option;
            }
        }
        return std::nullopt;
    }

    // Turns one CSV line into a Student, or nullopt if anything is invalid.
    std::optional<Student> parseStudent(const std::string& line) {
        const std::vector<std::string> fields = splitFields(line);
        if (fields.size() != kFieldCount) {
            return std::nullopt;
        }
        const std::optional<int> id = validation::parseInt(fields[0]);
        const std::optional<Date> dateOfBirth = Date::parse(fields[3]);
        const std::optional<Gender> gender = parseOption(fields[4], kAllGenders);
        const std::optional<double> gpa = validation::parseDouble(fields[5]);
        const std::optional<int> semester = validation::parseInt(fields[6]);
        const std::optional<Program> program = parseOption(fields[7], kAllPrograms);
        const std::optional<int> courses = validation::parseInt(fields[8]);

        if (!id || *id < 1 || !dateOfBirth || !gender || !gpa || !semester ||
            !program || !courses) {
            return std::nullopt;
        }
        if (validation::checkName(fields[1]) || validation::checkName(fields[2]) ||
            validation::checkGpa(*gpa) || validation::checkSemester(*semester) ||
            validation::checkNumberOfCourses(*courses)) {
            return std::nullopt;
        }
        return Student(*id, fields[1], fields[2], *dateOfBirth, *gender, *gpa,
                    *semester, *program, *courses);
    }
} // namespace

CsvStorage::CsvStorage(std::string filePath) : filePath_(std::move(filePath)) {}

const std::string& CsvStorage::filePath() const { return filePath_; }

bool CsvStorage::save(const EnrollmentManager& manager) const {
    // Write to a temporary file first, then swap it in. A crash mid-write
    // then cannot leave a half-written data file behind.
    const std::string tempPath = filePath_ + ".tmp";
    {
        std::ofstream out(tempPath, std::ios::trunc);
        if (!out) {
            return false;
        }
        out << std::setprecision(15); // keeps GPAs like 3.45 exact, no 3.4500001
        out << kNextIdPrefix << manager.nextStudentId() << "\n"
            << kColumnHeader << "\n";
        for (const Student* student : manager.allStudents()) {
            out << student->studentId() << ','
                << student->firstName() << ','
                << student->lastName() << ','
                << student->dateOfBirth().toString() << ','
                << toString(student->gender()) << ','
                << student->gpa() << ','
                << student->currentSemester() << ','
                << toString(student->program()) << ','
                << student->numberOfCourses() << "\n";
        }
        out.close();
        if (out.fail()) {
            return false;
        }
    }
    std::error_code error;
    std::filesystem::rename(tempPath, filePath_, error);
    return !error;
}

LoadResult CsvStorage::load(EnrollmentManager& manager) const {
    LoadResult result;
    std::ifstream in(filePath_);
    if (!in) {
        return result; // first run: nothing saved yet
    }
    result.fileFound = true;

    int savedNextId = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // tolerate Windows line endings
        }
        if (line.empty() || line == kColumnHeader) {
            continue;
        }
        if (line.rfind(kNextIdPrefix, 0) == 0) { // line starts with the prefix
            const std::optional<int> id =
                validation::parseInt(line.substr(kNextIdPrefix.size()));
            if (id) {
                savedNextId = *id;
            } else {
                ++result.skipped;
            }
            continue;
        }
        std::optional<Student> student = parseStudent(line);
        if (student &&
            !manager.existsDuplicate(student->firstName(), student->lastName(),
                                     student->dateOfBirth()) &&
            manager.restoreStudent(std::move(*student))) {
            ++result.loaded;
        } else {
            ++result.skipped;
        }
    }
    manager.setNextStudentId(savedNextId);
    return result;
}