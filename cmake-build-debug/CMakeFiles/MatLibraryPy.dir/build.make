# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/miguel/clion-2020.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/miguel/clion-2020.1.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/MatLibraryPy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MatLibraryPy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MatLibraryPy.dir/flags.make

CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o: CMakeFiles/MatLibraryPy.dir/flags.make
CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o: ../MatLibraryPy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o -c "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/MatLibraryPy.cpp"

CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/MatLibraryPy.cpp" > CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.i

CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/MatLibraryPy.cpp" -o CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.s

# Object files for target MatLibraryPy
MatLibraryPy_OBJECTS = \
"CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o"

# External object files for target MatLibraryPy
MatLibraryPy_EXTERNAL_OBJECTS =

MatLibraryPy.so: CMakeFiles/MatLibraryPy.dir/MatLibraryPy.cpp.o
MatLibraryPy.so: CMakeFiles/MatLibraryPy.dir/build.make
MatLibraryPy.so: /usr/lib/x86_64-linux-gnu/libboost_python38.so.1.71.0
MatLibraryPy.so: /usr/lib/x86_64-linux-gnu/libpython3.8.so
MatLibraryPy.so: CMakeFiles/MatLibraryPy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module MatLibraryPy.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MatLibraryPy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MatLibraryPy.dir/build: MatLibraryPy.so

.PHONY : CMakeFiles/MatLibraryPy.dir/build

CMakeFiles/MatLibraryPy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MatLibraryPy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MatLibraryPy.dir/clean

CMakeFiles/MatLibraryPy.dir/depend:
	cd "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy" "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy" "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug" "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug" "/home/miguel/Escritorio/SIANI/1 Cuatrimestre/PP/MatLibraryPy/cmake-build-debug/CMakeFiles/MatLibraryPy.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/MatLibraryPy.dir/depend

