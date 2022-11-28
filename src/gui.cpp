#include <iostream>
#include "gui.hpp"


GUI::GUI() {}

GUI::~GUI() {
  delete this->m_window;
}


void GUI::init() {
  this->m_window = nullptr;
  this->m_videoMode.height = 720;
  this->m_videoMode.width = 1280;
  this->start = sf::Vector2f(100, 200);
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
  this->addEnemy("bachelor_2", this->start);
  sf::Vector2f pos = this->start;
  pos.x += 200;
  this->addEnemy("doctor", pos);

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

void GUI::init_textures() {

  this->textures_map["bachelor_3"] = "src/images/bachelor_upgraded_twice.png";
  this->textures_map["bachelor_2"] = "src/images/bachelor_upgraded.png";
  this->textures_map["doctor"] = "src/images/doctor.png";
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
  // this->textures_map.insert();
}


void GUI::addEnemy(std::string type, sf::Vector2f pos) {
  // if (!this->texture.loadFromFile("src/images/bachelor.png")) {
  //   std::cout << "Error: Image not found" << std::endl;
  //   return;
  // }
  
  if (this->textures_map.find(type) != this->textures_map.end()){
    if (!this->texture.loadFromFile(this->textures_map[type])) {
      std::cout << "Error: Image not found" << std::endl; 
      return;
    }
    sf::Sprite enemy(this->texture);
    enemy.setPosition(pos);
    this->enemies.push_back(enemy);
  }
  else {
    std::cout << "Texture does not exist" << std::endl;
    return;
  }
  // this->m_window->draw(enemy);
}

void GUI::moveEnemies() {
  for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); enemy++){
    sf::Vector2f position = enemy->getPosition();
    if (position.x < 0 || position.x > 1280 - 20) this->x_velo *= -1; 
    // if (position.y < 0 || position.y > 720 - 20) this->y_velo *= -1;
    position.x += this->x_velo;
    // position.y += this->y_velo;

    enemy->setPosition(position);
  }
}


void GUI::update() {

  this->pollEvents();

  // this->addEnemy();

  // clear window
  this->m_window->clear();

  // draw changes

    // this->moveEnemies();
    for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); enemy++){
      this->m_window->draw(*enemy);
    }


  // display window
  this->m_window->display();
}