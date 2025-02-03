# Project Overview

This project is a modular C++ application designed to interact with serial ports, process data, and write it to pickle files. The application is structured for maintainability, with separate libraries for general utilities, serial port handling, and pickle writing.

---

## File Structure

### Main Files
- **`main.cpp`**: The entry point of the application. Includes the main logic for serial communication and data processing.

### Utility Libraries
- **`general_utils.h`**: Header file for general utility functions.
- **`general_utils.cpp`**: Implementation of general utility functions like timestamp generation, safe zone checking, and extracting values from JSON-like strings.

### Class Libraries
- **`PickleWriter.h`**: Header file for the `PickleWriter` class, which handles writing data to pickle files.
- **`PickleWriter.cpp`**: Implementation of the `PickleWriter` class.
- **`SerialPort.h`**: Header file for the `SerialPort` class, which manages serial port communication.
- **`SerialPort.cpp`**: Implementation of the `SerialPort` class.

### Other
- **`README.md`**: This documentation file.

---

## Adding a New Function
If you want to implement a new function in this project, follow these steps:

1. **Identify the Appropriate Location**:
   - If it is a utility function (e.g., string manipulation, file handling), add it to `general_utils.h` and implement it in `general_utils.cpp`.
   - If it is class-related, determine whether it belongs in the `PickleWriter` or `SerialPort` class. Add the declaration in the respective `.h` file and implement it in the corresponding `.cpp` file.

2. **Create a New Header and Implementation File (if needed)**:
   - If the new function or functionality requires its own module:
     - Create a new `.h` file (e.g., `NewFeature.h`) for the declarations.
     - Create a corresponding `.cpp` file (e.g., `NewFeature.cpp`) for the implementation.
   - Add the usual header guards to the `.h` file:
     ```cpp
     #ifndef NEW_FEATURE_H
     #define NEW_FEATURE_H
     
     // Function declarations or class definitions
     
     #endif
     ```
   - In the `.cpp` file, include the new header:
     ```cpp
     #include "NewFeature.h"
     ```

3. **Update the Headers**:
   - Add the declaration of the new function or class in the relevant `.h` file, or the newly created `.h` file.

4. **Implement the Function**:
   - Write the function implementation in the corresponding `.cpp` file.

5. **Include the Header in `main.cpp`**:
   - Ensure the header file containing the new function is included in `main.cpp` if the function is needed there.

6. **Test the Function**:
   - Add test cases in `main.cpp` or a dedicated test file to ensure the function works as expected.

---

## Compiling the Application
To compile the application into an executable:

### Using g++
Run the following command in the terminal:

```bash
g++ -o main.exe main.cpp general_utils.cpp PickleWriter.cpp SerialPort.cpp -lsetupapi
for linux: g++ -o threads.exe main.cpp general_utils.cpp PickleWriter.cpp SerialPort.cpp -pthread $(pkg-config --cflags --libs opencv4)
```

### Explanation of the Command:
- **`-o main.exe`**: Specifies the name of the output executable.
- **`main.cpp general_utils.cpp PickleWriter.cpp SerialPort.cpp`**: Includes all source files required for compilation.
- **`-lsetupapi`**: Links the SetupAPI library, necessary for serial communication on Windows.

### Using Visual Studio
1. Open Visual Studio and create a new Console Application project.
2. Add all `.cpp` and `.h` files to the project.
3. Ensure the SetupAPI library is linked in the linker settings.
4. Build the solution to generate the executable.

---

Feel free to reach out if you encounter issues or need further assistance!

