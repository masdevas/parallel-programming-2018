# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/masdevas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/masdevas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/masdevas/Learning/Parallel_TBB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/masdevas/Learning/Parallel_TBB/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/Parallel_OpenMP.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Parallel_OpenMP.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Parallel_OpenMP.dir/flags.make

src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.o: src/CMakeFiles/Parallel_OpenMP.dir/flags.make
src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.o: ../src/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masdevas/Learning/Parallel_TBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.o"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Parallel_OpenMP.dir/image.cpp.o -c /home/masdevas/Learning/Parallel_TBB/src/image.cpp

src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel_OpenMP.dir/image.cpp.i"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masdevas/Learning/Parallel_TBB/src/image.cpp > CMakeFiles/Parallel_OpenMP.dir/image.cpp.i

src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel_OpenMP.dir/image.cpp.s"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masdevas/Learning/Parallel_TBB/src/image.cpp -o CMakeFiles/Parallel_OpenMP.dir/image.cpp.s

src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.o: src/CMakeFiles/Parallel_OpenMP.dir/flags.make
src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.o: ../src/png.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masdevas/Learning/Parallel_TBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.o"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Parallel_OpenMP.dir/png.cpp.o -c /home/masdevas/Learning/Parallel_TBB/src/png.cpp

src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel_OpenMP.dir/png.cpp.i"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masdevas/Learning/Parallel_TBB/src/png.cpp > CMakeFiles/Parallel_OpenMP.dir/png.cpp.i

src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel_OpenMP.dir/png.cpp.s"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masdevas/Learning/Parallel_TBB/src/png.cpp -o CMakeFiles/Parallel_OpenMP.dir/png.cpp.s

src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.o: src/CMakeFiles/Parallel_OpenMP.dir/flags.make
src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/masdevas/Learning/Parallel_TBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.o"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Parallel_OpenMP.dir/main.cpp.o -c /home/masdevas/Learning/Parallel_TBB/src/main.cpp

src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel_OpenMP.dir/main.cpp.i"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/masdevas/Learning/Parallel_TBB/src/main.cpp > CMakeFiles/Parallel_OpenMP.dir/main.cpp.i

src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel_OpenMP.dir/main.cpp.s"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && /usr/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/masdevas/Learning/Parallel_TBB/src/main.cpp -o CMakeFiles/Parallel_OpenMP.dir/main.cpp.s

# Object files for target Parallel_OpenMP
Parallel_OpenMP_OBJECTS = \
"CMakeFiles/Parallel_OpenMP.dir/image.cpp.o" \
"CMakeFiles/Parallel_OpenMP.dir/png.cpp.o" \
"CMakeFiles/Parallel_OpenMP.dir/main.cpp.o"

# External object files for target Parallel_OpenMP
Parallel_OpenMP_EXTERNAL_OBJECTS =

src/Parallel_OpenMP: src/CMakeFiles/Parallel_OpenMP.dir/image.cpp.o
src/Parallel_OpenMP: src/CMakeFiles/Parallel_OpenMP.dir/png.cpp.o
src/Parallel_OpenMP: src/CMakeFiles/Parallel_OpenMP.dir/main.cpp.o
src/Parallel_OpenMP: src/CMakeFiles/Parallel_OpenMP.dir/build.make
src/Parallel_OpenMP: src/CMakeFiles/Parallel_OpenMP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/masdevas/Learning/Parallel_TBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Parallel_OpenMP"
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Parallel_OpenMP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Parallel_OpenMP.dir/build: src/Parallel_OpenMP

.PHONY : src/CMakeFiles/Parallel_OpenMP.dir/build

src/CMakeFiles/Parallel_OpenMP.dir/clean:
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/Parallel_OpenMP.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Parallel_OpenMP.dir/clean

src/CMakeFiles/Parallel_OpenMP.dir/depend:
	cd /home/masdevas/Learning/Parallel_TBB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/masdevas/Learning/Parallel_TBB /home/masdevas/Learning/Parallel_TBB/src /home/masdevas/Learning/Parallel_TBB/cmake-build-debug /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src /home/masdevas/Learning/Parallel_TBB/cmake-build-debug/src/CMakeFiles/Parallel_OpenMP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Parallel_OpenMP.dir/depend
