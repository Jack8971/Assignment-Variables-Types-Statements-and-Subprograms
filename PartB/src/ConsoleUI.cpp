// [ORIGINAL] 
// [EXTERNAL-MODIFIED] most comments were written by Claude.
#include "ConsoleUI.h"

#include <cctype>
#include <iomanip>
#include <optional>
#include <utility>

#include "InputValidation.h"

namespace {
// Thrown when stdin ends (Ctrl+D / end of a redirected file) mid-prompt.
struct EndOfInput {};

const char* const kDuplicateMessage =
    "A student with the same name and date of birth already exists.";
} // namespace

ConsoleUI::ConsoleUI(EnrollmentManager& manager, std::istream& in, std::ostream& out)
    : manager_(manager), in_(in), out_(out) {}

// ---------------------------------------------------------------- input helpers

std::string ConsoleUI::readLine(const std::string& prompt) {
    out_ << prompt;
    std::string line;
    if (!std::getline(in_, line)) {
        throw EndOfInput{};
    }
    return line;
}

template <typename Value, typename Parse, typename Check>
Value ConsoleUI::promptValue(const std::string& prompt, const std::string& formatHint,
                             Parse parse, Check check) {
    while (true) {
        const std::optional<Value> parsed = parse(readLine(prompt));
        if (!parsed) {
            out_ << "Error: " << formatHint << "\n";
            continue;
        }
        if (const std::optional<std::string> error = check(*parsed)) {
            out_ << "Error: " << *error << "\n";
            continue;
        }
        return *parsed;
    }
}

template <typename Option, std::size_t N>
Option ConsoleUI::promptChoice(const std::string& title,
                               const std::array<Option, N>& options) {
    out_ << title << "\n";
    for (std::size_t i = 0; i < N; ++i) {
        out_ << "  " << (i + 1) << ". " << toString(options[i]) << "\n";
    }
    const int choice = promptMenuChoice(
        "Enter choice (1-" + std::to_string(N) + "): ", 1, static_cast<int>(N));
    return options[static_cast<std::size_t>(choice - 1)];
}

int ConsoleUI::promptMenuChoice(const std::string& prompt, int low, int high) {
    while (true) {
        const std::optional<int> choice = validation::parseInt(readLine(prompt));
        if (choice && *choice >= low && *choice <= high) {
            return *choice;
        }
        out_ << "Error: Invalid choice. Please enter a number from "
             << low << " to " << high << ".\n";
    }
}

bool ConsoleUI::promptYesNo(const std::string& prompt) {
    while (true) {
        const std::string answer = validation::trim(readLine(prompt));
        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;
        out_ << "Error: Please answer y or n.\n";
    }
}

std::string ConsoleUI::promptName(const std::string& prompt) {
    return promptValue<std::string>(
        prompt, "Name cannot be empty.",
        [](const std::string& line) -> std::optional<std::string> {
            return validation::trim(line); // always "parses"; checkName judges it
        },
        validation::checkName);
}

Date ConsoleUI::promptDateOfBirth(const std::string& prompt) {
    const Date today = Date::today(); // local variable captured by the lambda below
    return promptValue<Date>(
        prompt, "Invalid date. Use the format YYYY-MM-DD (e.g. 2005-01-19).",
        [](const std::string& line) { return Date::parse(validation::trim(line)); },
        [&today](const Date& dob) { return validation::checkDateOfBirth(dob, today); });
}

double ConsoleUI::promptGpa() {
    return promptValue<double>(
        "GPA from previous institution (0.0 - 4.0): ",
        "Invalid number. Please enter a decimal such as 3.5.",
        validation::parseDouble, validation::checkGpa);
}

int ConsoleUI::promptSemester() {
    return promptValue<int>(
        "Current semester (1 - 8): ",
        "Invalid number. Please enter a whole number.",
        validation::parseInt, validation::checkSemester);
}

int ConsoleUI::promptNumberOfCourses() {
    return promptValue<int>(
        "Number of courses (1 - 10): ",
        "Invalid number. Please enter a whole number.",
        validation::parseInt, validation::checkNumberOfCourses);
}

