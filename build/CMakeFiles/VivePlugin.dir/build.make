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
include CMakeFiles/VivePlugin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VivePlugin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VivePlugin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VivePlugin.dir/flags.make

CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o: CMakeFiles/VivePlugin.dir/flags.make
CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o: ../src/VivePlugin.cpp
CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o: CMakeFiles/VivePlugin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carole/src/mc_vive_plugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o -MF CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o.d -o CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o -c /home/carole/src/mc_vive_plugin/src/VivePlugin.cpp

CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carole/src/mc_vive_plugin/src/VivePlugin.cpp > CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.i

CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carole/src/mc_vive_plugin/src/VivePlugin.cpp -o CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.s

# Object files for target VivePlugin
VivePlugin_OBJECTS = \
"CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o"

# External object files for target VivePlugin
VivePlugin_EXTERNAL_OBJECTS =

VivePlugin.so: CMakeFiles/VivePlugin.dir/src/VivePlugin.cpp.o
VivePlugin.so: CMakeFiles/VivePlugin.dir/build.make
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_control.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_tasks.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_trajectory.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libeigen-quadprog.so.1.1.1
VivePlugin.so: /home/carole/mc_rtc_install/lib/libstate-observation.so.1.4.1
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_solver.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_observers.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_rtc_gui.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_rbdyn.so.1.10.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_rtc_loader.so.1.10.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libltdl.so
VivePlugin.so: /home/carole/mc_rtc_install/lib/libmc_rtc_utils.so.1.10.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libboost_stacktrace_backtrace.so.1.71.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libRBDynParsers.so.1.5.2
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so.0.6.2
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libtinyxml2.so
VivePlugin.so: /home/carole/mc_rtc_install/lib/libTasks.so.1.6.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libboost_timer.so.1.71.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libRBDyn.so.1.5.2
VivePlugin.so: /home/carole/mc_rtc_install/lib/libsch-core.so.1.2.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.71.0
VivePlugin.so: /home/carole/mc_rtc_install/lib/libeigen-qld.so.1.2.1
VivePlugin.so: /home/carole/mc_rtc_install/lib/libeigen-lssol.so.1.0.0
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libgeos.so
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libnanomsg.so
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libopenvr_api.so
VivePlugin.so: /usr/lib/x86_64-linux-gnu/libdl.so
VivePlugin.so: CMakeFiles/VivePlugin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carole/src/mc_vive_plugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library VivePlugin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VivePlugin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VivePlugin.dir/build: VivePlugin.so
.PHONY : CMakeFiles/VivePlugin.dir/build

CMakeFiles/VivePlugin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VivePlugin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VivePlugin.dir/clean

CMakeFiles/VivePlugin.dir/depend:
	cd /home/carole/src/mc_vive_plugin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carole/src/mc_vive_plugin /home/carole/src/mc_vive_plugin /home/carole/src/mc_vive_plugin/build /home/carole/src/mc_vive_plugin/build /home/carole/src/mc_vive_plugin/build/CMakeFiles/VivePlugin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VivePlugin.dir/depend

