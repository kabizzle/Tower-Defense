#include "gui.hpp"

GUI::GUI() {}

GUI::~GUI() {
  delete this->m_window;
}


void GUI::init() {
  this->m_window = nullptr;
  this->m_videoMode.height = 720;
  this->m_videoMode.width = 1280;
}


bool GUI::running() {
  return this->m_window->isOpen();
}


void GUI::pollEvents() {
  while (this->m_window->pollEvent(this->m_event)) {
    if (this->m_event.type == sf::Event::Closed)
      this->m_window->close();
  }
}


void GUI::render() {
  this->m_window = new sf::RenderWindow(this->m_videoMode, "test window", sf::Style::Close);
  this->m_window->setFramerateLimit(60);
  this->addEnemy();

  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Green);

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


void GUI::addEnemy() {
  sf::RectangleShape enemy;
  enemy.setSize(sf::Vector2f(100, 100));
  enemy.setPosition(sf::Vector2f(200, 200));
  // this->m_window->draw(enemy);
  this->enemies.push_back(enemy);
}

void GUI::moveEnemies() {
  for (std::vector<sf::RectangleShape>::iterator enemy = this->enemies.begin(); enemy != this->enemies.end(); enemy++){
    sf::Vector2f position = enemy->getPosition();
    if (position.x < 0 || position.x > 1280 - 100) this->x_velo *= -1; 
    if (position.y < 0 || position.y > 720 - 100) this->y_velo *= -1;
    position.x += this->x_velo;
    position.y += this->y_velo;

    enemy->setPosition(position);
  }
}


void GUI::update() {

  this->pollEvents();

  // this->addEnemy();

  // clear window
  this->m_window->clear();

  // draw changes

    this->moveEnemies();
    for (std::vector<sf::RectangleShape>::iterator enemy = this->enemies.begin(); enemy != this->enemies.end(); enemy++){
      this->m_window->draw(*enemy);
    }


  // display window
  this->m_window->display();
}