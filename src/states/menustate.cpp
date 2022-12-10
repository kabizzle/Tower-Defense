#include "menustate.hpp"

#include "editorstate.hpp"
#include "gamestate.hpp"

MenuState::MenuState(GUI& gui, sf::RenderWindow& window)
    : State(gui, window),
      m_difficulty(Difficulty::Easy),
      m_selectedMap("src/maps/map1.txt"),
      m_editing(false) {
  // Create buttons
  m_buttons[0] = m_gui.CreateButton("Easy", 60, 260);
  m_buttons[0]->addHighlight();  // Highlight default selection
  m_buttons[1] = m_gui.CreateButton("Medium", 465, 260);
  m_buttons[2] = m_gui.CreateButton("Hard", 870, 260);
  m_buttons[3] = m_gui.CreateButton("Map 1", 60, 360);
  m_buttons[3]->addHighlight();  // Highlight default selection
  m_buttons[4] = m_gui.CreateButton("Map 2", 465, 360);
  m_buttons[5] = m_gui.CreateButton("Map 3", 870, 360);
  m_buttons[6] = m_gui.CreateButton("Edit map", 465, 460);
  m_buttons[7] = m_gui.CreateButton("Play now", 465, 560);

  // Create text boxes
  sf::Text titleText, subtitleText, difficultyText, mapText;
  titleText.setFont(m_gui.GetFont());
  titleText.setFillColor(sf::Color::White);
  titleText.setString("Wave University - Defend your deadline 1.0");
  titleText.setCharacterSize(48);
  titleText.setPosition((window.getSize().x / 2) - (43 * 14), 30);
  m_texts.push_back(titleText);

  subtitleText.setFont(m_gui.GetFont());
  subtitleText.setFillColor(sf::Color::White);
  subtitleText.setString("Tower defense game. Beat as many waves as you can.");
  subtitleText.setCharacterSize(30);
  subtitleText.setPosition((window.getSize().x / 2) - (50 * 9), 130);
  m_texts.push_back(subtitleText);

  difficultyText.setFont(m_gui.GetFont());
  difficultyText.setFillColor(sf::Color::White);
  difficultyText.setString("Select the difficulty");
  difficultyText.setCharacterSize(24);
  difficultyText.setPosition(60, 220);
  m_texts.push_back(difficultyText);

  mapText.setFont(m_gui.GetFont());
  mapText.setFillColor(sf::Color::White);
  mapText.setString("Select the map");
  mapText.setCharacterSize(24);
  mapText.setPosition(60, 320);
  m_texts.push_back(mapText);
}

void MenuState::PollEvents() {
  while (m_window.pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) m_window.close();

    if (this->m_event.type == sf::Event::MouseButtonPressed) {
      if (this->m_event.mouseButton.button == sf::Mouse::Left) {
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
              Renderables::getSelectSound().play();
              break;
            case 1:
              m_difficulty = Difficulty::Medium;
              m_buttons[1]->addHighlight();
              m_buttons[0]->removeHighlight();
              m_buttons[2]->removeHighlight();
              Renderables::getSelectSound().play();
              break;
            case 2:
              m_difficulty = Difficulty::Hard;
              m_buttons[2]->addHighlight();
              m_buttons[1]->removeHighlight();
              m_buttons[0]->removeHighlight();
              Renderables::getSelectSound().play();
              break;
            case 3:
              m_selectedMap = "src/maps/map1.txt";
              m_buttons[3]->addHighlight();
              m_buttons[4]->removeHighlight();
              m_buttons[5]->removeHighlight();
              Renderables::getSelectSound().play();
              break;
            case 4:
              m_selectedMap = "src/maps/map2.txt";
              m_buttons[4]->addHighlight();
              m_buttons[3]->removeHighlight();
              m_buttons[5]->removeHighlight();
              Renderables::getSelectSound().play();
              break;
            case 5:
              m_selectedMap = "src/maps/map3.txt";
              m_buttons[5]->addHighlight();
              m_buttons[3]->removeHighlight();
              m_buttons[4]->removeHighlight();
              Renderables::getSelectSound().play();
              break;
            case 6:
              m_gui.ChangeState(
                  new EditorState(m_gui, m_window, m_selectedMap));
              m_buttons[6]->addHighlight();
              Renderables::getSelectSound().play();
              break;
            case 7:
              m_gui.ChangeState(
                  new GameState(m_gui, m_window, m_difficulty, m_selectedMap));
              m_buttons[7]->addHighlight();
              Renderables::getSelectSound().play();
              break;
          }
        }
      }
    }
  }
}

void MenuState::Draw() {
  this->m_window.clear();
  this->m_window.draw(Renderables::getMenuBackgroundSprite());

  for (auto t : m_texts) {
    this->m_window.draw(t);
  }

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