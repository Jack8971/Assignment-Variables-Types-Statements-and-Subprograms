// [EXTERNAL-MODIFIED] All the code was written by Kunj but I had copilot to auto complete and add proper concise comments to the code and properly arrange it
#include "InputValidation.h"

#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace validation {

    namespace {
    // Builds "<label> must be between <low> and <high>." for any numeric type.
    template <typename Number>// Number can be int, double, etc. 
    std::string rangeMessage(const std::string& label, Number low, Number high) {// This function is used to generate a range error message for numeric values.
        std::ostringstream out;
        out << std::fixed;
        if (std::is_floating_point<Number>::value) {
            out << std::setprecision(1);
        }
        out << label << " must be between " << low << " and " << high << ".";
        return out.str();
    }
    } // namespace

    // Text helpers Used to trim whitespace and parse integers and doubles from strings.
    std::string trim(const std::string& text) {
        const char* whitespace = " \t\n\r\f\v";
        const std::size_t first = text.find_first_not_of(whitespace);
        if (first == std::string::npos) {
            return ""; // empty or all whitespace
        }
        const std::size_t last = text.find_last_not_of(whitespace);
        return text.substr(first, last - first + 1);
    }

    // Parses an integer from a string. Returns std::nullopt if the string is empty, contains non-numeric characters, or is out of range for int.
    std::optional<int> parseInt(const std::string& text) {
        const std::string cleaned = trim(text);
        if (cleaned.empty()) {
            return std::nullopt;
        }
        try {
            std::size_t consumed = 0;
            const int value = std::stoi(cleaned, &consumed);// std::stoi throws if the string is not a valid integer or is out of range for int.
            if (consumed != cleaned.size()) {
                return std::nullopt; // trailing junk such as "5abc" or "3.5"
            }
            return value;
        } catch (const std::invalid_argument&) {
            return std::nullopt;
        } catch (const std::out_of_range&) {
            return std::nullopt;
        }
    }

    // Parses a double from a string. Returns std::nullopt if the string is empty, contains non-numeric characters, or is out of range for double.
    std::optional<double> parseDouble(const std::string& text) {
        const std::string cleaned = trim(text);
        if (cleaned.empty()) {
            return std::nullopt;
        }
        try {
            std::size_t consumed = 0;
            const double value = std::stod(cleaned, &consumed);
            if (consumed != cleaned.size() || !std::isfinite(value)) {
                return std::nullopt; // rejects "3.5x", "nan", "inf"
            }
            return value;
        } catch (const std::invalid_argument&) {
            return std::nullopt;
        } catch (const std::out_of_range&) {
            return std::nullopt;
        }
    }
    
    // Field checks: Each function checks a specific field and returns an error message if invalid, or std::nullopt if valid.
    std::optional<std::string> checkName(const std::string& name) {
        if (name.empty()) {
            return "Name cannot be empty.";
        }
        if (name.size() > kMaxNameLength) {
            return "Name cannot be longer than " + std::to_string(kMaxNameLength) +
                " characters.";
        }
        for (char ch : name) {
            const unsigned char c = static_cast<unsigned char>(ch);
            // Letters, spaces, hyphens, apostrophes; bytes >= 0x80 allow accented
            // (UTF-8) letters.
            const bool allowed = std::isalpha(c) || c >= 0x80 ||
                                c == ' ' || c == '-' || c == '\'';
            if (!allowed) {
                return "Name may only contain letters, spaces, hyphens and apostrophes.";
            }
        }
        return std::nullopt;
    }

    // Checks that the date of birth is not in the future and that the age is within the allowed range.
    std::optional<std::string> checkDateOfBirth(const Date& dateOfBirth, const Date& today) {
        if (today < dateOfBirth) {
            return "Date of birth cannot be in the future.";
        }
        const int age = dateOfBirth.ageOn(today);
        if (age < kMinAge) {
            return "Student must be at least " + std::to_string(kMinAge) + " years old.";
        }
        if (age > kMaxAge) {
            return "Student cannot be older than " + std::to_string(kMaxAge) + " years.";
        }
        return std::nullopt;
    }

    // Checks that the GPA is within the allowed range.
    std::optional<std::string> checkGpa(double gpa) {
        if (gpa < kMinGpa || gpa > kMaxGpa) {
            return rangeMessage("GPA", kMinGpa, kMaxGpa);
        }
        return std::nullopt;
    }

    // Checks that the semester is within the allowed range.
    std::optional<std::string> checkSemester(int semester) {
        if (semester < kMinSemester || semester > kMaxSemester) {
            return rangeMessage("Semester", kMinSemester, kMaxSemester);
        }
        return std::nullopt;
    }

    // Checks that the number of courses is within the allowed range.
    std::optional<std::string> checkNumberOfCourses(int numberOfCourses) {
        if (numberOfCourses < kMinCourses || numberOfCourses > kMaxCourses) {
            return rangeMessage("Number of courses", kMinCourses, kMaxCourses);
        }
        return std::nullopt;
    }

} // namespace validation