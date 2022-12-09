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

/**
 * Game state variable - current_state
 * while window is open:
 *  call current_state.run()
 *
 *
 * -- inside current state
 * --
 *
 */