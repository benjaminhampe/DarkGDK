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
include pm_test/CMakeFiles/midithru.dir/depend.make

# Include the progress variables for this target.
include pm_test/CMakeFiles/midithru.dir/progress.make

# Include the compile flags for this target's objects.
include pm_test/CMakeFiles/midithru.dir/flags.make

pm_test/CMakeFiles/midithru.dir/midithru.c.obj: pm_test/CMakeFiles/midithru.dir/flags.make
pm_test/CMakeFiles/midithru.dir/midithru.c.obj: pm_test/CMakeFiles/midithru.dir/includes_C.rsp
pm_test/CMakeFiles/midithru.dir/midithru.c.obj: ../pm_test/midithru.c
	$(CMAKE_COMMAND) -E cmake_progress_report D:\github\DarkGDK\source\portmidi\lib-mingw\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object pm_test/CMakeFiles/midithru.dir/midithru.c.obj"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\midithru.dir\midithru.c.obj   -c D:\github\DarkGDK\source\portmidi\pm_test\midithru.c

pm_test/CMakeFiles/midithru.dir/midithru.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/midithru.dir/midithru.c.i"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E D:\github\DarkGDK\source\portmidi\pm_test\midithru.c > CMakeFiles\midithru.dir\midithru.c.i

pm_test/CMakeFiles/midithru.dir/midithru.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/midithru.dir/midithru.c.s"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && D:\dev\SDK\mingw-32-tdm\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S D:\github\DarkGDK\source\portmidi\pm_test\midithru.c -o CMakeFiles\midithru.dir\midithru.c.s

pm_test/CMakeFiles/midithru.dir/midithru.c.obj.requires:
.PHONY : pm_test/CMakeFiles/midithru.dir/midithru.c.obj.requires

pm_test/CMakeFiles/midithru.dir/midithru.c.obj.provides: pm_test/CMakeFiles/midithru.dir/midithru.c.obj.requires
	$(MAKE) -f pm_test\CMakeFiles\midithru.dir\build.make pm_test/CMakeFiles/midithru.dir/midithru.c.obj.provides.build
.PHONY : pm_test/CMakeFiles/midithru.dir/midithru.c.obj.provides

pm_test/CMakeFiles/midithru.dir/midithru.c.obj.provides.build: pm_test/CMakeFiles/midithru.dir/midithru.c.obj

# Object files for target midithru
midithru_OBJECTS = \
"CMakeFiles/midithru.dir/midithru.c.obj"

# External object files for target midithru
midithru_EXTERNAL_OBJECTS =

pm_test/midithru.exe: pm_test/CMakeFiles/midithru.dir/midithru.c.obj
pm_test/midithru.exe: pm_test/CMakeFiles/midithru.dir/build.make
pm_test/midithru.exe: libportmidi_s.a
pm_test/midithru.exe: pm_test/CMakeFiles/midithru.dir/objects1.rsp
pm_test/midithru.exe: pm_test/CMakeFiles/midithru.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable midithru.exe"
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\midithru.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pm_test/CMakeFiles/midithru.dir/build: pm_test/midithru.exe
.PHONY : pm_test/CMakeFiles/midithru.dir/build

pm_test/CMakeFiles/midithru.dir/requires: pm_test/CMakeFiles/midithru.dir/midithru.c.obj.requires
.PHONY : pm_test/CMakeFiles/midithru.dir/requires

pm_test/CMakeFiles/midithru.dir/clean:
	cd /d D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test && $(CMAKE_COMMAND) -P CMakeFiles\midithru.dir\cmake_clean.cmake
.PHONY : pm_test/CMakeFiles/midithru.dir/clean

pm_test/CMakeFiles/midithru.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\github\DarkGDK\source\portmidi D:\github\DarkGDK\source\portmidi\pm_test D:\github\DarkGDK\source\portmidi\lib-mingw D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test D:\github\DarkGDK\source\portmidi\lib-mingw\pm_test\CMakeFiles\midithru.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : pm_test/CMakeFiles/midithru.dir/depend
