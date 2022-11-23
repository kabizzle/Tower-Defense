#include <SFML/Graphics.hpp>

int gui() {
    
  sf::RenderWindow window(sf::VideoMode(400, 600), "Hello World");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
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
  return 0;
}