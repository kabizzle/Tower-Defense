/**
 * @file level_editor_test.cpp
 * @brief Used to test the LevelEditor class
 */

#include "../src/level_editor.hpp"

#include <iostream>

int main(void) {
  std::cout << "Testing default editor." << std::endl;
  LevelEditor editor = LevelEditor(30, 20);

  bool editResult;

  std::cout << "Editing tile (15, 8)" << std::endl;
  try {
    editResult = editor.Edit(std::make_pair(15, 8), 0);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Editing successful." << std::endl;
  } else {
    std::cout << "Editing failed." << std::endl;
  }

  std::cout << "Editing tile (14, 9)" << std::endl;
  try {
    editResult = editor.Edit(std::make_pair(14, 9), 2);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Editing successful." << std::endl;
  } else {
    std::cout << "Editing failed." << std::endl;
  }

  try {
    editResult = editor.Save("defaultTest");
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Saving successful." << std::endl;
  } else {
    std::cout << "Saving failed." << std::endl;
  }

  std::cout << "Default level editor tests complete." << std::endl << std::endl;

  std::cout << "Testing custom editor with testmap1." << std::endl;

  try {
    editor = LevelEditor(30, 20, "testmap1");
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 0;
  }

  std::cout << "Editing tile (0, 1)" << std::endl;
  try {
    editResult = editor.Edit(std::make_pair(0, 1), 0);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Editing successful." << std::endl;
  } else {
    std::cout << "Editing failed." << std::endl;
  }

  std::cout << "Editing tile (0, 0)" << std::endl;
  try {
    editResult = editor.Edit(std::make_pair(0, 0), 1);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Editing successful." << std::endl;
  } else {
    std::cout << "Editing failed." << std::endl;
  }

  std::cout << "Editing tile (1, 0)" << std::endl;
  try {
    editResult = editor.Edit(std::make_pair(1, 0), 2);
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Editing successful." << std::endl;
  } else {
    std::cout << "Editing failed." << std::endl;
  }

  try {
    editResult = editor.Save("customTest");
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  if (editResult) {
    std::cout << "Saving successful." << std::endl;
  } else {
    std::cout << "Saving failed." << std::endl;
  }

  std::cout << "Custom level editor tests complete." << std::endl;

  return 0;
}