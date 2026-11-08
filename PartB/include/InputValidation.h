// [EXTERNAL-MODIFIED] All the code was written by Kunj but I had copilot to auto complete and add proper concise comments to the code
#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <cstddef>
#include <optional>
#include <string>

#include "Date.h"

// Pure helper functions grouped in a named namespace (no object needed). So technincally not a class but a suite of helper functions.
// Every check*() returns std::nullopt when the value is valid, otherwise
// an error message ready to show the user.
namespace validation {

// Limits live in one place so messages and checks can never disagree.
inline constexpr std::size_t kMaxNameLength = 50;
inline constexpr double kMinGpa = 0.0;
inline constexpr double kMaxGpa = 4.0;
inline constexpr int kMinSemester = 1;
inline constexpr int kMaxSemester = 8;
inline constexpr int kMinCourses = 1;
inline constexpr int kMaxCourses = 10;
inline constexpr int kMinAge = 16;
inline constexpr int kMaxAge = 100;

// Text helpers
std::string trim(const std::string& text);
std::optional<int> parseInt(const std::string& text);
std::optional<double> parseDouble(const std::string& text);

// Field checks
std::optional<std::string> checkName(const std::string& name);
std::optional<std::string> checkDateOfBirth(const Date& dateOfBirth, const Date& today);
std::optional<std::string> checkGpa(double gpa);
std::optional<std::string> checkSemester(int semester);
std::optional<std::string> checkNumberOfCourses(int numberOfCourses);

} // namespace validation

#endif // INPUT_VALIDATION_H