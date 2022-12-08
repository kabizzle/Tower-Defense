#include "editorstate.hpp"

void EditorState::PollEvents() {
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
            // case 0:
            //
            // case 1:
            //
            // case 2:
          }
        }
      }
    }
  }
}

void EditorState::Draw() {
  // Draw everything
}

void EditorState::Run() {
  this->PollEvents();
  this->Draw();
}

// LevelEditor editor;

//    editor.Edit(selected, tileType::towerTile);

//   editor.Edit(selected, tileType::pathTile);

//  editor.Edit(selected, tileType::startTile);

//  editor.Edit(selected, tileType::endTile);

EditorState::~EditorState() {
  for (auto b : m_buttons) {
    delete b.second;
  }
}