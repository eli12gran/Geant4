# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eli_gran/examples/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eli_gran/examples/project/build

# Utility rule file for CubeSim.

# Include any custom commands dependencies for this target.
include CMakeFiles/CubeSim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CubeSim.dir/progress.make

CMakeFiles/CubeSim: src/exampleCubeSim

CubeSim: CMakeFiles/CubeSim
CubeSim: CMakeFiles/CubeSim.dir/build.make
.PHONY : CubeSim

# Rule to build all files generated by this target.
CMakeFiles/CubeSim.dir/build: CubeSim
.PHONY : CMakeFiles/CubeSim.dir/build

CMakeFiles/CubeSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CubeSim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CubeSim.dir/clean

CMakeFiles/CubeSim.dir/depend:
	cd /home/eli_gran/examples/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eli_gran/examples/project /home/eli_gran/examples/project /home/eli_gran/examples/project/build /home/eli_gran/examples/project/build /home/eli_gran/examples/project/build/CMakeFiles/CubeSim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CubeSim.dir/depend

