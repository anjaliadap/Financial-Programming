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
Since I’m using a Windows laptop with MSYS2/MinGW, I had to link against an additional experimental library (`libstdc++exp`) in order to use the new C++23 `<print>` header.

So my compile command is:

`g++ -std=c++23 -Iinclude src/*.cpp -o example_date.exe -lstdc++exp`

If you are compiling on Linux/macOS, you may not need `-lstdc++exp`.


## ▶️ Running the Program
After compilation, run:

`./example_date.exe`

The program output will appear directly in the terminal.

---

## 📄 Creating Output as a .txt File
Sometimes it’s useful to save the program’s output into a file instead of only displaying it in the terminal.  
You can do this using **output redirection** (`>`).

After compiling your program, run:

`./example_date.exe > example_date.txt`

- This will run the program and save everything it prints into a file named output.txt.
- If the file already exists, it will be overwritten.
- To append output to an existing file instead of overwriting, use:
  `./example_date.exe >> example_date.txt`

  You can then open output.txt in any text editor (like Notepad, Visual Studio Code, or within the terminal using `cat output.txt`).


