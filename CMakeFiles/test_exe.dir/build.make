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
CMAKE_COMMAND = /snap/cmake/323/bin/cmake

# The command to remove a file.
RM = /snap/cmake/323/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sumit/resource_clones/sumon_vai/event

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sumit/resource_clones/sumon_vai/event

# Include any dependencies generated for this target.
include CMakeFiles/test_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_exe.dir/flags.make

CMakeFiles/test_exe.dir/avr_timer.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/avr_timer.cpp.o: avr_timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_exe.dir/avr_timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/avr_timer.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/avr_timer.cpp

CMakeFiles/test_exe.dir/avr_timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/avr_timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/avr_timer.cpp > CMakeFiles/test_exe.dir/avr_timer.cpp.i

CMakeFiles/test_exe.dir/avr_timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/avr_timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/avr_timer.cpp -o CMakeFiles/test_exe.dir/avr_timer.cpp.s

CMakeFiles/test_exe.dir/event.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/event.cpp.o: event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_exe.dir/event.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/event.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/event.cpp

CMakeFiles/test_exe.dir/event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/event.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/event.cpp > CMakeFiles/test_exe.dir/event.cpp.i

CMakeFiles/test_exe.dir/event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/event.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/event.cpp -o CMakeFiles/test_exe.dir/event.cpp.s

CMakeFiles/test_exe.dir/new.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/new.cpp.o: new.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_exe.dir/new.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/new.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/new.cpp

CMakeFiles/test_exe.dir/new.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/new.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/new.cpp > CMakeFiles/test_exe.dir/new.cpp.i

CMakeFiles/test_exe.dir/new.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/new.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/new.cpp -o CMakeFiles/test_exe.dir/new.cpp.s

CMakeFiles/test_exe.dir/test.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/test.cpp.o: test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_exe.dir/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/test.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/test.cpp

CMakeFiles/test_exe.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/test.cpp > CMakeFiles/test_exe.dir/test.cpp.i

CMakeFiles/test_exe.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/test.cpp -o CMakeFiles/test_exe.dir/test.cpp.s

CMakeFiles/test_exe.dir/test/test_framework.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/test/test_framework.cpp.o: test/test_framework.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_exe.dir/test/test_framework.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/test/test_framework.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/test/test_framework.cpp

CMakeFiles/test_exe.dir/test/test_framework.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/test/test_framework.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/test/test_framework.cpp > CMakeFiles/test_exe.dir/test/test_framework.cpp.i

CMakeFiles/test_exe.dir/test/test_framework.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/test/test_framework.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/test/test_framework.cpp -o CMakeFiles/test_exe.dir/test/test_framework.cpp.s

CMakeFiles/test_exe.dir/timer.cpp.o: CMakeFiles/test_exe.dir/flags.make
CMakeFiles/test_exe.dir/timer.cpp.o: timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test_exe.dir/timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_exe.dir/timer.cpp.o -c /home/sumit/resource_clones/sumon_vai/event/timer.cpp

CMakeFiles/test_exe.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_exe.dir/timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumit/resource_clones/sumon_vai/event/timer.cpp > CMakeFiles/test_exe.dir/timer.cpp.i

CMakeFiles/test_exe.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_exe.dir/timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumit/resource_clones/sumon_vai/event/timer.cpp -o CMakeFiles/test_exe.dir/timer.cpp.s

# Object files for target test_exe
test_exe_OBJECTS = \
"CMakeFiles/test_exe.dir/avr_timer.cpp.o" \
"CMakeFiles/test_exe.dir/event.cpp.o" \
"CMakeFiles/test_exe.dir/new.cpp.o" \
"CMakeFiles/test_exe.dir/test.cpp.o" \
"CMakeFiles/test_exe.dir/test/test_framework.cpp.o" \
"CMakeFiles/test_exe.dir/timer.cpp.o"

# External object files for target test_exe
test_exe_EXTERNAL_OBJECTS =

test_exe: CMakeFiles/test_exe.dir/avr_timer.cpp.o
test_exe: CMakeFiles/test_exe.dir/event.cpp.o
test_exe: CMakeFiles/test_exe.dir/new.cpp.o
test_exe: CMakeFiles/test_exe.dir/test.cpp.o
test_exe: CMakeFiles/test_exe.dir/test/test_framework.cpp.o
test_exe: CMakeFiles/test_exe.dir/timer.cpp.o
test_exe: CMakeFiles/test_exe.dir/build.make
test_exe: CMakeFiles/test_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sumit/resource_clones/sumon_vai/event/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable test_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_exe.dir/build: test_exe

.PHONY : CMakeFiles/test_exe.dir/build

CMakeFiles/test_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_exe.dir/clean

CMakeFiles/test_exe.dir/depend:
	cd /home/sumit/resource_clones/sumon_vai/event && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sumit/resource_clones/sumon_vai/event /home/sumit/resource_clones/sumon_vai/event /home/sumit/resource_clones/sumon_vai/event /home/sumit/resource_clones/sumon_vai/event /home/sumit/resource_clones/sumon_vai/event/CMakeFiles/test_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_exe.dir/depend

