// [ORIGINAL] 
#include <exception>
#include <iostream>

#include "ConsoleUI.h"
#include "EnrollmentManager.h"

int main() {
    try {
        EnrollmentManager manager; //logic layer; contains all student records
        ConsoleUI ui(manager); //UI layer: works on the manager by reference
        ui.run(); 
    }
    catch (const std::exception& error) {
        std::cerr << "Fatal error: " <<error.what() << "\n";
        return 1;
    }
    return 0;
}