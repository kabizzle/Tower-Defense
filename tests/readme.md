# Test files

It is a common practice to do unit tests of each class before you integrate it into the project to validate its operation.
In this folder, you can create your own unit test files to validate the operation of your components.

> It might be a good idea to also take some notes about the tests since you are required to 
  report these in the final report.

# Unit Tests


## Test of EnemyFactory

**Involved Classes:**
EnemyFactory, Assignment, Degree(TODO), Renderable

**Test File:**
enemy_factory_test.cpp

**Results:**
An initial check on first few rounds indicates that the logic works and no leaks were spotted using valgrind


## Test of The general logic and interactions between towers and enemies

**Involved Classes:**
Game, Map, all tower and enemy related classes

**Test File:**
text_based_test.cpp

**Results:**
Some bugs were found (mainly with loop conditions) but they were fixed.
After the fixes no memory leaks were found using valgrind.