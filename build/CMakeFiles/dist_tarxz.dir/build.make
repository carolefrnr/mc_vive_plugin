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

# Utility rule file for dist_tarxz.

# Include any custom commands dependencies for this target.
include CMakeFiles/dist_tarxz.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dist_tarxz.dir/progress.make

CMakeFiles/dist_tarxz:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/carole/src/mc_vive_plugin/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating tar.xz tarball and its signature..."
	/usr/bin/tar -cJf VivePlugin-0.0.1.tar.xz VivePlugin-0.0.1/ && /usr/bin/gpg --detach-sign --armor -o /home/carole/src/mc_vive_plugin/build/VivePlugin-0.0.1.tar.xz.sig /home/carole/src/mc_vive_plugin/build/VivePlugin-0.0.1.tar.xz

dist_tarxz: CMakeFiles/dist_tarxz
dist_tarxz: CMakeFiles/dist_tarxz.dir/build.make
.PHONY : dist_tarxz

# Rule to build all files generated by this target.
CMakeFiles/dist_tarxz.dir/build: dist_tarxz
.PHONY : CMakeFiles/dist_tarxz.dir/build

CMakeFiles/dist_tarxz.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dist_tarxz.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dist_tarxz.dir/clean

CMakeFiles/dist_tarxz.dir/depend:
	cd /home/carole/src/mc_vive_plugin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carole/src/mc_vive_plugin /home/carole/src/mc_vive_plugin /home/carole/src/mc_vive_plugin/build /home/carole/src/mc_vive_plugin/build /home/carole/src/mc_vive_plugin/build/CMakeFiles/dist_tarxz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dist_tarxz.dir/depend

