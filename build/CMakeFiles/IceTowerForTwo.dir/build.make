# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ruxuge/CLionProjects/IceTowerForTwo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruxuge/CLionProjects/IceTowerForTwo/build

# Include any dependencies generated for this target.
include CMakeFiles/IceTowerForTwo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IceTowerForTwo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IceTowerForTwo.dir/flags.make

CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o: CMakeFiles/IceTowerForTwo.dir/flags.make
CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruxuge/CLionProjects/IceTowerForTwo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o -c /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp

CMakeFiles/IceTowerForTwo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IceTowerForTwo.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp > CMakeFiles/IceTowerForTwo.dir/src/main.cpp.i

CMakeFiles/IceTowerForTwo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IceTowerForTwo.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp -o CMakeFiles/IceTowerForTwo.dir/src/main.cpp.s

# Object files for target IceTowerForTwo
IceTowerForTwo_OBJECTS = \
"CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o"

# External object files for target IceTowerForTwo
IceTowerForTwo_EXTERNAL_OBJECTS =

IceTowerForTwo: CMakeFiles/IceTowerForTwo.dir/src/main.cpp.o
IceTowerForTwo: CMakeFiles/IceTowerForTwo.dir/build.make
IceTowerForTwo: CMakeFiles/IceTowerForTwo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruxuge/CLionProjects/IceTowerForTwo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IceTowerForTwo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IceTowerForTwo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IceTowerForTwo.dir/build: IceTowerForTwo

.PHONY : CMakeFiles/IceTowerForTwo.dir/build

CMakeFiles/IceTowerForTwo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IceTowerForTwo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IceTowerForTwo.dir/clean

CMakeFiles/IceTowerForTwo.dir/depend:
	cd /home/ruxuge/CLionProjects/IceTowerForTwo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruxuge/CLionProjects/IceTowerForTwo /home/ruxuge/CLionProjects/IceTowerForTwo /home/ruxuge/CLionProjects/IceTowerForTwo/build /home/ruxuge/CLionProjects/IceTowerForTwo/build /home/ruxuge/CLionProjects/IceTowerForTwo/build/CMakeFiles/IceTowerForTwo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IceTowerForTwo.dir/depend

