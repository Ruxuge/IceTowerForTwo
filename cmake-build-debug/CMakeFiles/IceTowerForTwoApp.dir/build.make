# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/ruxuge/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7142.21/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ruxuge/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7142.21/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ruxuge/CLionProjects/IceTowerForTwo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IceTowerForTwoApp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IceTowerForTwoApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IceTowerForTwoApp.dir/flags.make

CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o: CMakeFiles/IceTowerForTwoApp.dir/flags.make
CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o -c /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp

CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp > CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.i

CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruxuge/CLionProjects/IceTowerForTwo/src/main.cpp -o CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.s

# Object files for target IceTowerForTwoApp
IceTowerForTwoApp_OBJECTS = \
"CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o"

# External object files for target IceTowerForTwoApp
IceTowerForTwoApp_EXTERNAL_OBJECTS =

IceTowerForTwoApp: CMakeFiles/IceTowerForTwoApp.dir/src/main.cpp.o
IceTowerForTwoApp: CMakeFiles/IceTowerForTwoApp.dir/build.make
IceTowerForTwoApp: CMakeFiles/IceTowerForTwoApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IceTowerForTwoApp"
	/home/ruxuge/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7142.21/bin/cmake/linux/bin/cmake -E copy_directory /home/ruxuge/CLionProjects/IceTowerForTwo/data /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug/data
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IceTowerForTwoApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IceTowerForTwoApp.dir/build: IceTowerForTwoApp

.PHONY : CMakeFiles/IceTowerForTwoApp.dir/build

CMakeFiles/IceTowerForTwoApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IceTowerForTwoApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IceTowerForTwoApp.dir/clean

CMakeFiles/IceTowerForTwoApp.dir/depend:
	cd /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruxuge/CLionProjects/IceTowerForTwo /home/ruxuge/CLionProjects/IceTowerForTwo /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug /home/ruxuge/CLionProjects/IceTowerForTwo/cmake-build-debug/CMakeFiles/IceTowerForTwoApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IceTowerForTwoApp.dir/depend

