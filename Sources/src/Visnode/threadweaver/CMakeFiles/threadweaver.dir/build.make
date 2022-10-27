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
CMAKE_SOURCE_DIR = /home/kanken/code/AHRS_core/Sources/src/Visnode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kanken/code/AHRS_core/Sources/src/Visnode

# Include any dependencies generated for this target.
include threadweaver/CMakeFiles/threadweaver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include threadweaver/CMakeFiles/threadweaver.dir/compiler_depend.make

# Include the progress variables for this target.
include threadweaver/CMakeFiles/threadweaver.dir/progress.make

# Include the compile flags for this target's objects.
include threadweaver/CMakeFiles/threadweaver.dir/flags.make

threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o: threadweaver/CMakeFiles/threadweaver.dir/flags.make
threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o: threadweaver/threadweaver.cpp
threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o: threadweaver/CMakeFiles/threadweaver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kanken/code/AHRS_core/Sources/src/Visnode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o"
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o -MF CMakeFiles/threadweaver.dir/threadweaver.cpp.o.d -o CMakeFiles/threadweaver.dir/threadweaver.cpp.o -c /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver/threadweaver.cpp

threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadweaver.dir/threadweaver.cpp.i"
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver/threadweaver.cpp > CMakeFiles/threadweaver.dir/threadweaver.cpp.i

threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadweaver.dir/threadweaver.cpp.s"
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver/threadweaver.cpp -o CMakeFiles/threadweaver.dir/threadweaver.cpp.s

# Object files for target threadweaver
threadweaver_OBJECTS = \
"CMakeFiles/threadweaver.dir/threadweaver.cpp.o"

# External object files for target threadweaver
threadweaver_EXTERNAL_OBJECTS =

threadweaver/libthreadweaver.a: threadweaver/CMakeFiles/threadweaver.dir/threadweaver.cpp.o
threadweaver/libthreadweaver.a: threadweaver/CMakeFiles/threadweaver.dir/build.make
threadweaver/libthreadweaver.a: threadweaver/CMakeFiles/threadweaver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kanken/code/AHRS_core/Sources/src/Visnode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libthreadweaver.a"
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && $(CMAKE_COMMAND) -P CMakeFiles/threadweaver.dir/cmake_clean_target.cmake
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadweaver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
threadweaver/CMakeFiles/threadweaver.dir/build: threadweaver/libthreadweaver.a
.PHONY : threadweaver/CMakeFiles/threadweaver.dir/build

threadweaver/CMakeFiles/threadweaver.dir/clean:
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver && $(CMAKE_COMMAND) -P CMakeFiles/threadweaver.dir/cmake_clean.cmake
.PHONY : threadweaver/CMakeFiles/threadweaver.dir/clean

threadweaver/CMakeFiles/threadweaver.dir/depend:
	cd /home/kanken/code/AHRS_core/Sources/src/Visnode && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kanken/code/AHRS_core/Sources/src/Visnode /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver /home/kanken/code/AHRS_core/Sources/src/Visnode /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver /home/kanken/code/AHRS_core/Sources/src/Visnode/threadweaver/CMakeFiles/threadweaver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : threadweaver/CMakeFiles/threadweaver.dir/depend

