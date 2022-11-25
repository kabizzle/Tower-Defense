#include <iostream>
#include "gui.hpp"

int main() {
  GUI gui;

  gui.init();
  gui.render();

  while (gui.running()) {
  //   while (window.pollEvent(event))
  //   {
  //       if (event.type == sf::Event::Closed)
  //           window.close();
  //   }

  //     window.clear();
  //     window.draw(shape);
  //     window.display();

  // }
    gui.update();

  }
  std::cout << "Hello, World!" << std::endl;
  return 0;
}