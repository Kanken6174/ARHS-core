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
include model/hardware/hw/CMakeFiles/hw.dir/depend.make

# Include the progress variables for this target.
include model/hardware/hw/CMakeFiles/hw.dir/progress.make

# Include the compile flags for this target's objects.
include model/hardware/hw/CMakeFiles/hw.dir/flags.make

model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.o: model/hardware/hw/CMakeFiles/hw.dir/flags.make
model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.o: model/hardware/hw/serial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kanken/code/AHRS_core/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.o"
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw.dir/serial.cpp.o -c /home/kanken/code/AHRS_core/src/model/hardware/hw/serial.cpp

model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw.dir/serial.cpp.i"
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kanken/code/AHRS_core/src/model/hardware/hw/serial.cpp > CMakeFiles/hw.dir/serial.cpp.i

model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw.dir/serial.cpp.s"
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kanken/code/AHRS_core/src/model/hardware/hw/serial.cpp -o CMakeFiles/hw.dir/serial.cpp.s

# Object files for target hw
hw_OBJECTS = \
"CMakeFiles/hw.dir/serial.cpp.o"

# External object files for target hw
hw_EXTERNAL_OBJECTS =

model/hardware/hw/libhw.a: model/hardware/hw/CMakeFiles/hw.dir/serial.cpp.o
model/hardware/hw/libhw.a: model/hardware/hw/CMakeFiles/hw.dir/build.make
model/hardware/hw/libhw.a: model/hardware/hw/CMakeFiles/hw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kanken/code/AHRS_core/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libhw.a"
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && $(CMAKE_COMMAND) -P CMakeFiles/hw.dir/cmake_clean_target.cmake
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
model/hardware/hw/CMakeFiles/hw.dir/build: model/hardware/hw/libhw.a

.PHONY : model/hardware/hw/CMakeFiles/hw.dir/build

model/hardware/hw/CMakeFiles/hw.dir/clean:
	cd /home/kanken/code/AHRS_core/src/model/hardware/hw && $(CMAKE_COMMAND) -P CMakeFiles/hw.dir/cmake_clean.cmake
.PHONY : model/hardware/hw/CMakeFiles/hw.dir/clean

model/hardware/hw/CMakeFiles/hw.dir/depend:
	cd /home/kanken/code/AHRS_core/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kanken/code/AHRS_core/src /home/kanken/code/AHRS_core/src/model/hardware/hw /home/kanken/code/AHRS_core/src /home/kanken/code/AHRS_core/src/model/hardware/hw /home/kanken/code/AHRS_core/src/model/hardware/hw/CMakeFiles/hw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : model/hardware/hw/CMakeFiles/hw.dir/depend

