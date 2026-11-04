# Assignment-Variables-Types-Statements-and-Subprograms

# SAIT Student Enrollment Management System

> Group 2 — Variables, Types, Statements and Subprograms

A prototype enrollment management system for SAIT administrative staff, implemented twice
(**C++ / Qt 6** and **Python / PySide6**) so the two languages can be compared on variables,
types, binding, scoping, referencing and subprograms. Both programs read and write the
**same JSON data file**.

> Admin-only tool: students cannot enroll themselves.

---

## Team

| Name | GitHub | Primary Contributions |
|------|--------|-----------------------|
| Jackson / Kunj | @TODO | Part 2 — C++ program (Qt GUI, core logic, JSON storage) |
| Temi / Zeynep / Sehabir | @TODO | Part 3 — Python program (PySide6 GUI, core logic, JSON storage) |
| All members | — | Part 1 pseudocode, Part 4 comparison, Part 5 peer review, testing |

---

## Features

- [ ] Add a student record
- [ ] Modify a student record
- [ ] Remove a student record (with confirmation)
- [ ] View all students in a table
- [ ] Search / filter students (id, name or program)
- [ ] Input validation (names, DOB, GPA, semester, courses)
- [ ] Load from / save to shared `data/students.json`
- [ ] Unsaved-changes protection (`*` in the title, confirm on reload and close)
- [ ] Identical behaviour and layout in the C++ and Python GUIs

## Student Record Fields

| Field | JSON key | JSON type | C++ type | Python type | Rules |
|-------|----------|-----------|----------|-------------|-------|
| Student ID | `id` | integer | `int` | `int` | auto-generated from 1001, unique, never reused |
| First name | `firstName` | string | `std::string` | `str` | 1–50 chars; letters, spaces, hyphens, apostrophes |
| Last name | `lastName` | string | `std::string` | `str` | same as first name |
| Date of birth | `dateOfBirth` | string | `std::string` | `str` | `YYYY-MM-DD`, real date, not in future, age 16–100 |
| Gender | `gender` | string | `std::string` | `str` | Female, Male, Non-binary, Prefer not to say |
| Previous GPA | `previousGpa` | number | `double` | `float` | 0.00 – 4.00 |
| Current semester | `currentSemester` | integer | `int` | `int` | 1 – 8 |
| Program | `program` | string | `std::string` | `str` | Software Development, Information Technology, Cybersecurity, Data Analytics, Business Administration, Computer Systems Technology |
| Number of courses | `numberOfCourses` | integer | `int` | `int` | 1 – 8 |

## Data File Format

Both programs use one file, `data/students.json`:

```json
{
  "nextStudentId": 1006,
  "students": [
    {
      "currentSemester": 2,
      "dateOfBirth": "2004-03-15",
      "firstName": "Amara",
      "gender": "Female",
      "id": 1001,
      "lastName": "Okafor",
      "numberOfCourses": 5,
      "previousGpa": 3.5,
      "program": "Software Development"
    }
  ]
}
```

- Keys use camelCase in the file; Python converts to `snake_case` only when reading and writing.
- Files are written with 2-space indent, UTF-8, keys sorted A–Z, a newline at the end and GPA rounded to 2 decimals, so a file saved by either program is identical.
- `nextStudentId` is stored in the file so ids never collide and are never reused.
- A missing or empty file is created as `{"nextStudentId": 1001, "students": []}`.
- A malformed file, a missing or wrongly typed key, an invalid value or a duplicate id shows an error message. The file is never overwritten, and editing is disabled until a successful Reload.
- Saving writes a temporary file and then replaces the real one, so a crash cannot corrupt the data.

`data/students.sample.json` holds 5 sample students. Copy it over `data/students.json` to reset.

---

## Repository Structure

