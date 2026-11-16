#file header and some comments helped by Cursor
"""
main.py

This file is the starting point of the Python enrollment program.
It is based on PartB main.cpp.

It contains:
- main() which loads the JSON data file (optional)
- Creates the EnrollmentManager and MainWindow
- Starts the menu loop
"""

import sys
from enrollment_manager import EnrollmentManager
from json_storage import JsonStorage
from main_window import MainWindow


def main():
    data_file = "../data/students.json"
    persist = True

    # check if user passed any command line args
    if len(sys.argv) > 1:
        if sys.argv[1] == "--no-persist":
            persist = False
        else:
            data_file = sys.argv[1]

    # manager holds all the students in memory
    manager = EnrollmentManager()
    storage = None

    # load saved students if persistence is on
    if persist:
        storage = JsonStorage(data_file)
        result = storage.load(manager)
        if result.file_found:
            print("Loaded", result.loaded, "student(s) from", data_file + ".")
            if result.skipped > 0:
                print("Warning: skipped", result.skipped, "invalid record(s).")
        else:
            # first time running / no file yet
            print("No saved data found. Starting with an empty list.")

    # start the menu loop
    ui = MainWindow(manager, storage)
    ui.run()


# only run main() if this file is run directly
if __name__ == "__main__":
    main()
