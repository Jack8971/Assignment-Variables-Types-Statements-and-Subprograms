# Assignment-Variables-Types-Statements-and-Subprograms

# SAIT Student Enrollment Management System

A prototype enrollment management system for SAIT administrative staff, implemented twice
(**C++ / Qt 6** and **Python / PySide6**) so the two languages can be compared on variables,
types, binding, scoping, referencing and subprograms. Both programs read and write the
**same JSON data file**.

> Admin-only tool: students cannot enroll themselves.

---

## Team

| Name | GitHub | Primary Contributions |
|------|--------|-----------------------|
| Jackson/Kunj | @TODO  | TODO (e.g. Part 2 C++ core + JSON) |
| Temi/zeynep/Sehabir | @TODO  | TODO (e.g. Part 3 Python) |
| TODO | @TODO  | TODO (e.g. GUI / Part 4) |
| ALL | @TODO  | TODO (e.g. Part 1 / Part 5 / testing) |

---

## Features

- [ ] Add a student record
- [ ] Modify a student record
- [ ] Remove a student record (with confirmation)
- [ ] View all students in a table
- [ ] Search / filter students
- [ ] Input validation (names, DOB, GPA, semester, courses)
- [ ] Load from / save to shared `data/students.json`
- [ ] Identical behaviour and layout in the C++ and Python GUIs

## Student Record Fields

| Field | JSON key | JSON type | C++ type | Python type | Rules |
|-------|----------|-----------|----------|-------------|-------|
| Student ID | `id` | integer | `int` | `int` | auto-generated, unique |
| First name | `firstName` | string | `std::string` | `str` | TODO |
| Last name | `lastName` | string | `std::string` | `str` | TODO |
| Date of birth | `dateOfBirth` | string | `std::string` | `str` | `YYYY-MM-DD`, real date, not in future |
| Gender | `gender` | string | `std::string` | `str` | one of TODO |
| Previous GPA | `previousGpa` | number | `double` | `float` | 0.00 – 4.00 |
| Current semester | `currentSemester` | integer | `int` | `int` | TODO range |
| Program | `program` | string | `std::string` | `str` | one of TODO list |
| Number of courses | `numberOfCourses` | integer | `int` | `int` | TODO range |

Full contract: [`docs/json_schema.md`](docs/json_schema.md)

---

## Repository Structure

```
sait-enrollment-system/
├── README.md
├── .gitignore
├── data/
│   ├── students.json            # shared live data file (used by BOTH programs)
│   └── students.sample.json     # clean seed data for resetting tests
├── docs/
│   ├── part1_pseudocode.md
│   ├── json_schema.md
│   ├── ui_spec.md
│   └── test_cases.md
├── cpp/
│   ├── CMakeLists.txt
│   ├── third_party/nlohmann/json.hpp
│   └── src/
│       ├── main.cpp
│       ├── Student.h / Student.cpp
│       ├── EnrollmentManager.h / .cpp
│       ├── JsonStorage.h / .cpp
│       ├── InputValidation.h / .cpp
│       ├── MainWindow.h / .cpp
│       └── StudentDialog.h / .cpp
├── python/
│   ├── requirements.txt
│   ├── main.py
│   ├── student.py
│   ├── enrollment_manager.py
│   ├── json_storage.py
│   ├── input_validation.py
│   ├── main_window.py
│   └── student_dialog.py
└── tests/
    ├── compare_json_output.py
    └── test_scenarios.md
```

## Architecture

```
GUI layer      MainWindow, StudentDialog
     │
Logic layer    EnrollmentManager        (add / modify / remove / search)
     │
Data layer     JsonStorage              (load / save students.json)
     │
Model          Student
Validation     InputValidation          (pure functions, no GUI code)
```

Both implementations mirror this layering file-for-file.

---

## Requirements

| | C++ | Python |
|---|---|---|
| Language | C++17 | Python 3.10+ |
| GUI | Qt 6 (Widgets) | PySide6 |
| JSON | nlohmann/json (bundled, header-only) | built-in `json` |
| Build | CMake 3.16+ and a C++17 compiler | none |

## Build & Run

### C++
```bash
cd cpp
cmake -B build
cmake --build build
./build/enrollment            # Windows: build\Debug\enrollment.exe
```

### Python
```bash
cd python
pip install -r requirements.txt
python main.py
```

Both programs load `../data/students.json` by default. TODO: document optional path argument.

---

## Usage

TODO: screenshots of both GUIs side by side + short walkthrough
(add → modify → remove → search → save).

## Testing

- Reset data: copy `data/students.sample.json` over `data/students.json`
- Scenarios and expected results: [`docs/test_cases.md`](docs/test_cases.md)
- Cross-language check: `python tests/compare_json_output.py <fileA> <fileB>`
- Compatibility: a file written by one program must load unchanged in the other

## Design Decisions

- **Data structures:** TODO (e.g. `std::vector<Student>` / `list[Student]`, and why)
- **Static vs dynamic binding:** TODO
- **Validation rules and where they live:** TODO
- **Save strategy (autosave vs manual):** TODO
- **JSON formatting:** 2-space indent, UTF-8, sorted keys so files diff cleanly

## Code Attribution & AI Use

As required by the assignment, code that came from an external tool or was adapted from
an online source is marked in-code:

```
// [ORIGINAL]            written by our team
// [EXTERNAL-MODIFIED]   from a tool/online source, heavily modified by us (python: # ...)
```

TODO: short summary of what was tool-assisted, by whom, and how it was modified.

## Known Limitations

- TODO (e.g. no concurrent-access locking if both programs run at once)

## Documentation (submitted via Brightspace)

- Part 1: Pseudocode — also in [`docs/part1_pseudocode.md`](docs/part1_pseudocode.md)
- Part 4: Comparison table (Word)
- Part 5: Peer review (Word)

## Academic Note

Submitted for academic assessment at SAIT. See SAIT policy AC.3.4.3 (Student Academic Conduct).
