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
      m_editor(LevelEditor(30, 20, mapPath)) {
  // Initialize the buttons
  m_buttons[0] = m_gui.createButton("Path starting tile", 915, 215);
  m_buttons[1] = m_gui.createButton("Path tile", 915, 255);
  m_buttons[2] = m_gui.createButton("Path ending tile", 915, 295);
  m_buttons[3] = m_gui.createButton("Clear tile", 915, 335);
  m_buttons[4] = m_gui.createButton("Save and return to menu", 915, 620);
  m_buttons[5] = m_gui.createButton("Cancel changes", 915, 670);

  // Initialize the selected tile square shape
  m_selectedShape = sf::RectangleShape(sf::Vector2f(30, 30));
  m_selectedShape.setFillColor(sf::Color(0, 255, 255, 64));
  m_selectedShape.setOutlineThickness(4);
  m_selectedShape.setOutlineColor(sf::Color::Cyan);
}

void EditorState::PollEvents() {
  while (m_window.pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) m_window.close();

    if (this->m_event.type == sf::Event::MouseButtonPressed) {
      if (this->m_event.mouseButton.button == sf::Mouse::Left) {
        std::cout << "the left button was pressed" << std::endl;
        sf::Vector2f mouse =
            m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        // Check if the mouse press was inside the map area
        int32_t xInt = static_cast<int32_t>(mouse.x);
        int32_t yInt = static_cast<int32_t>(mouse.y);
        if (xInt < 900 && yInt < 600) {
          // Find which tile is selected
          m_selX = xInt / TILE_SIZE;
          m_selY = yInt / TILE_SIZE;

        } else {
          for (auto b : m_buttons) {
            if (!b.second->getGlobalBounds().contains(mouse)) continue;

            switch (b.first) {
              case 0:
                try {
                  m_editor.Edit(std::make_pair(m_selX, m_selY),
                                tileType::startTile);
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }
                break;
              case 1:
                try {
                  m_editor.Edit(std::make_pair(m_selX, m_selY),
                                tileType::pathTile);
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }
                break;
              case 2:
                try {
                  m_editor.Edit(std::make_pair(m_selX, m_selY),
                                tileType::endTile);
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }
                break;
              case 3:
                try {
                  m_editor.Edit(std::make_pair(m_selX, m_selY),
                                tileType::towerTile);
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }

                break;
              case 4:
                try {
                  m_editor.Save();
                } catch (std::exception& e) {
                  std::cout << e.what() << std::endl;
                }
                m_gui.changeState(new MenuState(m_gui, m_window));
                break;
              case 5:
                m_gui.changeState(new MenuState(m_gui, m_window));
                m_buttons[4]->addHighlight();
                break;
            }
          }
        }
      }
    }
  }
}

void EditorState::Draw() {
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

  // Draw the selected tile square
  if (m_selX >= 0 || m_selY >= 0) {
    m_selectedShape.setPosition(
        sf::Vector2f(m_selX * TILE_SIZE, m_selY * TILE_SIZE));
    m_window.draw(m_selectedShape);
  }

  // Draw the buttons
  for (auto b : m_buttons) {
    b.second->drawButton(m_window);
  }

  m_window.display();
}

void EditorState::Run() {
  this->PollEvents();
  this->Draw();
}

EditorState::~EditorState() {
  for (auto b : m_buttons) {
    delete b.second;
  }
}