# Assignment-Variables-Types-Statements-and-Subprograms
# SAIT Student Enrollment Management System

> Group 2 · CMPS 3020 BSA · Instructor: Omar Wahdan
> Assignment: Variables, Types, Statements and Subprograms

A prototype enrollment management system for SAIT administrative staff, implemented twice, in **C++** (`PartB`) and in **Python** (`PartC`), so the two languages can be compared on variables, types, binding, scoping, referencing and subprograms. Both programs follow the same pseudocode (`docs/part1_pseudocode.md`) and must produce the same output.

> Admin-only tool: students cannot enroll themselves.

---

## Team

| Name | GitHub | Primary Contributions |
|------|--------|-----------------------|
| Jackson Battista | @Jack8971 |  Part 1 pseudocode,  Part 2: C++ program (`PartB`) |
| Kunj Kalpeshkumar Patel | @kunj406962 |  Part 1 pseudocode,  Part 2: C++ program (`PartB`) |
| Temi Bankole | @TODO | Part 3: Python program (`PartC`) |
| Zeynep Ozdemir | @TODO | Part 3: Python program (`PartC`) |
| Sehabir | @TODO | Part 3: Python program (`PartC`) |
| All members | |Part 4 comparison, Part 5 peer review, testing |

## Assignment Parts

| Assignment part | Letter | What | Where |
|---|---|---|---|
| Part 1 | A | Pseudocode | `docs/part1_pseudocode.md` (Word copy in the Brightspace ZIP) |
| Part 2 | B | C++ program | `PartB/` |
| Part 3 | C | Python program | `PartC/` |
| Part 4 | D | Comparison table, C++ vs Python | Word document (Brightspace ZIP) |
| Part 5 | E | Peer review | Word document (Brightspace ZIP) |

---

## What the Program Does

A console menu program for administrative staff. Records are kept in memory while the program runs.

```
===== SAIT Enrollment Management =====
1. Add student
2. Modify student
3. Remove student
4. View all students
0. Exit
Enter choice:
```

- [ ] **Add** a student (every field is checked and re-requested until valid)
- [ ] **Modify** one field of an existing student (or cancel)
- [ ] **Remove** a student after a yes/no confirmation
- [ ] **View** all students
- [ ] Identical prompts, messages and results in the C++ and Python programs

Planned extras, not in the Part 1 pseudocode (mark them in the code as additions):

