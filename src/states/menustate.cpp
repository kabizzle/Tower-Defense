#include "menustate.hpp"

MenuState::MenuState(GUI& gui, sf::RenderWindow& window)
    : State(gui, window),
      m_difficulty(Difficulty::Easy),
      m_selectedMap("1"),
      m_editing(false) {
  auto easyButton = m_gui.createButton("Easy", 0, 10);
  m_buttons["Easy"] = easyButton;

  auto mediumButton = m_gui.createButton("Easy", 60, 915);
  m_buttons["Medium"] = mediumButton;

  auto hardButton = m_gui.createButton("Easy", 105, 915);
  m_buttons["Hard"] = hardButton;

  auto map1Button = m_gui.createButton("Map 1", 465, 450);
  m_buttons["Map1"] = map1Button;

  auto map2Button = m_gui.createButton("Change map", 465, 450);
  m_buttons["Map1"] = map2Button;

  auto map3Button = m_gui.createButton("Change map", 465, 450);
  m_buttons["Map1"] = map3Button;

  auto createMapButton = m_gui.createButton("Easy", 150, 915);
  m_buttons["Create"] = createMapButton;

  auto editButton = m_gui.createButton("Easy", 195, 915);
  m_buttons["Edit"] = editButton;

  auto deleteButton = m_gui.createButton("Easy", 240, 915);
  m_buttons["Delete"] = deleteButton;

  auto playButton = m_gui.createButton("Easy", 285, 915);
  m_buttons["Play"] = playButton;
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
          if (!b.second.getGlobalBounds().contains(mouse)) continue;

          switch (b.first) {
            case "Easy":
              m_difficulty = Difficulty::Easy;
              m_buttons["Easy"].addHighlight();
              m_buttons["Medium"].removeHighlight();
              m_buttons["Hard"].removeHighlight();
            case 'Medium':
              m_difficulty = Difficulty::Medium;
              m_buttons["Medium"].addHighlight();
              m_buttons["Easy"].removeHighlight();
              m_buttons["Hard"].removeHighlight();
            case "Hard":
              m_difficulty = Difficulty::Hard;
              m_buttons["Hard"].addHighlight();
              m_buttons["Medium"].removeHighlight();
              m_buttons["Easy"].removeHighlight();
            case "Map1":
              m_selectedMap = "Map1";
              m_buttons["Map1"].addHighlight();
              m_buttons["Map2"].removeHighlight();
              m_buttons["Map3"].removeHighlight();
            case "Map2":
              m_selectedMap = "Map2";
              m_buttons["Map2"].addHighlight();
              m_buttons["Map1"].removeHighlight();
              m_buttons["Map3"].removeHighlight();
            case "Map3":
              m_selectedMap = "Map3";
              m_buttons["Map3"].addHighlight();
              m_buttons["Map1"].removeHighlight();
              m_buttons["Map2"].removeHighlight();
            case "Edit":
              // SHOULD THIS BE ANOTHER STATE?
              MenuState::RunLevelEditor(m_width, m_height, "DEFAULT");
            case "Play":
              // gui.currentState = GameState(diff, map);
              // return; ???
          }
        }
      }
    }
  }
};

void MenuState::Draw() {
  if (!m_editing) {
    // Draw: Menu Background

    // Draw:
    // Difficulty buttons:
    // Easy
    // Medium
    // Hard
    // Map list: new Gui::DropDownList(./maps/default_maps + ./maps/custom_maps)
    // Edit selected map -button Gui::Button()
    // Delete selected map -button Gui::Button()
    // Create new map -button
    // Play now button
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

  if (map == "DEFAULT") {
    try {
      editor = LevelEditor(m_width, m_height);
    } catch (std::exception& e) {
      return;
    }
  } else {
    try {
      editor = LevelEditor(m_width, m_height, map);
    } catch (std::exception& e) {
      return;
    }
  }

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

~MenuState::MenuState() {
  for (b : m_buttons) {
    delete b.second;
  }
}