// Returns a pointer to the chosen record, or nullptr if the ID was not found.
Student* ConsoleUI::promptExistingStudent() {
    const std::optional<int> id = validation::parseInt(readLine("Enter student ID: "));
    if (!id) {
        out_ << "Error: Invalid ID. Please enter a number.\n";
        return nullptr;
    }
    Student* student = manager_.findStudent(*id);
    if (student == nullptr) {
        out_ << "Error: No student found with ID " << *id << ".\n";
    }
    return student;
}

// --------------------------------------------------------------- output helpers

// Takes the BASE type by const reference: describe() is resolved at run time
// to Student::describe() (dynamic binding).
void ConsoleUI::printPerson(const Person& person) {
    out_ << person.describe() << "\n";
}

void ConsoleUI::printStudentList(const std::string& heading,
                                 const std::vector<const Student*>& students) {
    out_ << "\n--- " << heading << " (" << students.size() << ") ---\n";
    if (students.empty()) {
        out_ << "No students to display.\n";
        return;
    }
    for (const Student* student : students) {
        printPerson(*student);
    }
}

void ConsoleUI::printMenu() {
    out_ << "\n===== SAIT Enrollment Management System =====\n"
         << "1. Add student\n"
         << "2. View all students\n"
         << "3. Search students by name\n"
         << "4. Modify student\n"
         << "5. Remove student\n"
         << "6. View students sorted\n"
         << "7. Filter students by program\n"
         << "8. Show statistics\n"
         << "0. Exit\n";
}

// ----------------------------------------------------------------- menu actions

void ConsoleUI::run() {
    try {
        bool running = true;
        while (running) {
            printMenu();
            const int choice = promptMenuChoice("Enter your choice: ", 0, 8);
            switch (choice) {
                case 1: addStudent();        break;
                case 2: viewAllStudents();   break;
                case 3: searchStudents();    break;
                case 4: modifyStudent();     break;
                case 5: removeStudent();     break;
                case 6: sortStudents();      break;
                case 7: filterByProgram();   break;
                case 8: showStatistics();    break;
                case 0: running = false;     break;
            }
        }
        out_ << "Goodbye!\n";
    } catch (const EndOfInput&) {
        out_ << "\nEnd of input. Exiting program.\n";
    }
}

void ConsoleUI::addStudent() {
    out_ << "\n--- Add Student ---\n";
    std::string firstName = promptName("First name: ");
    std::string lastName = promptName("Last name: ");
    const Date dateOfBirth = promptDateOfBirth("Date of birth (YYYY-MM-DD): ");

    if (manager_.existsDuplicate(firstName, lastName, dateOfBirth)) {
        out_ << "Error: " << kDuplicateMessage << "\nStudent was not added.\n";
        return;
    }

    const Gender gender = promptChoice("Gender:", kAllGenders);
    const double gpa = promptGpa();
    const int semester = promptSemester();
    const Program program = promptChoice("Program:", kAllPrograms);
    const int courses = promptNumberOfCourses();

    const int newId = manager_.addStudent(std::move(firstName), std::move(lastName),
                                          dateOfBirth, gender, gpa, semester,
                                          program, courses);
    out_ << "Student added successfully with ID: " << newId << "\n";
}

void ConsoleUI::viewAllStudents() {
    printStudentList("All Students", manager_.allStudents());
}

void ConsoleUI::searchStudents() {
    const std::string text = validation::trim(readLine("Enter name to search for: "));
    if (text.empty()) {
        out_ << "Error: Search text cannot be empty.\n";
        return;
    }
    printStudentList("Search Results", manager_.searchByName(text));
}

void ConsoleUI::modifyStudent() {
    out_ << "\n--- Modify Student ---\n";
    Student* student = promptExistingStudent();
    if (student == nullptr) {
        return;
    }
    modifyFields(*student); // dereference: pass the record itself by reference
}

