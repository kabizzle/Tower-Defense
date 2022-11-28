#include <iostream>
#include "gui.hpp"

int main() {
  GUI gui;

  gui.init();
  gui.init_textures();
  gui.render();

  while (gui.running()) {
    gui.update();
  }
  std::cout << "Hello, World!" << std::endl;
  return 0;
}