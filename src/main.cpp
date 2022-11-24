#include <iostream>
#include "gui.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 600), "Hello World");
  window.setKeyRepeatEnabled(false);
  
  // // window.clear();
  // // game.draw_display();
  // // window.display();

  while (window.isOpen())
  {
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Green);
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

      window.clear();
      window.draw(shape);
      window.display();

  }

  std::cout << "Hello, World!" << std::endl;
  return 0;
}