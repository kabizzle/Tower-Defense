#include "gui.hpp"

GUI::GUI(sf::RenderWindow& window) : 
  m_window(window) { }

void GUI::draw_display() {
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  m_window.draw(shape);

  // while (m_window.isOpen())
  // {
  //     sf::Event event;
  //     while (m_window.pollEvent(event))
  //     {
  //         if (event.type == sf::Event::Closed)
  //             m_window.close();
  //     }

      // m_window.clear();
      // m_window.display();
  // }
}