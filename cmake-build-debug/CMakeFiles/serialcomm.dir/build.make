# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/314/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/314/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lab03/Desktop/ejadaarms/serialcomm-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/serialcomm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/serialcomm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/serialcomm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serialcomm.dir/flags.make

CMakeFiles/serialcomm.dir/main.cpp.o: CMakeFiles/serialcomm.dir/flags.make
CMakeFiles/serialcomm.dir/main.cpp.o: /home/lab03/Desktop/ejadaarms/serialcomm-master/main.cpp
CMakeFiles/serialcomm.dir/main.cpp.o: CMakeFiles/serialcomm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serialcomm.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/serialcomm.dir/main.cpp.o -MF CMakeFiles/serialcomm.dir/main.cpp.o.d -o CMakeFiles/serialcomm.dir/main.cpp.o -c /home/lab03/Desktop/ejadaarms/serialcomm-master/main.cpp

CMakeFiles/serialcomm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/serialcomm.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lab03/Desktop/ejadaarms/serialcomm-master/main.cpp > CMakeFiles/serialcomm.dir/main.cpp.i

CMakeFiles/serialcomm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/serialcomm.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lab03/Desktop/ejadaarms/serialcomm-master/main.cpp -o CMakeFiles/serialcomm.dir/main.cpp.s

# Object files for target serialcomm
serialcomm_OBJECTS = \
"CMakeFiles/serialcomm.dir/main.cpp.o"

# External object files for target serialcomm
serialcomm_EXTERNAL_OBJECTS =

serialcomm: CMakeFiles/serialcomm.dir/main.cpp.o
serialcomm: CMakeFiles/serialcomm.dir/build.make
serialcomm: CMakeFiles/serialcomm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable serialcomm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialcomm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serialcomm.dir/build: serialcomm
.PHONY : CMakeFiles/serialcomm.dir/build

CMakeFiles/serialcomm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serialcomm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serialcomm.dir/clean

CMakeFiles/serialcomm.dir/depend:
	cd /home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lab03/Desktop/ejadaarms/serialcomm-master /home/lab03/Desktop/ejadaarms/serialcomm-master /home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug /home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug /home/lab03/Desktop/ejadaarms/serialcomm-master/cmake-build-debug/CMakeFiles/serialcomm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/serialcomm.dir/depend