void ConsoleUI::modifyFields(Student& student) {
    bool editing = true;
    while (editing) {
        out_ << "\nCurrent record:\n";
        printPerson(student);
        out_ << "Which field do you want to modify?\n"
             << "  1. First name\n"
             << "  2. Last name\n"
             << "  3. Date of birth\n"
             << "  4. Gender\n"
             << "  5. GPA\n"
             << "  6. Current semester\n"
             << "  7. Program\n"
             << "  8. Number of courses\n"
             << "  0. Done\n";
        const int choice = promptMenuChoice("Enter your choice: ", 0, 8);
        switch (choice) {
            case 1: {
                std::string newFirst = promptName("New first name: ");
                if (manager_.existsDuplicate(newFirst, student.lastName(),
                                             student.dateOfBirth(), student.studentId())) {
                    out_ << "Error: " << kDuplicateMessage << "\n";
                    break;
                }
                student.setFirstName(std::move(newFirst));
                out_ << "First name updated.\n";
                break;
            }
            case 2: {
                std::string newLast = promptName("New last name: ");
                if (manager_.existsDuplicate(student.firstName(), newLast,
                                             student.dateOfBirth(), student.studentId())) {
                    out_ << "Error: " << kDuplicateMessage << "\n";
                    break;
                }
                student.setLastName(std::move(newLast));
                out_ << "Last name updated.\n";
                break;
            }
            case 3: {
                const Date newDob = promptDateOfBirth("New date of birth (YYYY-MM-DD): ");
                if (manager_.existsDuplicate(student.firstName(), student.lastName(),
                                             newDob, student.studentId())) {
                    out_ << "Error: " << kDuplicateMessage << "\n";
                    break;
                }
                student.setDateOfBirth(newDob);
                out_ << "Date of birth updated.\n";
                break;
            }
            case 4:
                student.setGender(promptChoice("Gender:", kAllGenders));
                out_ << "Gender updated.\n";
                break;
            case 5:
                student.setGpa(promptGpa());
                out_ << "GPA updated.\n";
                break;
            case 6:
                student.setCurrentSemester(promptSemester());
                out_ << "Current semester updated.\n";
                break;
            case 7:
                student.setProgram(promptChoice("Program:", kAllPrograms));
                out_ << "Program updated.\n";
                break;
            case 8:
                student.setNumberOfCourses(promptNumberOfCourses());
                out_ << "Number of courses updated.\n";
                break;
            case 0:
                editing = false;
                break;
        }
    }
    out_ << "Modification finished.\n";
}

void ConsoleUI::removeStudent() {
    out_ << "\n--- Remove Student ---\n";
    const Student* student = promptExistingStudent();
    if (student == nullptr) {
        return;
    }
    printPerson(*student);
    const int id = student->studentId(); // copy the ID: the record is about to vanish
    if (!promptYesNo("Are you sure you want to remove this student? (y/n): ")) {
        out_ << "Removal cancelled.\n";
        return;
    }
    manager_.removeStudent(id);
    out_ << "Student " << id << " removed.\n";
}

void ConsoleUI::sortStudents() {
    out_ << "\nSort by:\n  1. GPA (highest first)\n  2. Last name (A-Z)\n";
    const int choice = promptMenuChoice("Enter choice (1-2): ", 1, 2);
    if (choice == 1) {
        printStudentList("Students Sorted by GPA", manager_.sortedByGpaDescending());
    } else {
        printStudentList("Students Sorted by Last Name", manager_.sortedByLastName());
    }
}

void ConsoleUI::filterByProgram() {
    const Program program = promptChoice("Program:", kAllPrograms);
    printStudentList("Students in " + toString(program),
                     manager_.filterByProgram(program));
}

void ConsoleUI::showStatistics() {
    out_ << "\n--- Statistics ---\n";
    if (manager_.studentCount() == 0) {
        out_ << "No students enrolled.\n";
        return;
    }
    out_ << "Total students: " << manager_.studentCount() << "\n"
         << "Average GPA: " << std::fixed << std::setprecision(2)
         << manager_.averageGpa() << "\n"
         << "Students per program:\n";
    for (Program program : kAllPrograms) {
        out_ << "  " << toString(program) << ": "
             << manager_.countInProgram(program) << "\n";
    }
}
