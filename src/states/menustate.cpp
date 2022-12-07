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
  if (!m_editing) {
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
              case 1:
                m_difficulty = Difficulty::Medium;
                m_buttons[1]->addHighlight();
                m_buttons[0]->removeHighlight();
                m_buttons[2]->removeHighlight();
              case 2:
                m_difficulty = Difficulty::Hard;
                m_buttons[2]->addHighlight();
                m_buttons[1]->removeHighlight();
                m_buttons[0]->removeHighlight();
              case 3:
                m_selectedMap = "./maps/map1.txt";
                m_buttons[3]->addHighlight();
                m_buttons[4]->removeHighlight();
                m_buttons[5]->removeHighlight();
              case 4:
                m_selectedMap = "./maps/map2.txt";
                m_buttons[4]->addHighlight();
                m_buttons[3]->removeHighlight();
                m_buttons[5]->removeHighlight();
              case 5:
                m_selectedMap = "./maps/map3.txt";
                m_buttons[5]->addHighlight();
                m_buttons[3]->removeHighlight();
                m_buttons[4]->removeHighlight();
              case 6:
                // SHOULD THIS BE ANOTHER STATE?
                m_editing = true;
              case 7:
                // gui.currentState = GameState(m_gui, m_window, m_difficulty,
                // m_selectedMap); return; ???
            }
          }
        }
      }
    }
  } else {
    // another poll events thing for editing mode.
  }
}

void MenuState::Draw() {
  if (!m_editing) {
    // Draw menu background

    for (auto b : m_buttons) {
      b.second->drawButton(m_window);
    }
  } else {
    // Draw Game/Map background

    // Draw:
    // PathTile button
    // StartTile button
    // EndTile button
    // Clear button
    // Save button
  }
}

void MenuState::Run() {
  this->PollEvents();
  this->Draw();
}

void MenuState::RunLevelEditor(const std::string& map) {
  LevelEditor editor;

  std::pair<int, int> selected = std::make_pair(0, 0);
  // Draw level editor background (same as GameState background)
  // Create sprites:
  // mapTiles, buttons

  while (/* Window is open */) {
    // Draw:
    // Current mapTiles
    // Clear tile button
    // PathTile button
    // StartTile button
    // EndTile button
    // Save and Exit button
    // Cancel editing button
    // Highlight (0, 0) tile as selected

    if (/* Map tile is pressed */) {
      // remove highlight from selected tile
      //  selected = pressed maptile coordinates.
      //  add highlight to selected maptile
    } else if (/* Clear tile button is pressed */) {
      editor.Edit(selected, tileType::towerTile);
    } else if (/* PathTile button is pressed */) {
      editor.Edit(selected, tileType::pathTile);
    } else if (/* StartTile button is pressed */) {
      editor.Edit(selected, tileType::startTile);
    } else if (/* EndTile button is pressed */) {
      editor.Edit(selected, tileType::endTile);
    } else if (/* Cancel editing button is pressed */) {
      return;
    } else if (/* Save and Exit button is pressed */) {
      bool success = false;
      if (map != "DEFAULT") {
        success = editor.Save(map);
      } else {
        std::string& mapName = "";
        // Draw things that request name from user
        success = editor.Save(mapName);
      }
      if (success) {
        return;
      } else {
        // Display some error thing about saving failed (invalid map).
      }
    }
  }
}
}
;

MenuState::~MenuState() {
  for (auto b : m_buttons) {
    delete b.second;
  }
}
