# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mk/OSlabs/OSlabs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mk/OSlabs/OSlabs/build

# Include any dependencies generated for this target.
include CMakeFiles/os.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/os.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/os.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/os.dir/flags.make

CMakeFiles/os.dir/src/ChildOne.c.o: CMakeFiles/os.dir/flags.make
CMakeFiles/os.dir/src/ChildOne.c.o: /Users/mk/OSlabs/OSlabs/src/ChildOne.c
CMakeFiles/os.dir/src/ChildOne.c.o: CMakeFiles/os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mk/OSlabs/OSlabs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/os.dir/src/ChildOne.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/os.dir/src/ChildOne.c.o -MF CMakeFiles/os.dir/src/ChildOne.c.o.d -o CMakeFiles/os.dir/src/ChildOne.c.o -c /Users/mk/OSlabs/OSlabs/src/ChildOne.c

CMakeFiles/os.dir/src/ChildOne.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/os.dir/src/ChildOne.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/OSlabs/OSlabs/src/ChildOne.c > CMakeFiles/os.dir/src/ChildOne.c.i

CMakeFiles/os.dir/src/ChildOne.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/os.dir/src/ChildOne.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/OSlabs/OSlabs/src/ChildOne.c -o CMakeFiles/os.dir/src/ChildOne.c.s

CMakeFiles/os.dir/src/ChildTwo.c.o: CMakeFiles/os.dir/flags.make
CMakeFiles/os.dir/src/ChildTwo.c.o: /Users/mk/OSlabs/OSlabs/src/ChildTwo.c
CMakeFiles/os.dir/src/ChildTwo.c.o: CMakeFiles/os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mk/OSlabs/OSlabs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/os.dir/src/ChildTwo.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/os.dir/src/ChildTwo.c.o -MF CMakeFiles/os.dir/src/ChildTwo.c.o.d -o CMakeFiles/os.dir/src/ChildTwo.c.o -c /Users/mk/OSlabs/OSlabs/src/ChildTwo.c

CMakeFiles/os.dir/src/ChildTwo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/os.dir/src/ChildTwo.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/OSlabs/OSlabs/src/ChildTwo.c > CMakeFiles/os.dir/src/ChildTwo.c.i

CMakeFiles/os.dir/src/ChildTwo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/os.dir/src/ChildTwo.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/OSlabs/OSlabs/src/ChildTwo.c -o CMakeFiles/os.dir/src/ChildTwo.c.s

CMakeFiles/os.dir/src/Parent.c.o: CMakeFiles/os.dir/flags.make
CMakeFiles/os.dir/src/Parent.c.o: /Users/mk/OSlabs/OSlabs/src/Parent.c
CMakeFiles/os.dir/src/Parent.c.o: CMakeFiles/os.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mk/OSlabs/OSlabs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/os.dir/src/Parent.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/os.dir/src/Parent.c.o -MF CMakeFiles/os.dir/src/Parent.c.o.d -o CMakeFiles/os.dir/src/Parent.c.o -c /Users/mk/OSlabs/OSlabs/src/Parent.c

CMakeFiles/os.dir/src/Parent.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/os.dir/src/Parent.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mk/OSlabs/OSlabs/src/Parent.c > CMakeFiles/os.dir/src/Parent.c.i

CMakeFiles/os.dir/src/Parent.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/os.dir/src/Parent.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mk/OSlabs/OSlabs/src/Parent.c -o CMakeFiles/os.dir/src/Parent.c.s

# Object files for target os
os_OBJECTS = \
"CMakeFiles/os.dir/src/ChildOne.c.o" \
"CMakeFiles/os.dir/src/ChildTwo.c.o" \
"CMakeFiles/os.dir/src/Parent.c.o"

# External object files for target os
os_EXTERNAL_OBJECTS =

os: CMakeFiles/os.dir/src/ChildOne.c.o
os: CMakeFiles/os.dir/src/ChildTwo.c.o
os: CMakeFiles/os.dir/src/Parent.c.o
os: CMakeFiles/os.dir/build.make
os: CMakeFiles/os.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mk/OSlabs/OSlabs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable os"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/os.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/os.dir/build: os
.PHONY : CMakeFiles/os.dir/build

CMakeFiles/os.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/os.dir/cmake_clean.cmake
.PHONY : CMakeFiles/os.dir/clean

CMakeFiles/os.dir/depend:
	cd /Users/mk/OSlabs/OSlabs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mk/OSlabs/OSlabs /Users/mk/OSlabs/OSlabs /Users/mk/OSlabs/OSlabs/build /Users/mk/OSlabs/OSlabs/build /Users/mk/OSlabs/OSlabs/build/CMakeFiles/os.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/os.dir/depend

