// [ORIGINAL] 
#include <exception>
#include <iostream>
#include <cstring>
#include <string>

#include "CsvStorage.h"
#include "ConsoleUI.h"
#include "EnrollmentManager.h"

int main(int argc, char* argv[]) {
    try {
        std::string dataFile = "students.csv";
        bool persist = true;
        if (argc > 1) {
            if (std::strcmp(argv[1], "--no-persist") == 0) {
                persist = false;
            } else {
                dataFile = argv[1];
            }
        }

        EnrollmentManager manager;
        CsvStorage storage(dataFile);

        if (persist) {
            const LoadResult loaded = storage.load(manager);
            if (loaded.fileFound) {
                std::cout << "Loaded " << loaded.loaded << " student(s) from "
                          << dataFile << ".\n";
                if (loaded.skipped > 0) {
                    std::cout << "Warning: skipped " << loaded.skipped
                              << " invalid record(s).\n";
                }
            } else {
                std::cout << "No saved data found. Starting with an empty list.\n";
            }
        }

        ConsoleUI ui(manager, persist ? &storage : nullptr);
        ui.run();
    }
    catch (const std::exception& error) {
        std::cerr << "Fatal error: " <<error.what() << "\n";
        return 1;
    }
    return 0;
}