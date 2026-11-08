// [ORIGINAL]
// [EXTERNAL-MODIFIED] most comments were written by Claude.
#include "EnrollmentManager.h"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <utility>

namespace {
// Returns a lowercase copy for case-insensitive comparisons (ASCII only).
std::string toLower(std::string text) {
    // Cast to unsigned char first: passing a negative char to std::tolower is UB.
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

// Sort key: last name, then first name (case-insensitive), then ID so the
// order is always fully determined.
bool lastNameLess(const Student* a, const Student* b) {
    const std::string aLast = toLower(a->lastName());
    const std::string bLast = toLower(b->lastName());
    if (aLast != bLast) return aLast < bLast;
    const std::string aFirst = toLower(a->firstName());
    const std::string bFirst = toLower(b->firstName());
    if (aFirst != bFirst) return aFirst < bFirst;
    return a->studentId() < b->studentId(); // IDs are unique, so no two students tie
}
} // namespace

int EnrollmentManager::addStudent(std::string firstName, std::string lastName,
                                  Date dateOfBirth, Gender gender, double gpa,
                                  int currentSemester, Program program,
                                  int numberOfCourses) {
    // IDs are sequential and never reused, even after a student is removed.
    const int newId = nextStudentId_++;
    // emplace constructs the Student directly inside the map (no extra copy).
    // Names were taken by value, so move them in instead of copying again.
    // Note: no duplicate check here; callers should use existsDuplicate() first.
    students_.emplace(newId, Student(newId, std::move(firstName), std::move(lastName),
                                     dateOfBirth, gender, gpa, currentSemester,
                                     program, numberOfCourses));
    return newId;
}

bool EnrollmentManager::removeStudent(int studentId) {
    // erase returns the number of elements removed (0 or 1).
    // Any pointer previously handed out for this student is now dangling.
    return students_.erase(studentId) > 0;
}

Student* EnrollmentManager::findStudent(int studentId) {
    auto it = students_.find(studentId);
    // nullptr signals "not found"; the pointer does not transfer ownership.
    return it == students_.end() ? nullptr : &it->second;
}

const Student* EnrollmentManager::findStudent(int studentId) const {
    // Read-only overload; same behavior as above.
    auto it = students_.find(studentId);
    return it == students_.end() ? nullptr : &it->second;
}

bool EnrollmentManager::existsDuplicate(const std::string& firstName,
                                        const std::string& lastName,
                                        const Date& dateOfBirth, int ignoreId) const {
    // Lowercase the inputs once, outside the loop.
    const std::string first = toLower(firstName);
    const std::string last = toLower(lastName);
    // Linear scan: a duplicate is same name (case-insensitive) and same birth date.
    return std::any_of(students_.begin(), students_.end(),
        [&](const std::pair<const int, Student>& entry) {
            const Student& s = entry.second;
            // Skip ignoreId so a record being edited isn't flagged as its own duplicate.
            return s.studentId() != ignoreId &&
                   toLower(s.firstName()) == first &&
                   toLower(s.lastName()) == last &&
                   s.dateOfBirth() == dateOfBirth;
        });
}

std::vector<const Student*> EnrollmentManager::allStudents() const {
    std::vector<const Student*> result;
    result.reserve(students_.size()); // size is known; avoid reallocations
    // Return non-owning pointers so records are never copied.
    for (const auto& entry : students_) {
        result.push_back(&entry.second);
    }
    return result;
}

std::vector<const Student*> EnrollmentManager::searchByName(const std::string& text) const {
    const std::string needle = toLower(text);
    std::vector<const Student*> result;
    for (const auto& entry : students_) {
        // Substring match anywhere in the full name; an empty search matches everyone.
        if (toLower(entry.second.fullName()).find(needle) != std::string::npos) {
            result.push_back(&entry.second);
        }
    }
    return result;
}

std::vector<const Student*> EnrollmentManager::filterByProgram(Program program) const {
    std::vector<const Student*> result;
    for (const auto& entry : students_) {
        if (entry.second.program() == program) {
            result.push_back(&entry.second);
        }
    }
    return result;
}

std::vector<const Student*> EnrollmentManager::sortedByGpaDescending() const {
    std::vector<const Student*> result = allStudents();
    // Highest GPA first.
    std::sort(result.begin(), result.end(), [](const Student* a, const Student* b) {
        if (a->gpa() != b->gpa()) return a->gpa() > b->gpa();
        return lastNameLess(a, b); // tie-breaker keeps output deterministic
    });
    return result;
}

std::vector<const Student*> EnrollmentManager::sortedByLastName() const {
    std::vector<const Student*> result = allStudents();
    std::sort(result.begin(), result.end(), lastNameLess);
    return result;
}

std::size_t EnrollmentManager::studentCount() const { return students_.size(); }

double EnrollmentManager::averageGpa() const {
    // Avoid dividing by zero; callers can check studentCount() to tell
    // "no students" apart from a real 0.0 average.
    if (students_.empty()) {
        return 0.0;
    }
    // Unweighted mean: every student counts equally regardless of course load.
    const double total = std::accumulate(
        students_.begin(), students_.end(), 0.0,
        [](double sum, const std::pair<const int, Student>& entry) {
            return sum + entry.second.gpa();
        });
    return total / static_cast<double>(students_.size());
}

std::size_t EnrollmentManager::countInProgram(Program program) const {
    // Counts without building a vector (cheaper than filterByProgram().size()).
    // count_if returns a signed difference_type, so cast to match the return type.
    return static_cast<std::size_t>(std::count_if(
        students_.begin(), students_.end(),
        [program](const std::pair<const int, Student>& entry) {
            return entry.second.program() == program;
        }));
}