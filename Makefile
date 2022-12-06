# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kabir/tower-defense-2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kabir/tower-defense-2

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kabir/tower-defense-2/CMakeFiles /home/kabir/tower-defense-2/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kabir/tower-defense-2/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tower-defense

# Build rule for target.
tower-defense: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tower-defense
.PHONY : tower-defense

# fast build rule for target.
tower-defense/fast:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/build
.PHONY : tower-defense/fast

src/assignment.o: src/assignment.cpp.o

.PHONY : src/assignment.o

# target to build an object file
src/assignment.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/assignment.cpp.o
.PHONY : src/assignment.cpp.o

src/assignment.i: src/assignment.cpp.i

.PHONY : src/assignment.i

# target to preprocess a source file
src/assignment.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/assignment.cpp.i
.PHONY : src/assignment.cpp.i

src/assignment.s: src/assignment.cpp.s

.PHONY : src/assignment.s

# target to generate assembly for a file
src/assignment.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/assignment.cpp.s
.PHONY : src/assignment.cpp.s

src/attacking_tower.o: src/attacking_tower.cpp.o

.PHONY : src/attacking_tower.o

# target to build an object file
src/attacking_tower.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/attacking_tower.cpp.o
.PHONY : src/attacking_tower.cpp.o

src/attacking_tower.i: src/attacking_tower.cpp.i

.PHONY : src/attacking_tower.i

# target to preprocess a source file
src/attacking_tower.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/attacking_tower.cpp.i
.PHONY : src/attacking_tower.cpp.i

src/attacking_tower.s: src/attacking_tower.cpp.s

.PHONY : src/attacking_tower.s

# target to generate assembly for a file
src/attacking_tower.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/attacking_tower.cpp.s
.PHONY : src/attacking_tower.cpp.s

src/degree.o: src/degree.cpp.o

.PHONY : src/degree.o

# target to build an object file
src/degree.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/degree.cpp.o
.PHONY : src/degree.cpp.o

src/degree.i: src/degree.cpp.i

.PHONY : src/degree.i

# target to preprocess a source file
src/degree.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/degree.cpp.i
.PHONY : src/degree.cpp.i

src/degree.s: src/degree.cpp.s

.PHONY : src/degree.s

# target to generate assembly for a file
src/degree.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/degree.cpp.s
.PHONY : src/degree.cpp.s

src/enemy_factory.o: src/enemy_factory.cpp.o

.PHONY : src/enemy_factory.o

# target to build an object file
src/enemy_factory.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/enemy_factory.cpp.o
.PHONY : src/enemy_factory.cpp.o

src/enemy_factory.i: src/enemy_factory.cpp.i

.PHONY : src/enemy_factory.i

# target to preprocess a source file
src/enemy_factory.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/enemy_factory.cpp.i
.PHONY : src/enemy_factory.cpp.i

src/enemy_factory.s: src/enemy_factory.cpp.s

.PHONY : src/enemy_factory.s

# target to generate assembly for a file
src/enemy_factory.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/enemy_factory.cpp.s
.PHONY : src/enemy_factory.cpp.s

src/game.o: src/game.cpp.o

.PHONY : src/game.o

# target to build an object file
src/game.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/game.cpp.o
.PHONY : src/game.cpp.o

src/game.i: src/game.cpp.i

.PHONY : src/game.i

# target to preprocess a source file
src/game.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/game.cpp.i
.PHONY : src/game.cpp.i

src/game.s: src/game.cpp.s

.PHONY : src/game.s

# target to generate assembly for a file
src/game.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/game.cpp.s
.PHONY : src/game.cpp.s

src/gui.o: src/gui.cpp.o

.PHONY : src/gui.o

# target to build an object file
src/gui.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/gui.cpp.o
.PHONY : src/gui.cpp.o

src/gui.i: src/gui.cpp.i

.PHONY : src/gui.i

# target to preprocess a source file
src/gui.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/gui.cpp.i
.PHONY : src/gui.cpp.i

src/gui.s: src/gui.cpp.s

.PHONY : src/gui.s

# target to generate assembly for a file
src/gui.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/gui.cpp.s
.PHONY : src/gui.cpp.s

src/level_editor.o: src/level_editor.cpp.o

.PHONY : src/level_editor.o

# target to build an object file
src/level_editor.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/level_editor.cpp.o
.PHONY : src/level_editor.cpp.o

src/level_editor.i: src/level_editor.cpp.i

.PHONY : src/level_editor.i

# target to preprocess a source file
src/level_editor.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/level_editor.cpp.i
.PHONY : src/level_editor.cpp.i

