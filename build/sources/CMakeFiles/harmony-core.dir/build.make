# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/tima/gitForks/harmony-core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tima/gitForks/harmony-core/build

# Include any dependencies generated for this target.
include sources/CMakeFiles/harmony-core.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include sources/CMakeFiles/harmony-core.dir/compiler_depend.make

# Include the progress variables for this target.
include sources/CMakeFiles/harmony-core.dir/progress.make

# Include the compile flags for this target's objects.
include sources/CMakeFiles/harmony-core.dir/flags.make

sources/CMakeFiles/harmony-core.dir/note.cpp.o: sources/CMakeFiles/harmony-core.dir/flags.make
sources/CMakeFiles/harmony-core.dir/note.cpp.o: /home/tima/gitForks/harmony-core/sources/note.cpp
sources/CMakeFiles/harmony-core.dir/note.cpp.o: sources/CMakeFiles/harmony-core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tima/gitForks/harmony-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sources/CMakeFiles/harmony-core.dir/note.cpp.o"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sources/CMakeFiles/harmony-core.dir/note.cpp.o -MF CMakeFiles/harmony-core.dir/note.cpp.o.d -o CMakeFiles/harmony-core.dir/note.cpp.o -c /home/tima/gitForks/harmony-core/sources/note.cpp

sources/CMakeFiles/harmony-core.dir/note.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/harmony-core.dir/note.cpp.i"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tima/gitForks/harmony-core/sources/note.cpp > CMakeFiles/harmony-core.dir/note.cpp.i

sources/CMakeFiles/harmony-core.dir/note.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/harmony-core.dir/note.cpp.s"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tima/gitForks/harmony-core/sources/note.cpp -o CMakeFiles/harmony-core.dir/note.cpp.s

sources/CMakeFiles/harmony-core.dir/accidental.cpp.o: sources/CMakeFiles/harmony-core.dir/flags.make
sources/CMakeFiles/harmony-core.dir/accidental.cpp.o: /home/tima/gitForks/harmony-core/sources/accidental.cpp
sources/CMakeFiles/harmony-core.dir/accidental.cpp.o: sources/CMakeFiles/harmony-core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tima/gitForks/harmony-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object sources/CMakeFiles/harmony-core.dir/accidental.cpp.o"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sources/CMakeFiles/harmony-core.dir/accidental.cpp.o -MF CMakeFiles/harmony-core.dir/accidental.cpp.o.d -o CMakeFiles/harmony-core.dir/accidental.cpp.o -c /home/tima/gitForks/harmony-core/sources/accidental.cpp

sources/CMakeFiles/harmony-core.dir/accidental.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/harmony-core.dir/accidental.cpp.i"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tima/gitForks/harmony-core/sources/accidental.cpp > CMakeFiles/harmony-core.dir/accidental.cpp.i

sources/CMakeFiles/harmony-core.dir/accidental.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/harmony-core.dir/accidental.cpp.s"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tima/gitForks/harmony-core/sources/accidental.cpp -o CMakeFiles/harmony-core.dir/accidental.cpp.s

sources/CMakeFiles/harmony-core.dir/octave.cpp.o: sources/CMakeFiles/harmony-core.dir/flags.make
sources/CMakeFiles/harmony-core.dir/octave.cpp.o: /home/tima/gitForks/harmony-core/sources/octave.cpp
sources/CMakeFiles/harmony-core.dir/octave.cpp.o: sources/CMakeFiles/harmony-core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tima/gitForks/harmony-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object sources/CMakeFiles/harmony-core.dir/octave.cpp.o"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sources/CMakeFiles/harmony-core.dir/octave.cpp.o -MF CMakeFiles/harmony-core.dir/octave.cpp.o.d -o CMakeFiles/harmony-core.dir/octave.cpp.o -c /home/tima/gitForks/harmony-core/sources/octave.cpp

sources/CMakeFiles/harmony-core.dir/octave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/harmony-core.dir/octave.cpp.i"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tima/gitForks/harmony-core/sources/octave.cpp > CMakeFiles/harmony-core.dir/octave.cpp.i

sources/CMakeFiles/harmony-core.dir/octave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/harmony-core.dir/octave.cpp.s"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tima/gitForks/harmony-core/sources/octave.cpp -o CMakeFiles/harmony-core.dir/octave.cpp.s

sources/CMakeFiles/harmony-core.dir/key.cpp.o: sources/CMakeFiles/harmony-core.dir/flags.make
sources/CMakeFiles/harmony-core.dir/key.cpp.o: /home/tima/gitForks/harmony-core/sources/key.cpp
sources/CMakeFiles/harmony-core.dir/key.cpp.o: sources/CMakeFiles/harmony-core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tima/gitForks/harmony-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object sources/CMakeFiles/harmony-core.dir/key.cpp.o"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT sources/CMakeFiles/harmony-core.dir/key.cpp.o -MF CMakeFiles/harmony-core.dir/key.cpp.o.d -o CMakeFiles/harmony-core.dir/key.cpp.o -c /home/tima/gitForks/harmony-core/sources/key.cpp

sources/CMakeFiles/harmony-core.dir/key.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/harmony-core.dir/key.cpp.i"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tima/gitForks/harmony-core/sources/key.cpp > CMakeFiles/harmony-core.dir/key.cpp.i

sources/CMakeFiles/harmony-core.dir/key.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/harmony-core.dir/key.cpp.s"
	cd /home/tima/gitForks/harmony-core/build/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tima/gitForks/harmony-core/sources/key.cpp -o CMakeFiles/harmony-core.dir/key.cpp.s

# Object files for target harmony-core
harmony__core_OBJECTS = \
"CMakeFiles/harmony-core.dir/note.cpp.o" \
"CMakeFiles/harmony-core.dir/accidental.cpp.o" \
"CMakeFiles/harmony-core.dir/octave.cpp.o" \
"CMakeFiles/harmony-core.dir/key.cpp.o"

# External object files for target harmony-core
harmony__core_EXTERNAL_OBJECTS =

sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/note.cpp.o
sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/accidental.cpp.o
sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/octave.cpp.o
sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/key.cpp.o
sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/build.make
sources/libharmony-core.a: sources/CMakeFiles/harmony-core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tima/gitForks/harmony-core/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libharmony-core.a"
	cd /home/tima/gitForks/harmony-core/build/sources && $(CMAKE_COMMAND) -P CMakeFiles/harmony-core.dir/cmake_clean_target.cmake
	cd /home/tima/gitForks/harmony-core/build/sources && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/harmony-core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sources/CMakeFiles/harmony-core.dir/build: sources/libharmony-core.a
.PHONY : sources/CMakeFiles/harmony-core.dir/build

sources/CMakeFiles/harmony-core.dir/clean:
	cd /home/tima/gitForks/harmony-core/build/sources && $(CMAKE_COMMAND) -P CMakeFiles/harmony-core.dir/cmake_clean.cmake
.PHONY : sources/CMakeFiles/harmony-core.dir/clean

sources/CMakeFiles/harmony-core.dir/depend:
	cd /home/tima/gitForks/harmony-core/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tima/gitForks/harmony-core /home/tima/gitForks/harmony-core/sources /home/tima/gitForks/harmony-core/build /home/tima/gitForks/harmony-core/build/sources /home/tima/gitForks/harmony-core/build/sources/CMakeFiles/harmony-core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sources/CMakeFiles/harmony-core.dir/depend

