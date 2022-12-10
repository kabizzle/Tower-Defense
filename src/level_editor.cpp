#include "level_editor.hpp"

#include <fstream>
#include <iostream>

#define PRINT_EDITOR_ERRORS false

LevelEditor::LevelEditor(int32_t width, int32_t height, std::string& mapPath)
    : m_map(Map(width, height)),
      m_width(width),
      m_height(height),
      m_mapPath(mapPath) {
  m_map.InitializeMap(m_mapPath);
}

bool LevelEditor::Edit(std::pair<int32_t, int32_t> coordinate, TileType tile) {
  return m_map.Edit(coordinate, tile);
}

bool LevelEditor::Save() {
  bool validate = false;
  try {
    validate = (m_map.ValidateMap() && m_map.BuildPath());
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    validate = false;
  }

  if (!validate) {
    return false;
  }

  std::ofstream os(m_mapPath, std::ios::trunc);
  if (os.rdstate() && (os.failbit | os.badbit)) {
    throw std::invalid_argument("File selecting failed.");
  }

  int32_t tile;

  for (int32_t y = 0; y < m_height; y++) {
    for (int32_t x = 0; x < m_width; x++) {
      tile = m_map.GetPos(std::make_pair(x, y));

      switch (tile) {
        case TileType::towerTile:
          os << '_' << std::flush;
          break;

        case TileType::startTile:
          os << 'S' << std::flush;
          break;

        case TileType::pathTile:
          os << 'X' << std::flush;
          break;

        case TileType::endTile:
          os << 'E' << std::flush;
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

bool LevelEditor::Validate() {
  bool result = false;
  try {
    result = m_map.ValidateMap() && m_map.BuildPath();
  } catch (std::exception& e) {
    if (PRINT_EDITOR_ERRORS) std::cout << e.what() << std::endl;
    result = false;
  }
  return result;
}