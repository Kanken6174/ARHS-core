# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/kanken/code/AHRS_core/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kanken/code/AHRS_core/src

# Include any dependencies generated for this target.
include model/hardware/ihidapi/CMakeFiles/ihidapi.dir/depend.make

# Include the progress variables for this target.
include model/hardware/ihidapi/CMakeFiles/ihidapi.dir/progress.make

# Include the compile flags for this target's objects.
include model/hardware/ihidapi/CMakeFiles/ihidapi.dir/flags.make

model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o: model/hardware/ihidapi/CMakeFiles/ihidapi.dir/flags.make
model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o: model/hardware/ihidapi/hidapi_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kanken/code/AHRS_core/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o"
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o -c /home/kanken/code/AHRS_core/src/model/hardware/ihidapi/hidapi_functions.cpp

model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ihidapi.dir/hidapi_functions.cpp.i"
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kanken/code/AHRS_core/src/model/hardware/ihidapi/hidapi_functions.cpp > CMakeFiles/ihidapi.dir/hidapi_functions.cpp.i

model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ihidapi.dir/hidapi_functions.cpp.s"
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kanken/code/AHRS_core/src/model/hardware/ihidapi/hidapi_functions.cpp -o CMakeFiles/ihidapi.dir/hidapi_functions.cpp.s

# Object files for target ihidapi
ihidapi_OBJECTS = \
"CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o"

# External object files for target ihidapi
ihidapi_EXTERNAL_OBJECTS =

model/hardware/ihidapi/libihidapi.a: model/hardware/ihidapi/CMakeFiles/ihidapi.dir/hidapi_functions.cpp.o
model/hardware/ihidapi/libihidapi.a: model/hardware/ihidapi/CMakeFiles/ihidapi.dir/build.make
model/hardware/ihidapi/libihidapi.a: model/hardware/ihidapi/CMakeFiles/ihidapi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kanken/code/AHRS_core/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libihidapi.a"
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && $(CMAKE_COMMAND) -P CMakeFiles/ihidapi.dir/cmake_clean_target.cmake
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ihidapi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
model/hardware/ihidapi/CMakeFiles/ihidapi.dir/build: model/hardware/ihidapi/libihidapi.a

.PHONY : model/hardware/ihidapi/CMakeFiles/ihidapi.dir/build

model/hardware/ihidapi/CMakeFiles/ihidapi.dir/clean:
	cd /home/kanken/code/AHRS_core/src/model/hardware/ihidapi && $(CMAKE_COMMAND) -P CMakeFiles/ihidapi.dir/cmake_clean.cmake
.PHONY : model/hardware/ihidapi/CMakeFiles/ihidapi.dir/clean

model/hardware/ihidapi/CMakeFiles/ihidapi.dir/depend:
	cd /home/kanken/code/AHRS_core/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kanken/code/AHRS_core/src /home/kanken/code/AHRS_core/src/model/hardware/ihidapi /home/kanken/code/AHRS_core/src /home/kanken/code/AHRS_core/src/model/hardware/ihidapi /home/kanken/code/AHRS_core/src/model/hardware/ihidapi/CMakeFiles/ihidapi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : model/hardware/ihidapi/CMakeFiles/ihidapi.dir/depend

