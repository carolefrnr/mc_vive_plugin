# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/carole/src/mc_vive_plugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carole/src/mc_vive_plugin/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_controller.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_controller.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_controller.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_controller.dir/flags.make

tests/CMakeFiles/test_controller.dir/main.cpp.o: tests/CMakeFiles/test_controller.dir/flags.make
tests/CMakeFiles/test_controller.dir/main.cpp.o: ../tests/main.cpp
tests/CMakeFiles/test_controller.dir/main.cpp.o: tests/CMakeFiles/test_controller.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carole/src/mc_vive_plugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_controller.dir/main.cpp.o"
	cd /home/carole/src/mc_vive_plugin/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_controller.dir/main.cpp.o -MF CMakeFiles/test_controller.dir/main.cpp.o.d -o CMakeFiles/test_controller.dir/main.cpp.o -c /home/carole/src/mc_vive_plugin/tests/main.cpp

tests/CMakeFiles/test_controller.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_controller.dir/main.cpp.i"
	cd /home/carole/src/mc_vive_plugin/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carole/src/mc_vive_plugin/tests/main.cpp > CMakeFiles/test_controller.dir/main.cpp.i

tests/CMakeFiles/test_controller.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_controller.dir/main.cpp.s"
	cd /home/carole/src/mc_vive_plugin/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carole/src/mc_vive_plugin/tests/main.cpp -o CMakeFiles/test_controller.dir/main.cpp.s

# Object files for target test_controller
test_controller_OBJECTS = \
"CMakeFiles/test_controller.dir/main.cpp.o"

# External object files for target test_controller
test_controller_EXTERNAL_OBJECTS =

tests/test_controller: tests/CMakeFiles/test_controller.dir/main.cpp.o
tests/test_controller: tests/CMakeFiles/test_controller.dir/build.make
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_control.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_tasks.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_trajectory.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libeigen-quadprog.so.1.1.1
tests/test_controller: /home/carole/mc_rtc_install/lib/libstate-observation.so.1.4.1
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_solver.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_observers.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_rtc_gui.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_rbdyn.so.1.10.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_rtc_loader.so.1.10.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libltdl.so
tests/test_controller: /home/carole/mc_rtc_install/lib/libmc_rtc_utils.so.1.10.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libboost_stacktrace_backtrace.so.1.71.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libRBDynParsers.so.1.5.2
tests/test_controller: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so.0.6.2
tests/test_controller: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
tests/test_controller: /home/carole/mc_rtc_install/lib/libTasks.so.1.6.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libboost_timer.so.1.71.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libRBDyn.so.1.5.2
tests/test_controller: /home/carole/mc_rtc_install/lib/libsch-core.so.1.2.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.71.0
tests/test_controller: /home/carole/mc_rtc_install/lib/libeigen-qld.so.1.2.1
tests/test_controller: /home/carole/mc_rtc_install/lib/libeigen-lssol.so.1.0.0
tests/test_controller: /usr/lib/x86_64-linux-gnu/libgeos.so
tests/test_controller: /usr/lib/x86_64-linux-gnu/libnanomsg.so
tests/test_controller: tests/CMakeFiles/test_controller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carole/src/mc_vive_plugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_controller"
	cd /home/carole/src/mc_vive_plugin/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_controller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_controller.dir/build: tests/test_controller
.PHONY : tests/CMakeFiles/test_controller.dir/build

tests/CMakeFiles/test_controller.dir/clean:
	cd /home/carole/src/mc_vive_plugin/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_controller.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_controller.dir/clean

tests/CMakeFiles/test_controller.dir/depend:
	cd /home/carole/src/mc_vive_plugin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carole/src/mc_vive_plugin /home/carole/src/mc_vive_plugin/tests /home/carole/src/mc_vive_plugin/build /home/carole/src/mc_vive_plugin/build/tests /home/carole/src/mc_vive_plugin/build/tests/CMakeFiles/test_controller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_controller.dir/depend
