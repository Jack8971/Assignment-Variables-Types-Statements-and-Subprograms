## How to Run

Both programs are console menus with the same options. Both load and save `students.csv` in the folder they are started from, using the same file format.

### Requirements

| Program | Needs |
|---|---|
| C++ (`PartB`) | A C++17 compiler (g++ / MinGW or Visual Studio Build Tools) and CMake |
| Python (`PartC`) | Python 3.10 or newer (no extra packages) |

### C++ (PartB)

```
cd PartB
cmake -S . -B build
cmake --build build
```

Then run:

| System | Command |
|---|---|
| Windows (MinGW / Ninja) | `.\build\enrollment.exe` |
| Windows (Visual Studio) | `.\build\Debug\enrollment.exe` |
| Mac / Linux | `./build/enrollment` |

If `build` already exists, only `cmake --build build` is needed. If CMake reports a generator or `nmake` error, delete `build` and run again. With MinGW add `-G "MinGW Makefiles"` to the first command, or use the "Developer PowerShell for VS" for Visual Studio.

No CMake? From inside `PartB`: `g++ -std=c++17 -Iinclude src/*.cpp -o enrollment`

### Python (PartC)

```
cd PartC
python main.py
```

Use `py main.py` if `python` is not recognized on Windows.

### Using the menu

Type a number and press Enter: 1 Add, 2 View all, 3 Search, 4 Modify, 5 Remove, 6 Sort, 7 Filter by program, 8 Statistics, 0 Exit. Changes are saved to the CSV file after add, modify and remove.

### Options (both programs)

| Option | Effect |
|---|---|
| `--no-persist` | Do not load or save; start with an empty list |
| `somefile.csv` | Use a different data file |

Examples: `./build/enrollment --no-persist` and `python main.py other.csv`

### Check that both programs match

Run the same scenario in each program with a new data file, then compare the saved files. Run the three scenarios in order (`persist_1_add`, `persist_2_view_remove`, `persist_3_add_again`).

```
# from PartB
./build/enrollment cpp_test.csv < tests/scenarios/persist_1_add.in

# from PartC
python main.py py_test.csv < ../PartB/tests/scenarios/persist_1_add.in

# compare (no output means identical)
cmp PartB/cpp_test.csv PartC/py_test.csv
```

On Windows use `.\build\enrollment.exe`, backslashes in paths, and `fc` instead of `cmp`. Delete the test files afterwards; they are not part of the project.

### Troubleshooting

| Problem | Fix |
|---|---|
| `cmake` or `g++` not recognized | Install it, then close and reopen the terminal |
| `nmake` / generator error | Delete `PartB/build` and rebuild (see above) |
| `python` not recognized | Try `py main.py` or install Python 3.10+ |
| "No saved data found" | Normal on a first run; the file is created on the first save |