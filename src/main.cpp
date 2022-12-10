#include <iostream>

#include "gui.hpp"

int main() {
  GUI gui;
  gui.init();

  while (gui.running()) {
    gui.update();
  }

  return 0;
}