- [ ] Search by id, name or program
- [ ] Load from / save to the shared JSON data file (see [Data Files](#data-files))

## Student Record Fields

| Field | Type | Rules |
|-------|------|-------|
| Student ID | integer | assigned automatically starting at 1001, unique, never reused |
| First name | string | 1–50 characters: letters, spaces, hyphens, apostrophes |
| Last name | string | same as first name |
| Date of birth | string `YYYY-MM-DD` | must be a real calendar date (leap years handled) |
| Gender | string | one of the fixed `GENDERS` list in the pseudocode |
| Previous GPA | real | 0.0 – 4.0 |
| Current semester | integer | 1 – 8 |
| Program | string | one of the fixed `PROGRAMS` list in the pseudocode |
| Number of courses | integer | 1 – 8 |

---

## Repository Structure

```
Assignment-Variables-Types-Statements-and-Subprograms/
├── README.md
├── data/
│   ├── students.json            # team's own student data
│   ├── students.sample.json     # AI-assisted sample data (see AI_use.txt)
│   └── AI_use.txt               # which data files used AI help
├── docs/
│   └── part1_pseudocode.md      # Part 1 pseudocode
├── PartB/                       # Part 2: C++
│   ├── CMakeLists.txt
│   ├── include/
│   │   ├── ConsoleUI.h          # menu and prompts
│   │   ├── Date.h               # date of birth
│   │   ├── EnrollmentManager.h  # add / modify / remove / find
│   │   ├── InputValidation.h    # input checking
│   │   ├── Person.h             # personal details
│   │   └── Student.h            # student record
│   └── src/
│       └── main.cpp
├── PartC/                       # Part 3: Python
│   ├── main.py
│   ├── student.py
│   ├── enrollment_manager.py
│   ├── input_validation.py
│   ├── json_storage.py
│   ├── main_window.py
│   ├── student_dialog.py
│   └── requirements.txt
└── tests/
    ├── compare_json_output.py   # compares two saved data files
    └── test_scenarios.md        # test inputs and expected results
```

---

## Git Workflow and Branches

`main` always holds working, reviewed code. Each assignment part has its own branch, and work reaches `main` through a pull request.

| Branch | Assignment part | What it holds | Owner |
|--------|-----------------|---------------|-------|
| `main` | | Final, working code only. No direct commits | All members |
| `feature/part-a` | Part 1 | Pseudocode (`docs/part1_pseudocode.md`) | Jackson / Kunj |
| `feature/part-b` | Part 2 | C++ program (`PartB/`) | Jackson / Kunj |
| `feature/part-c` | Part 3 | Python program (`PartC/`) and `tests/` | Temi / Zeynep / Sehabir |
| `feature/part-d` | Part 4 | Comparison table drafts | All members |
| `feature/part-e` | Part 5 | Peer review drafts | All members |

Parts 4 and 5 are Word documents submitted through Brightspace, so `feature/part-d` and `feature/part-e` only hold drafts and are not part of the final repo contents.

### Day-to-day workflow

```bash
git checkout main
git pull                              # start from the latest main
git checkout -b feature/part-b        # create your branch (first time only)

# ... write code, then commit often with a clear message
git add PartB/include/Student.h
git commit -m "Add Student class with fields"

git push -u origin feature/part-b     # push the branch
# On GitHub: open a Pull Request into main, a teammate reviews, then merge

git checkout feature/part-b
git pull origin main                  # bring merged changes back into your branch
```

### Rules

- Only these branches: `main` and `feature/part-a` to `feature/part-e`
- Commit your own work from your own GitHub account, since the history is evidence for the Part 5 peer review
- Every pull request is reviewed by at least one teammate before merging
- Only merge code that builds and runs; pull `main` into your branch first to catch conflicts
- Write commit messages as short actions: "Add remove student", "Fix leap-year check"
- Add the `[ORIGINAL]` / `[EXTERNAL-MODIFIED]` comments before you commit, not afterwards

### Suggested merge order

1. `feature/part-a` (pseudocode first, since Parts 2 and 3 are built from it)
2. `feature/part-b` and `feature/part-c` (in parallel)

---

## Requirements

| | C++ (`PartB`) | Python (`PartC`) |
|---|---|---|
| Language | C++17 | Python 3.10+ |
| Libraries | standard library | standard library |
| Build | CMake 3.16+ and a C++17 compiler | none |

## Build & Run

### C++
```bash
cd PartB
cmake -B build
cmake --build build
./build/<executable>          # Windows: build\Debug\<executable>.exe
```
The executable name is set in `PartB/CMakeLists.txt` (TODO: add the name here once it is written).

### Python
```bash
cd PartC
python main.py
```

---

## Data Files

`data/students.sample.json` and `data/students.json` hold starting student records in JSON. They let both programs begin with the same data so their results can be compared. Loading and saving is a planned extra (see above); the Part 1 pseudocode keeps records in memory only.

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

- Keys use camelCase; Python converts to `snake_case` when reading and writing.
- `nextStudentId` must be higher than every existing `id`.
- Files are written with 2-space indent, sorted keys and a newline at the end, so a file saved by either program is identical and `tests/compare_json_output.py` can compare them.

---

## Testing

Run the same typed input through **both** programs and compare what they print:

```bash
cd PartB && ./build/<executable> < ../tests/input1.txt > ../cpp_output.txt
cd ../PartC && python main.py < ../tests/input1.txt > ../py_output.txt
diff ../cpp_output.txt ../py_output.txt        # no output means they match
```

Write each scenario's inputs and expected results in `tests/test_scenarios.md`. Things to test in both programs:

- Add a valid student, then bad input: empty name, name with digits, GPA 5, semester 9, courses 0, date `2023-02-30`, letters where a number is expected. Each must re-ask, not crash.
- Modify every field, and cancel with `0`
- Remove with `y` and with `n`; try an id that does not exist
- View all with no students and with several
- Menu: enter a number outside 0–4 and text instead of a number

### Test results

| Test | C++ | Python |
|---|---|---|
| Add valid student | | |
| Add with invalid input (re-asks) | | |
| Modify each field | | |
| Modify and cancel | | |
| Remove with y / n | | |
| Remove unknown id | | |
| View all (empty and with data) | | |
| Invalid menu choice | | |
| Same input gives same output in both | | |

## Design Decisions

- **Containers:** students are held in a dynamic list (`std::vector` in C++, `list` in Python); gender and program choices are fixed-size arrays. A student record groups the fields.
- **Subprograms:** add, modify, remove, find, display and each input check are separate subprograms, as in the pseudocode. The Part 4 document compares how each language passes arguments (by value, by reference).
- **Validation:** every input subprogram repeats until the value is valid, so invalid data never reaches the list.
- **Static vs dynamic binding:** C++ types are fixed at compile time; Python types are bound at run time. Part 4 compares both.

## Code Attribution & AI Use

As required by the assignment, code that came from an external tool or was adapted from an online source is marked in-code:

```
// [ORIGINAL]            written by our team
// [EXTERNAL-MODIFIED]   from a tool/online source, heavily modified by us (Python: # ...)
```

An AI assistant (Claude, by Anthropic) was used to help produce the structure of this README, the assignment outline, a sample data in `data/students.sample.json`. The team reviewed and adapted this material. `data/students.json` was written by the team without AI. Details for the data files are in [`data/AI_use.txt`](data/AI_use.txt).

TODO: list which source files (if any) contain tool-assisted code, who modified them, and how.

## Known Limitations

- No login: the program assumes administrative staff run it, and it has no function that lets a student enroll themselves.
- Students are found by a linear search through the list, which is fine for a prototype-sized list.
- If JSON saving is added, do not run both programs on the same data file at the same time (no file locking; the last save wins).

## Documentation (submitted via Brightspace)

- Part 1: Pseudocode, also in [`docs/part1_pseudocode.md`](docs/part1_pseudocode.md)
- Part 4: Comparison table (Word)
- Part 5: Peer review (Word)

## Academic Note

Submitted for academic assessment at SAIT. See SAIT policy AC.3.4.3 (Student Academic Conduct).
