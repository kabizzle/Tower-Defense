#include "level_editor.hpp"

#include <fstream>
#include <iostream>

LevelEditor::LevelEditor(int width, int height, std::string& mapPath)
    : m_width(width),
      m_height(height),
      m_map(Map(width, height)),
      m_mapPath(mapPath) {
  m_map.InitializeMap(m_mapPath);
}

bool LevelEditor::Edit(std::pair<int, int> coordinate, tileType tile) {
  return m_map.Edit(coordinate, tile);
}

bool LevelEditor::Save() {
  bool validate = false;
  try {
    validate = m_map.ValidateMap() && m_map.BuildPath();
  } catch (std::exception& e) {
    throw e;
    validate = false;
  }

  if (!validate) {
    return false;
  }

  std::ofstream os(m_mapPath, std::ios::trunc);
  if (os.rdstate() && (os.failbit | os.badbit)) {
    throw std::invalid_argument("File selecting failed.");
  }

  int tile;

  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      tile = m_map.GetPos(std::make_pair(x, y));

      switch (tile) {
        case tileType::towerTile:
          os << '_';
          break;

        case tileType::startTile:
          os << 'S';
          break;

        case tileType::pathTile:
          os << 'X';
          break;

        case tileType::endTile:
          os << 'E';
          break;

        default:
          throw std::invalid_argument("Map has faulty tile enumeration.");
          return false;
      }
    }
    if (y < (m_height - 1)) {
      os << std::endl;
    }
  }

  os.flush();

  return true;
}

const Map& LevelEditor::GetMap() const { return m_map; }