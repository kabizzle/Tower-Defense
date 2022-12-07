#include "menustate.hpp"

MenuState::MenuState(GUI& gui, sf::RenderWindow& window)
    : State(gui, window),
      m_difficulty(Difficulty::Easy),
      m_selectedMap("./maps/map1.txt"),
      m_editing(false) {
  auto easyButton = m_gui.createButton("Easy", 60, 260);
  m_buttons[0] = easyButton;

  auto mediumButton = m_gui.createButton("Easy", 465, 260);
  m_buttons[1] = mediumButton;

  auto hardButton = m_gui.createButton("Easy", 870, 260);
  m_buttons[2] = hardButton;

  auto map1Button = m_gui.createButton("Map 1", 60, 420);
  m_buttons[3] = map1Button;

  auto map2Button = m_gui.createButton("Map 2", 465, 420);
  m_buttons[4] = map2Button;

  auto map3Button = m_gui.createButton("Map 3", 870, 420);
  m_buttons[5] = map3Button;

  auto editButton = m_gui.createButton("Edit level", 465, 580);
  m_buttons[6] = editButton;

  auto playButton = m_gui.createButton("Play now", 465, 740);
  m_buttons[7] = playButton;
}

void MenuState::PollEvents() {
  while (m_window.pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) m_window.close();

    if (this->m_event.type == sf::Event::MouseButtonPressed) {
      if (this->m_event.mouseButton.button == sf::Mouse::Left) {
        std::cout << "the left button was pressed" << std::endl;
        sf::Vector2f mouse =
            m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

        for (auto b : m_buttons) {
          if (!b.second->getGlobalBounds().contains(mouse)) continue;

          switch (b.first) {
            case 0:
              m_difficulty = Difficulty::Easy;
              m_buttons[0]->addHighlight();
              m_buttons[1]->removeHighlight();
              m_buttons[2]->removeHighlight();
              break;
            case 1:
              m_difficulty = Difficulty::Medium;
              m_buttons[1]->addHighlight();
              m_buttons[0]->removeHighlight();
              m_buttons[2]->removeHighlight();
              break;
            case 2:
              m_difficulty = Difficulty::Hard;
              m_buttons[2]->addHighlight();
              m_buttons[1]->removeHighlight();
              m_buttons[0]->removeHighlight();
              break;
            case 3:
              m_selectedMap = "./maps/map1.txt";
              m_buttons[3]->addHighlight();
              m_buttons[4]->removeHighlight();
              m_buttons[5]->removeHighlight();
              break;
            case 4:
              m_selectedMap = "./maps/map2.txt";
              m_buttons[4]->addHighlight();
              m_buttons[3]->removeHighlight();
              m_buttons[5]->removeHighlight();
              break;
            case 5:
              m_selectedMap = "./maps/map3.txt";
              m_buttons[5]->addHighlight();
              m_buttons[3]->removeHighlight();
              m_buttons[4]->removeHighlight();
              break;
            //case 6:
              // gui.currentState = EditorState(m_gui, m_window,
              // m_selectedMap)
            //case 7:
              // gui.currentState = GameState(m_gui, m_window, m_difficulty,
              // m_selectedMap); return; ???
          }
        }
      }
    }
  }
}

void MenuState::Draw() {
    // Draw menu background

    this->m_window.clear();
    this->m_window.draw(Renderables::getMenuBackgroundSprite());

    for (auto b : m_buttons) {
      b.second->drawButton(m_window);
    }

    this->m_window.display();
}

void MenuState::Run() {
  this->PollEvents();
  this->Draw();
}

MenuState::~MenuState() {
  for (auto b : m_buttons) {
    delete b.second;
  }
}