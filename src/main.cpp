#include <iostream>

#include "gui.hpp"

int main() {
  GUI gui;
  gui.init();

  while (gui.running()) {
    gui.update();
  }
  std::cout << "Closing the software." << std::endl;
  return 0;
}