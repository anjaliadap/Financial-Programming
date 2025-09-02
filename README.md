# Financial Programming 

## 📂 Project Structure
To keep the project organized and easy to read, I sorted my files into two main folders:

- **`src/`** → contains all the C++ **source files** (`.cpp`).  
  Examples:  
  - `example_date.cpp` (main program)  
  - `date.cpp` (implementation for `date.h`)  
  - `black_scholes.cpp` (implementation for `black_scholes.h`)  

- **`include/`** → contains all the **header files** (`.h`).  
  Examples:  
  - `date.h`  
  - `black_scholes.h`  

This separation follows common industry practices:  
- Headers define *interfaces* (class/function declarations).  
- Source files contain the actual *implementations*.  
- It keeps the codebase modular and much more readable.

## ⚙️ Compilation Instructions

### Standard compilation
From inside the `HW1` folder:

`g++ -std=c++23 -Iinclude src/*.cpp -o example_date.exe`

This compiles all the .cpp files and produces an executable named example_date.exe.

## Windows-specific note

Since I’m using a Windows laptop with MSYS2/MinGW, I had to link against an additional experimental library (libstdc++exp) in order to use the new C++23 `<print>` header.

So my compile command is:

`g++ -std=c++23 -Iinclude src/*.cpp -o example_date.exe -lstdc++exp`

If you are compiling on Linux/macOS, you may not need `-lstdc++exp`.


## ▶️ Running the Program

After compilation, run:

`./example_date.exe`

The program output will appear directly in the terminal.

## 📝 Notes

This repository is organized into subfolders like HW1/, HW2/, etc. for each homework assignment.

Each homework folder has its own src/ and include/ directories to keep code separated and modular.

