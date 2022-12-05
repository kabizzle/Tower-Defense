#include "menustate.hpp"

void MenuState::Run() {
  // Create sprites:
  // Easy button (Default highlighted)
  // Medium button
  // Hard button

  // Draw: Menu Background

  while (/* Window is open */) {
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

    /* Poll Events */

    if (/* Easy sprite is pressed */) {
      m_difficulty = Difficulty::Easy;
      // Remove highlight from medium and hard sprite
      // Add highlight to easy sprite
    } else if (/* Medium sprite is pressed */) {
      m_difficulty = Difficulty::Medium;
      // Remove highlight from easy and hard sprite
      // Add highlight to medium sprite
    } else if (/* Hard sprite is pressed */) {
      // Remove highlight from easy and medium sprite
      // Add highlight to hard sprite
      m_difficulty = Difficulty::Hard;
    } else if (/* Map list is used */) {
      m_map = /* Selected map */;
    } else if (/* Edit selected map is pressed */) {
      MenuState::RunLevelEditor(m_selectedMap);
      // Draw menu background after editor closes
    } else if (/* Create new map is pressed */) {
      MenuState::RunLevelEditor("DEFAULT");
      // Draw menu background after editor closes
    } else if (/* Delete selected map is pressed */) {
      if (m_selectedMap != "1" && m_selectedMap != "2") {
        remove("./maps/TD/" + m_selectedMap + ".txt");
      }
    } else if (/* Play now is pressed */) {
      /* call m_gui.MoveToGameState(m_difficulty, ("./maps/TD/" + m_selectedMap
       * + ".txt")); */
      return;
    }
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
  };
