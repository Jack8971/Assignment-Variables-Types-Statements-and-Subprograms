// [EXTERNAL-MODIFIED] All the code was written by Kunj but Jackson wrote it in this file to learn C++ but Kunj had copilot to auto complete and add proper concise comments to the code
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "EnrollmentManager.h"
#include "CsvStorage.h"

// Presentation layer: all menus, prompts and printing live here.
// Streams are injected so the UI can be driven from a file in tests.
class ConsoleUI {
    public:
        // References are stored, not copied: the UI works on the caller's objects.
        explicit ConsoleUI(EnrollmentManager& manager,
                        CsvStorage* storage = nullptr,
                        std::istream& in = std::cin,
                        std::ostream& out = std::cout);

        // Main loop: show the menu until the user exits (or input ends).
        void run();
    private:
        EnrollmentManager& manager_;
        CsvStorage* storage_;
        std::istream& in_;
        std::ostream& out_;

        // Menu actions
        void printMenu();
        void addStudent();
        void viewAllStudents();
        void searchStudents();
        void modifyStudent();
        void removeStudent();
        void sortStudents();
        void filterByProgram();
        void showStatistics();
        void saveChanges();

        // Output helpers
        void printPerson(const Person& person);
        void printStudentList(const std::string& heading,
                            const std::vector<const Student*>& students);

        // Modify helper: takes the record by (non-const) reference and edits it in place.
        void modifyFields(Student& student);

        // Input helpers
        std::string readLine(const std::string& prompt);
        int promptMenuChoice(const std::string& prompt, int low, int high);
        bool promptYesNo(const std::string& prompt);
        Student* promptExistingStudent();

        std::string promptName(const std::string& prompt);
        Date promptDateOfBirth(const std::string& prompt);
        double promptGpa();
        int promptSemester();
        int promptNumberOfCourses();

        // Generic prompt loop: read, parse, validate, repeat until valid.
        template <typename Value, typename Parse, typename Check>
        Value promptValue(const std::string& prompt, const std::string& formatHint,
                        Parse parse, Check check);

        // Numbered menu built from any fixed-size array of enum values.
        template <typename Option, std::size_t N>
        Option promptChoice(const std::string& title, const std::array<Option, N>& options);
};

#endif // CONSOLE_UI_H