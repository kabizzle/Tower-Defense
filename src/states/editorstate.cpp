#include "editorstate.hpp"

#include "menustate.hpp"

#define TILE_SIZE 30

EditorState::EditorState(GUI& gui, sf::RenderWindow& window,
                         std::string& mapPath)
    : State(gui, window),
      m_editor(LevelEditor(30, 20, mapPath)),
      m_mapPath(mapPath),
      m_selX(-1),
      m_selY(-1),
      m_selectedButton(0) {
  // Initialize the buttons
  m_buttons[0] = m_gui.CreateButton("Clear tile", 915, 15);
  m_buttons[0]->addHighlight();
  m_buttons[1] = m_gui.CreateButton("Path tile", 915, 55);
  m_buttons[2] = m_gui.CreateButton("Path starting tile", 915, 95);
  m_buttons[3] = m_gui.CreateButton("Path ending tile", 915, 135);
  m_buttons[4] = m_gui.CreateButton("Save and return", 915, 620);
  m_buttons[5] = m_gui.CreateButton("Cancel changes", 915, 670);

  // Initialize the selected tile square shape
  m_selectedShape = sf::RectangleShape(sf::Vector2f(30, 30));
  m_selectedShape.setFillColor(sf::Color(0, 255, 255, 64));
  m_selectedShape.setOutlineThickness(4);
  m_selectedShape.setOutlineColor(sf::Color::Cyan);

  m_validated.setFont(m_gui.GetFont());
  m_validated.setFillColor(sf::Color::Green);
  m_validated.setString("Map is Valid");
  m_validated.setCharacterSize(24);
  m_validated.setPosition(30, 648);

  m_unvalidated.setFont(m_gui.GetFont());
  m_unvalidated.setFillColor(sf::Color::Red);
  m_unvalidated.setString("Map is faulty");
  m_unvalidated.setCharacterSize(24);
  m_unvalidated.setPosition(30, 648);

  m_instructions.setFont(m_gui.GetFont());
  m_instructions.setFillColor(sf::Color::White);
  m_instructions.setString(
      "Map requirements:\n- Exactly 1 starting tile in the\n  leftmost "
      "column.\n- "
      "Exactly "
      "1 ending tile in the\n  rightmost column.\n- Single intact path from "
      "starting\n  tile to ending "
      "tile.\n- Two parts of the path can't run\n  alongside each other "
      "without\n  "
      "an empty tile in between.");
  m_instructions.setCharacterSize(16);
  m_instructions.setPosition(915, 175);
}

void EditorState::Priv_PollEvents() {
  while (m_window.pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) m_window.close();

    if (this->m_event.type == sf::Event::MouseButtonPressed) {
      if (this->m_event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse =
            m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        // Check if the mouse press was inside the map area
        int32_t xInt = static_cast<int32_t>(mouse.x);
        int32_t yInt = static_cast<int32_t>(mouse.y);
        if (xInt < 900 && yInt < 600) {
          // Find which tile is selected
          m_selX = xInt / TILE_SIZE;
          m_selY = yInt / TILE_SIZE;
          // Perform action if an action button is selected
          switch (m_selectedButton) {
            case 0:
              try {
                m_editor.Edit(std::make_pair(m_selX, m_selY),
                              TileType::towerTile);
              } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
              }
              break;
            case 1:
              try {
                m_editor.Edit(std::make_pair(m_selX, m_selY),
                              TileType::pathTile);
              } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
              }
              break;
            case 2:
              try {
                m_editor.Edit(std::make_pair(m_selX, m_selY),
                              TileType::startTile);
              } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
              }
              break;
            case 3:
              try {
                m_editor.Edit(std::make_pair(m_selX, m_selY),
                              TileType::endTile);
              } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
              }
              break;
            default:
              break;
          }

        } else {
          for (auto b : m_buttons) {
            if (!b.second->getGlobalBounds().contains(mouse)) continue;

            switch (b.first) {
              case 0:
                m_buttons[m_selectedButton]->removeHighlight();
                m_selectedButton = 0;
                m_buttons[0]->addHighlight();
                break;
              case 1:
                m_buttons[m_selectedButton]->removeHighlight();
                m_selectedButton = 1;
                m_buttons[1]->addHighlight();
                break;
              case 2:
                m_buttons[m_selectedButton]->removeHighlight();
                m_selectedButton = 2;
                m_buttons[2]->addHighlight();
                break;
              case 3:
                m_buttons[m_selectedButton]->removeHighlight();
                m_selectedButton = 3;
                m_buttons[3]->addHighlight();
                break;
              case 4:
                try {
                  m_editor.Save();
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }
                m_gui.ChangeState(new MenuState(m_gui, m_window));
                break;
              case 5:
                m_gui.ChangeState(new MenuState(m_gui, m_window));
                m_buttons[4]->addHighlight();
                break;
            }
          }
        }
      }
    }

    // Check if the selected tile has to be drawn
    if (m_event.type == sf::Event::MouseMoved) {
      // Reset to false
      m_drawSelectedShape = false;
      // Check if mouse is hovering over a maptile
      // Check if the mouse is inside the map area
      int32_t xInt = static_cast<int32_t>(m_event.mouseMove.x);
      int32_t yInt = static_cast<int32_t>(m_event.mouseMove.y);
      if (xInt < 900 && yInt < 600) {
        m_selX = xInt / TILE_SIZE;
        m_selY = yInt / TILE_SIZE;
        m_drawSelectedShape = true;
      }
    }
  }
}

void EditorState::Priv_Draw() {
  m_window.clear();

  // Initialize the map tiles
  m_mapTileSprites.clear();

  for (auto& [coords, tile] : m_editor.GetMap().GetGrid()) {
    sf::Sprite sprite;
    switch (tile) {
      case towerTile:
        sprite = Renderables::getTowertileSprite();
        break;
      case startTile:
        sprite = Renderables::getStarttileSprite();
        break;
      case pathTile:
        sprite = Renderables::getPathtileSprite();
        break;
      case endTile:
        sprite = Renderables::getEndtileSprite();
        break;
    }
    sprite.setPosition(TILE_SIZE * coords.first, TILE_SIZE * coords.second);
    m_mapTileSprites.push_back(sprite);
  }

  // Draw the background and tiles
  const auto& bcg = Renderables::getBackgroundSprite();
  m_window.draw(bcg);
  for (const auto& s : m_mapTileSprites) {
    m_window.draw(s);
  }

  // Draw the selected tile square if mouse is hovering over the map
  if (m_drawSelectedShape && m_selX >= 0 && m_selY >= 0) {
    m_selectedShape.setPosition(
        sf::Vector2f(m_selX * TILE_SIZE, m_selY * TILE_SIZE));
    m_window.draw(m_selectedShape);
  }

  // Draw the buttons
  for (auto b : m_buttons) {
    b.second->drawButton(m_window);
  }
  // Draw the syntax status of the map (Correct / Faulty)
  if (m_editor.Validate()) {
    m_window.draw(m_validated);
  } else {
    m_window.draw(m_unvalidated);
  }

  // Draw the instructions
  m_window.draw(m_instructions);

  m_window.display();
}

void EditorState::Run() {
  this->Priv_PollEvents();
  this->Priv_Draw();
}

EditorState::~EditorState() {
  for (auto b : m_buttons) {
    delete b.second;
  }
}