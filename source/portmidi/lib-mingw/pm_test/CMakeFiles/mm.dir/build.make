# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 2.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\dev\SDK\CMake 2.8\bin\cmake.exe"

# The command to remove a file.
RM = "D:\dev\SDK\CMake 2.8\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "D:\dev\SDK\CMake 2.8\bin\cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\github\DarkGDK\source\portmidi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\github\DarkGDK\source\portmidi\lib-mingw

# Include any dependencies generated for this target.
include pm_test/CMakeFiles/mm.dir/depend.make

# Include the progress variables for this target.
include pm_test/CMakeFiles/mm.dir/progress.make

# Include the compile flags for this target's objects.
include pm_test/CMakeFiles/mm.dir/flags.make

pm_test/CMakeFiles/mm.dir/mm.c.obj: pm_test/CMakeFiles/mm.dir/flags.make
pm_test/CMakeFiles/mm.dir/mm.c.obj: pm_test/CMakeFiles/mm.dir/includes_C.rsp
pm_test/CMakeFiles/mm.dir/mm.c.obj: ../pm_test/mm.c
	$(CMAKE_COMMAND) -E cmake_progress_report D:\github\DarkGDK\source\portmidi\lib-mingw\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object pm_test/CMakeFiles/mm.dir/mm.c.obj"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\mm.dir\mm.c.obj   -c D:\github\DarkGDK\source\portmidi\pm_test\mm.c

pm_test/CMakeFiles/mm.dir/mm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mm.dir/mm.c.i"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E D:\github\DarkGDK\source\portmidi\pm_test\mm.c > CMakeFiles\mm.dir\mm.c.i

pm_test/CMakeFiles/mm.dir/mm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mm.dir/mm.c.s"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S D:\github\DarkGDK\source\portmidi\pm_test\mm.c -o CMakeFiles\mm.dir\mm.c.s

pm_test/CMakeFiles/mm.dir/mm.c.obj.requires:
.PHONY : pm_test/CMakeFiles/mm.dir/mm.c.obj.requires

pm_test/CMakeFiles/mm.dir/mm.c.obj.provides: pm_test/CMakeFiles/mm.dir/mm.c.obj.requires
	$(MAKE) -f pm_test\CMakeFiles\mm.dir\build.make pm_test/CMakeFiles/mm.dir/mm.c.obj.provides.build
.PHONY : pm_test/CMakeFiles/mm.dir/mm.c.obj.provides

pm_test/CMakeFiles/mm.dir/mm.c.obj.provides.build: pm_test/CMakeFiles/mm.dir/mm.c.obj

# Object files for target mm
mm_OBJECTS = \
"CMakeFiles/mm.dir/mm.c.obj"

# External object files for target mm
mm_EXTERNAL_OBJECTS =

pm_test/mm.exe: pm_test/CMakeFiles/mm.dir/mm.c.obj
pm_test/mm.exe: pm_test/CMakeFiles/mm.dir/build.make
pm_test/mm.exe: libportmidi_s.a
pm_test/mm.exe: pm_test/CMakeFiles/mm.dir/objects1.rsp
pm_test/mm.exe: pm_test/CMakeFiles/mm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable mm.exe"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pm_test/CMakeFiles/mm.dir/build: pm_test/mm.exe
.PHONY : pm_test/CMakeFiles/mm.dir/build

pm_test/CMakeFiles/mm.dir/requires: pm_test/CMakeFiles/mm.dir/mm.c.obj.requires
.PHONY : pm_test/CMakeFiles/mm.dir/requires

pm_test/CMakeFiles/mm.dir/clean:
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && $(CMAKE_COMMAND) -P CMakeFiles\mm.dir\cmake_clean.cmake
.PHONY : pm_test/CMakeFiles/mm.dir/clean

pm_test/CMakeFiles/mm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\github\DarkGDK\source\portmidi D:\github\DarkGDK\source\portmidi\pm_test D:\github\DarkGDK\source\portmidi\lib-mingw D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test\CMakeFiles\mm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : pm_test/CMakeFiles/mm.dir/depend
