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
include CMakeFiles/1629.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/1629.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1629.dir/flags.make

CMakeFiles/1629.dir/1629_slowest_key.cpp.obj: CMakeFiles/1629.dir/flags.make
CMakeFiles/1629.dir/1629_slowest_key.cpp.obj: ../1629_slowest_key.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Project\LEARNING\AdsLearning\leetcode\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1629.dir/1629_slowest_key.cpp.obj"
	D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\1629.dir\1629_slowest_key.cpp.obj -c D:\Project\LEARNING\AdsLearning\leetcode\1629_slowest_key.cpp

CMakeFiles/1629.dir/1629_slowest_key.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1629.dir/1629_slowest_key.cpp.i"
	D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\LEARNING\AdsLearning\leetcode\1629_slowest_key.cpp > CMakeFiles\1629.dir\1629_slowest_key.cpp.i

CMakeFiles/1629.dir/1629_slowest_key.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1629.dir/1629_slowest_key.cpp.s"
	D:\DevelopTool\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\LEARNING\AdsLearning\leetcode\1629_slowest_key.cpp -o CMakeFiles\1629.dir\1629_slowest_key.cpp.s

# Object files for target 1629
1629_OBJECTS = \
"CMakeFiles/1629.dir/1629_slowest_key.cpp.obj"

# External object files for target 1629
1629_EXTERNAL_OBJECTS =

1629.exe: CMakeFiles/1629.dir/1629_slowest_key.cpp.obj
1629.exe: CMakeFiles/1629.dir/build.make
1629.exe: CMakeFiles/1629.dir/linklibs.rsp
1629.exe: CMakeFiles/1629.dir/objects1.rsp
1629.exe: CMakeFiles/1629.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Project\LEARNING\AdsLearning\leetcode\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1629.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\1629.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1629.dir/build: 1629.exe
.PHONY : CMakeFiles/1629.dir/build

CMakeFiles/1629.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\1629.dir\cmake_clean.cmake
.PHONY : CMakeFiles/1629.dir/clean

CMakeFiles/1629.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\LEARNING\AdsLearning\leetcode D:\Project\LEARNING\AdsLearning\leetcode D:\Project\LEARNING\AdsLearning\leetcode\build D:\Project\LEARNING\AdsLearning\leetcode\build D:\Project\LEARNING\AdsLearning\leetcode\build\CMakeFiles\1629.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1629.dir/depend

