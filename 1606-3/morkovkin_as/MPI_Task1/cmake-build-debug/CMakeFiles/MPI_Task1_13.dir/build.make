# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/masdevas/Soft/apps/CLion/ch-0/182.3911.40/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/masdevas/Soft/apps/CLion/ch-0/182.3911.40/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/masdevas/Learning/MPI_Task1_13

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masdevas/Learning/MPI_Task1_13/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MPI_Task1_13.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MPI_Task1_13.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MPI_Task1_13.dir/flags.make

CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o: CMakeFiles/MPI_Task1_13.dir/flags.make
CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masdevas/Learning/MPI_Task1_13/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o"
	/usr/bin/clang++-6.0  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o -c /home/masdevas/Learning/MPI_Task1_13/src/main.cpp

CMakeFiles/MPI_Task1_13.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_Task1_13.dir/src/main.cpp.i"
	/usr/bin/clang++-6.0 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masdevas/Learning/MPI_Task1_13/src/main.cpp > CMakeFiles/MPI_Task1_13.dir/src/main.cpp.i

CMakeFiles/MPI_Task1_13.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_Task1_13.dir/src/main.cpp.s"
	/usr/bin/clang++-6.0 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masdevas/Learning/MPI_Task1_13/src/main.cpp -o CMakeFiles/MPI_Task1_13.dir/src/main.cpp.s

# Object files for target MPI_Task1_13
MPI_Task1_13_OBJECTS = \
"CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o"

# External object files for target MPI_Task1_13
MPI_Task1_13_EXTERNAL_OBJECTS =

MPI_Task1_13: CMakeFiles/MPI_Task1_13.dir/src/main.cpp.o
MPI_Task1_13: CMakeFiles/MPI_Task1_13.dir/build.make
MPI_Task1_13: /usr/lib/x86_64-linux-gnu/libmpichcxx.so
MPI_Task1_13: /usr/lib/x86_64-linux-gnu/libmpich.so
MPI_Task1_13: /usr/lib/x86_64-linux-gnu/libomp.so
MPI_Task1_13: /usr/lib/x86_64-linux-gnu/libpthread.so
MPI_Task1_13: CMakeFiles/MPI_Task1_13.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masdevas/Learning/MPI_Task1_13/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MPI_Task1_13"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MPI_Task1_13.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MPI_Task1_13.dir/build: MPI_Task1_13

.PHONY : CMakeFiles/MPI_Task1_13.dir/build

CMakeFiles/MPI_Task1_13.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MPI_Task1_13.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MPI_Task1_13.dir/clean

CMakeFiles/MPI_Task1_13.dir/depend:
	cd /home/masdevas/Learning/MPI_Task1_13/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masdevas/Learning/MPI_Task1_13 /home/masdevas/Learning/MPI_Task1_13 /home/masdevas/Learning/MPI_Task1_13/cmake-build-debug /home/masdevas/Learning/MPI_Task1_13/cmake-build-debug /home/masdevas/Learning/MPI_Task1_13/cmake-build-debug/CMakeFiles/MPI_Task1_13.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MPI_Task1_13.dir/depend

