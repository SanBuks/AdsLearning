# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\DevelopTool\clion\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = D:\DevelopTool\clion\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project\LEARNING\AdsLearning\leetcode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project\LEARNING\AdsLearning\leetcode\build

# Include any dependencies generated for this target.
include math/CMakeFiles/0899.dir/depend.make
# Include the progress variables for this target.
include math/CMakeFiles/0899.dir/progress.make

# Include the compile flags for this target's objects.
include math/CMakeFiles/0899.dir/flags.make

math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.obj: math/CMakeFiles/0899.dir/flags.make
math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.obj: ../math/0899_orderly_queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\LEARNING\AdsLearning\leetcode\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.obj"
	cd /d D:\Project\LEARNING\AdsLearning\leetcode\build\math && D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\0899.dir\0899_orderly_queue.cpp.obj -c D:\Project\LEARNING\AdsLearning\leetcode\math\0899_orderly_queue.cpp

math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0899.dir/0899_orderly_queue.cpp.i"
	cd /d D:\Project\LEARNING\AdsLearning\leetcode\build\math && D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\LEARNING\AdsLearning\leetcode\math\0899_orderly_queue.cpp > CMakeFiles\0899.dir\0899_orderly_queue.cpp.i

math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0899.dir/0899_orderly_queue.cpp.s"
	cd /d D:\Project\LEARNING\AdsLearning\leetcode\build\math && D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\LEARNING\AdsLearning\leetcode\math\0899_orderly_queue.cpp -o CMakeFiles\0899.dir\0899_orderly_queue.cpp.s

# Object files for target 0899
0899_OBJECTS = \
"CMakeFiles/0899.dir/0899_orderly_queue.cpp.obj"

# External object files for target 0899
0899_EXTERNAL_OBJECTS =

math/0899.exe: math/CMakeFiles/0899.dir/0899_orderly_queue.cpp.obj
math/0899.exe: math/CMakeFiles/0899.dir/build.make
math/0899.exe: math/CMakeFiles/0899.dir/linklibs.rsp
math/0899.exe: math/CMakeFiles/0899.dir/objects1.rsp
math/0899.exe: math/CMakeFiles/0899.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project\LEARNING\AdsLearning\leetcode\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 0899.exe"
	cd /d D:\Project\LEARNING\AdsLearning\leetcode\build\math && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\0899.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
math/CMakeFiles/0899.dir/build: math/0899.exe
.PHONY : math/CMakeFiles/0899.dir/build

math/CMakeFiles/0899.dir/clean:
	cd /d D:\Project\LEARNING\AdsLearning\leetcode\build\math && $(CMAKE_COMMAND) -P CMakeFiles\0899.dir\cmake_clean.cmake
.PHONY : math/CMakeFiles/0899.dir/clean

math/CMakeFiles/0899.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\LEARNING\AdsLearning\leetcode D:\Project\LEARNING\AdsLearning\leetcode\math D:\Project\LEARNING\AdsLearning\leetcode\build D:\Project\LEARNING\AdsLearning\leetcode\build\math D:\Project\LEARNING\AdsLearning\leetcode\build\math\CMakeFiles\0899.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : math/CMakeFiles/0899.dir/depend
