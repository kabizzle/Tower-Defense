#include "gui.hpp"

#include <iostream>

#include "button.hpp"

#include "states/state.hpp"
#include "states/menustate.hpp"

GUI::GUI() : m_renderables(new Renderables()) {}

GUI::~GUI() {
  delete this->m_window;
  delete this->m_renderables;
  delete this->m_state;

}

void GUI::init() {
  this->m_videoMode.height = 720;
  this->m_videoMode.width = 1280;
  this->m_window = new sf::RenderWindow(this->m_videoMode, "test window", sf::Style::Close);
  this->m_window->setFramerateLimit(60);
  this->start = sf::Vector2f(100, 200);
  this->m_state = new MenuState(*this, *this->m_window);
}

bool GUI::running() { return this->m_window->isOpen(); }

void GUI::pollEvents() {
  while (this->m_window->pollEvent(this->m_event)) {
    if (this->m_event.type == sf::Event::Closed) this->m_window->close();

    if (this->m_event.type == sf::Event::MouseButtonPressed) {
      if (this->m_event.mouseButton.button == sf::Mouse::Right) {
        std::cout << "the right button was pressed" << std::endl;
        std::cout << "mouse x: " << this->m_event.mouseButton.x << std::endl;
        std::cout << "mouse y: " << this->m_event.mouseButton.y << std::endl;
      }
    }
  }
}

// void GUI::addEnemy(std::string type, sf::Vector2f pos) {

//   // if (this->textures_map.find(type) != this->textures_map.end()){
//   //   if (!this->texture.loadFromFile(this->textures_map[type])) {
//   //     std::cout << "Error: Image not found" << std::endl;
//   //     return;
//   //   }
//   //   sf::Sprite enemy(this->texture);
//   //   enemy.setPosition(pos);
//   //   this->enemies.push_back(enemy);
//   // }
//   // else {
//   //   std::cout << "Texture does not exist" << std::endl;
//   //   return;
//   // }
//   // // this->m_window->draw(enemy);
// }

void GUI::moveEnemies() {
  for (auto enemy = this->enemies.begin(); enemy != this->enemies.end();
       enemy++) {
    sf::Vector2f position = enemy->getPosition();
    if (position.x < 0 || position.x > 1280 - 20) this->x_velo *= -1;
    // if (position.y < 0 || position.y > 720 - 20) this->y_velo *= -1;
    position.x += this->x_velo;
    // position.y += this->y_velo;

    enemy->setPosition(position);
  }
}

Button* GUI::createButton(std::string text, int x, int y) {
  Button* button = new Button(text, x, y);
  return button;
}

void GUI::update() {
  // this->pollEvents();

  // // clear window
  // this->m_window->clear();

  // // draw changes
  // this->m_window->draw(Renderables::getDoctor1Sprite());
  // // this->moveEnemies();
  // for (auto enemy = this->enemies.begin(); enemy != this->enemies.end();
  //      enemy++) {
  //   this->m_window->draw(*enemy);
  // }

  // // display window
  // this->m_window->display();
  this->m_state->Run();
}