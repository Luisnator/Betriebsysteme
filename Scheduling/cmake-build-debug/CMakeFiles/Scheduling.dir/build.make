# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/luis/Downloads/clion-2018.1.5/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/luis/Downloads/clion-2018.1.5/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luis/Github/Betriebsysteme/Scheduling

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Scheduling.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Scheduling.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Scheduling.dir/flags.make

CMakeFiles/Scheduling.dir/main.c.o: CMakeFiles/Scheduling.dir/flags.make
CMakeFiles/Scheduling.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Scheduling.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Scheduling.dir/main.c.o   -c /home/luis/Github/Betriebsysteme/Scheduling/main.c

CMakeFiles/Scheduling.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Scheduling.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luis/Github/Betriebsysteme/Scheduling/main.c > CMakeFiles/Scheduling.dir/main.c.i

CMakeFiles/Scheduling.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Scheduling.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luis/Github/Betriebsysteme/Scheduling/main.c -o CMakeFiles/Scheduling.dir/main.c.s

CMakeFiles/Scheduling.dir/main.c.o.requires:

.PHONY : CMakeFiles/Scheduling.dir/main.c.o.requires

CMakeFiles/Scheduling.dir/main.c.o.provides: CMakeFiles/Scheduling.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Scheduling.dir/build.make CMakeFiles/Scheduling.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Scheduling.dir/main.c.o.provides

CMakeFiles/Scheduling.dir/main.c.o.provides.build: CMakeFiles/Scheduling.dir/main.c.o


# Object files for target Scheduling
Scheduling_OBJECTS = \
"CMakeFiles/Scheduling.dir/main.c.o"

# External object files for target Scheduling
Scheduling_EXTERNAL_OBJECTS =

Scheduling: CMakeFiles/Scheduling.dir/main.c.o
Scheduling: CMakeFiles/Scheduling.dir/build.make
Scheduling: CMakeFiles/Scheduling.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Scheduling"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Scheduling.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Scheduling.dir/build: Scheduling

.PHONY : CMakeFiles/Scheduling.dir/build

CMakeFiles/Scheduling.dir/requires: CMakeFiles/Scheduling.dir/main.c.o.requires

.PHONY : CMakeFiles/Scheduling.dir/requires

CMakeFiles/Scheduling.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Scheduling.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Scheduling.dir/clean

CMakeFiles/Scheduling.dir/depend:
	cd /home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luis/Github/Betriebsysteme/Scheduling /home/luis/Github/Betriebsysteme/Scheduling /home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug /home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug /home/luis/Github/Betriebsysteme/Scheduling/cmake-build-debug/CMakeFiles/Scheduling.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Scheduling.dir/depend

