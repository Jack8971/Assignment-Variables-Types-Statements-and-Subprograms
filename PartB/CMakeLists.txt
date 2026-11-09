# [EXTERNAL-MODIFIED] used CLAUDE to generate the following CMakeLists.txt file because I do not know how to write it. I will review it and make any necessary changes.
cmake_minimum_required(VERSION 3.16)
project(EnrollmentSystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(enrollment
    src/main.cpp src/Date.cpp src/Person.cpp src/Student.cpp
    src/InputValidation.cpp src/EnrollmentManager.cpp src/ConsoleUI.cpp src/CsvStorage.cpp)
target_include_directories(enrollment PRIVATE include)
target_compile_options(enrollment PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)