```
sait-enrollment-system/
├── README.md
├── .gitignore
├── data/
│   ├── students.json            # shared live data file (used by BOTH programs)
│   └── students.sample.json     # clean sample data for resetting tests
├── docs/
│   └── part1_pseudocode.md
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
└── python/
    ├── requirements.txt
    ├── main.py
    ├── student.py
    ├── enrollment_manager.py
    ├── json_storage.py
    ├── input_validation.py
    ├── main_window.py
    └── student_dialog.py
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

Both implementations mirror this layering file-for-file. The pseudocode in [`docs/part1_pseudocode.md`](docs/part1_pseudocode.md) follows the same structure.

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
If CMake cannot find Qt, add `-DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/<kit>` to the first command.

### Python
```bash
cd python
pip install -r requirements.txt
python main.py
```

### Choosing the data file

Both programs load `../data/students.json` by default. To use a different file, give its path as the first argument:

```bash
./build/enrollment ../data/students.sample.json
python main.py ../data/students.sample.json
```

---

## Usage

1. Start either program. The table shows every student in the data file.
2. **Add**: fill in the dialog and press OK. Invalid input shows a message and keeps the dialog open.
3. **Modify**: select a row, press Modify, change values, press OK.
4. **Remove**: select a row, press Remove, confirm with Yes.
5. **Search**: type an id, name or program and press Search (or Enter). **Clear** shows everyone again.
6. **Save** writes the data file. A `*` in the window title means there are unsaved changes. **Reload** re-reads the file.

TODO: add screenshots of both GUIs side by side.

## Testing

Reset the data (copy `data/students.sample.json` over `data/students.json`), then run the same steps in **both** programs:

- Add a valid student, then try invalid names (empty, digits, symbols); the dialog must stay open with the message
- Modify a student; try Cancel and confirm nothing changes
- Remove a student with Yes and with No; try Modify and Remove with nothing selected
- Search by id, first name, last name and program, in upper and lower case; try a term with no match; press Clear
- Make a change, then try Reload and closing the window; the unsaved-changes questions must appear
- Start with a missing file, an empty file and a malformed file; the program must not crash or overwrite the file
- Save in one program and open the same file in the other; both must load it with no errors
- After the same add / modify / remove steps in each program, compare the saved files: `diff fileA.json fileB.json` must show no differences

## Design Decisions

- **Data structures:** students are held in a dynamic container (`std::vector<Student>` in C++, `list[Student]` in Python); gender and program choices are fixed-size arrays/constant lists. A `Student` struct (C++) or `@dataclass` (Python) is the record type.
- **Layering:** GUI, logic, data, model and validation are separate files so the language concepts (binding, scoping, referencing, argument passing) stay visible and the logic is testable without a GUI.
- **Static vs dynamic binding:** C++ types are fixed at compile time; Python types are bound at run time. Both are compared in the Part 4 document.
- **Validation:** pure functions in `InputValidation` return a result and an error message; the same rules run when the user types a record and when a file is loaded.
- **Save strategy:** manual Save with an unsaved-changes marker and confirmations on Reload and Close.
- **Failed loads are safe:** if the file cannot be read, nothing is overwritten and editing is disabled until a successful Reload.

## Code Attribution & AI Use

As required by the assignment, code that came from an external tool or was adapted from an online source is marked in-code:

```
// [ORIGINAL]            written by our team
// [EXTERNAL-MODIFIED]   from a tool/online source, heavily modified by us (python: # ...)
```

An AI assistant (Claude, by Anthropic) was used to help produce the structure of this README, the assignment outline, the draft JSON data format and the first draft of the pseudocode. The team reviewed and adapted this material.

TODO: list which source files (if any) contain tool-assisted code, who modified them, and how.

## Known Limitations

- Both programs must not be open on the same data file at the same time (no file locking; the last save wins).
- Names accept letters, spaces, hyphens and apostrophes only (no digits or other punctuation).
- Messages are not pluralised (for example "Students loaded: 1").
- The gender and program lists are fixed in the code, not read from the file.

## Documentation (submitted via Brightspace)

- Part 1: Pseudocode — also in [`docs/part1_pseudocode.md`](docs/part1_pseudocode.md)
- Part 4: Comparison table (Word)
- Part 5: Peer review (Word)

## Academic Note

Submitted for academic assessment at SAIT. See SAIT policy AC.3.4.3 (Student Academic Conduct).
