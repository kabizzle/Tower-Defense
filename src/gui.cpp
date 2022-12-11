#include "gui.hpp"

#include <iostream>

#include "button.hpp"

#include "states/state.hpp"
#include "states/menustate.hpp"
#include "states/endstate.hpp"

GUI::GUI() : m_renderables(new Renderables()) {}

GUI::~GUI() {
  delete m_renderables;
  if(m_window) {
    delete m_window;
  }
  this->Priv_DeleteState();
}

void GUI::init() {
  this->m_videoMode.height = 720;
  this->m_videoMode.width = 1280;
  this->m_window = new sf::RenderWindow(this->m_videoMode, "test window", sf::Style::Close);
  this->m_window->setFramerateLimit(60);
  this->m_window->setPosition(sf::Vector2i(0, 30));
  this->start = sf::Vector2f(100, 200);
  this->m_state = new MenuState(*this, *this->m_window);
  this->m_new_state = nullptr;
  this->m_font.loadFromFile("SpaceMono-Regular.ttf");
}

bool GUI::running() { return this->m_window->isOpen(); }

Button* GUI::CreateButton(std::string text, int32_t x, int32_t y) {
  Button* button = new Button(text, x, y, m_font);
  return button;
}

TowerButton* GUI::CreateTowerButton(TowerType type, int32_t x, int32_t y) {
  TowerButton* towerButton = new TowerButton(type, x, y, m_font);
  return towerButton;
}

void GUI::update() {
  if (this->m_new_state){
    this->Priv_DeleteState();
    this->m_state = this->m_new_state;
    this->m_new_state = nullptr;
  }

  this->m_state->Run();
}

const sf::Font& GUI::GetFont() const {
  return m_font;
}

void GUI::ChangeState(State* state) {
  this->m_new_state = state;
}


void GUI::Priv_DeleteState() {
  if (this->m_state) {
    delete this->m_state;
  }
}