src/level_editor.s: src/level_editor.cpp.s

.PHONY : src/level_editor.s

# target to generate assembly for a file
src/level_editor.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/level_editor.cpp.s
.PHONY : src/level_editor.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/map.o: src/map.cpp.o

.PHONY : src/map.o

# target to build an object file
src/map.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/map.cpp.o
.PHONY : src/map.cpp.o

src/map.i: src/map.cpp.i

.PHONY : src/map.i

# target to preprocess a source file
src/map.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/map.cpp.i
.PHONY : src/map.cpp.i

src/map.s: src/map.cpp.s

.PHONY : src/map.s

# target to generate assembly for a file
src/map.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/map.cpp.s
.PHONY : src/map.cpp.s

src/renderable.o: src/renderable.cpp.o

.PHONY : src/renderable.o

# target to build an object file
src/renderable.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/renderable.cpp.o
.PHONY : src/renderable.cpp.o

src/renderable.i: src/renderable.cpp.i

.PHONY : src/renderable.i

# target to preprocess a source file
src/renderable.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/renderable.cpp.i
.PHONY : src/renderable.cpp.i

src/renderable.s: src/renderable.cpp.s

.PHONY : src/renderable.s

# target to generate assembly for a file
src/renderable.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/renderable.cpp.s
.PHONY : src/renderable.cpp.s

src/support_towers.o: src/support_towers.cpp.o

.PHONY : src/support_towers.o

# target to build an object file
src/support_towers.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/support_towers.cpp.o
.PHONY : src/support_towers.cpp.o

src/support_towers.i: src/support_towers.cpp.i

.PHONY : src/support_towers.i

# target to preprocess a source file
src/support_towers.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/support_towers.cpp.i
.PHONY : src/support_towers.cpp.i

src/support_towers.s: src/support_towers.cpp.s

.PHONY : src/support_towers.s

# target to generate assembly for a file
src/support_towers.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/support_towers.cpp.s
.PHONY : src/support_towers.cpp.s

src/tower.o: src/tower.cpp.o

.PHONY : src/tower.o

# target to build an object file
src/tower.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/tower.cpp.o
.PHONY : src/tower.cpp.o

src/tower.i: src/tower.cpp.i

.PHONY : src/tower.i

# target to preprocess a source file
src/tower.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/tower.cpp.i
.PHONY : src/tower.cpp.i

src/tower.s: src/tower.cpp.s

.PHONY : src/tower.s

# target to generate assembly for a file
src/tower.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/tower.cpp.s
.PHONY : src/tower.cpp.s

src/utils.o: src/utils.cpp.o

.PHONY : src/utils.o

# target to build an object file
src/utils.cpp.o:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/utils.cpp.o
.PHONY : src/utils.cpp.o

src/utils.i: src/utils.cpp.i

.PHONY : src/utils.i

# target to preprocess a source file
src/utils.cpp.i:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/utils.cpp.i
.PHONY : src/utils.cpp.i

src/utils.s: src/utils.cpp.s

.PHONY : src/utils.s

# target to generate assembly for a file
src/utils.cpp.s:
	$(MAKE) -f CMakeFiles/tower-defense.dir/build.make CMakeFiles/tower-defense.dir/src/utils.cpp.s
.PHONY : src/utils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... tower-defense"
	@echo "... src/assignment.o"
	@echo "... src/assignment.i"
	@echo "... src/assignment.s"
	@echo "... src/attacking_tower.o"
	@echo "... src/attacking_tower.i"
	@echo "... src/attacking_tower.s"
	@echo "... src/degree.o"
	@echo "... src/degree.i"
	@echo "... src/degree.s"
	@echo "... src/enemy_factory.o"
	@echo "... src/enemy_factory.i"
	@echo "... src/enemy_factory.s"
	@echo "... src/game.o"
	@echo "... src/game.i"
	@echo "... src/game.s"
	@echo "... src/gui.o"
	@echo "... src/gui.i"
	@echo "... src/gui.s"
	@echo "... src/level_editor.o"
	@echo "... src/level_editor.i"
	@echo "... src/level_editor.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/map.o"
	@echo "... src/map.i"
	@echo "... src/map.s"
	@echo "... src/renderable.o"
	@echo "... src/renderable.i"
	@echo "... src/renderable.s"
	@echo "... src/support_towers.o"
	@echo "... src/support_towers.i"
	@echo "... src/support_towers.s"
	@echo "... src/tower.o"
	@echo "... src/tower.i"
	@echo "... src/tower.s"
	@echo "... src/utils.o"
	@echo "... src/utils.i"
	@echo "... src/utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

