#include <iostream>
#include "gui.hpp"

int main() {
  GUI gui;

  gui.init();
  gui.render();

  // gui.run();

  while (gui.running()) {
    gui.update();
  }
  std::cout << "Hello, World!" << std::endl;
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