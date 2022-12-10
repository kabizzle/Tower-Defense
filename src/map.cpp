#include "map.hpp"

#include <iostream>

Map::Map(int32_t width, int32_t height) : m_width(width), m_height(height) { }

bool Map::InitializeMap(const std::string& filename) {
  std::ifstream is(filename);
  if (is.rdstate() && (is.failbit | is.badbit)) {
    throw std::invalid_argument("Map file couldn't be found");
  }

  char c;
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x <= m_width; x++) {
      is.get(c);
      if (c == EOF) {
        throw std::invalid_argument(
            "Map file does not have the right amount of symbols.");
      }

      switch (c) {
        case '_':
          m_grid[std::make_pair(x, y)] = TileType::towerTile;
          break;

        case 'S':
          m_grid[std::make_pair(x, y)] = TileType::startTile;
          m_start = std::make_pair(x, y);
          break;

        case 'X':
          m_grid[std::make_pair(x, y)] = TileType::pathTile;
          break;

        case 'E':
          m_grid[std::make_pair(x, y)] = TileType::endTile;
          m_end = std::make_pair(x, y);
          break;

        case '\n':
          break;

        default:
          throw std::invalid_argument("Map file has an unrecognized symbol.");
          return false;
      }
    }
  }
  m_grid.erase(std::make_pair(30, 19));

  return ValidateMap() && BuildPath();
}

const std::vector<std::pair<int, int>>& Map::GetPath() const { return m_path; }

std::vector<std::pair<int, int>> Map::GetNeighbors(int x, int y) {
  std::vector<std::pair<int, int>> neighbors;
  if (x != 0) {
    neighbors.push_back(std::make_pair(x - 1, y));
  }
  if (x != (m_width - 1)) {
    neighbors.push_back(std::make_pair(x + 1, y));
  }
  if (y != 0) {
    neighbors.push_back(std::make_pair(x, y - 1));
  }
  if (y != (m_height - 1)) {
    neighbors.push_back(std::make_pair(x, y + 1));
  }
  return neighbors;
}

bool Map::TestTilePos(std::pair<int, int> coordinate, TileType tile) {
  std::vector<std::pair<int, int>> neighbors =
      GetNeighbors(coordinate.first, coordinate.second);
  int count = 0;

  switch (tile) {
    case TileType::startTile:
      if (coordinate.first != 0) {
        throw std::invalid_argument(
            "Start tile is not in the leftmost column.");
        return false;
      }
      return true;

    case TileType::endTile:
      if (coordinate.second != (m_width - 1)) {
        throw std::invalid_argument("End tile is not in the rightmost column.");
        return false;
      }
      return true;

    case TileType::towerTile:
      return true;

    case TileType::pathTile:
      for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
        if (m_grid[*iter] == TileType::towerTile) {
          count++;
        }
      }
      if ((neighbors.size() - count) > 2) {
        throw std::invalid_argument(
            "Loaded map doesn't follow path rules (no adjacent parts!)");
        return false;
      }
      return true;

    default:
      throw std::invalid_argument("Faulty tile enumeration.");
      return false;
  }
}

bool Map::ValidateMap() {
  int startFlag = 0;
  int endFlag = 0;
  m_start = std::make_pair(-1, -1);
  m_end = std::make_pair(-1, -1);
  if (static_cast<int32_t>(m_grid.size()) != (m_height * m_width)) {
    throw std::invalid_argument("Loaded map is wrong size.");
  }

  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      int tile = m_grid[std::make_pair(x, y)];
      auto neighbors = GetNeighbors(x, y);
      int count = 0;

      switch (tile) {
        case TileType::startTile:
          if (startFlag != 0) {
            throw std::invalid_argument("Loaded map has multiple start tiles.");
            return false;
          } else if (x != 0) {
            throw std::invalid_argument(
                "Start tile is not in the leftmost column.");
            return false;
          }
          startFlag = 1;
          m_start = std::make_pair(x, y);
          break;

        case TileType::endTile:
          if (endFlag != 0) {
            throw std::invalid_argument("Loaded map has multiple end tiles.");
          } else if (x != (m_width - 1)) {
            throw std::invalid_argument(
                "End tile is not in the rightmost column.");
            return false;
          }
          endFlag = 1;
          m_end = std::make_pair(x, y);
          break;

        case TileType::towerTile:
          break;

        case TileType::pathTile:
          for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
            if (m_grid[*iter] == TileType::towerTile) {
              count++;
            }
          }
          if ((neighbors.size() - count) > 2) {
            throw std::invalid_argument(
                "Loaded map doesn't follow path rules (no adjacent parts!)");
            return false;
          }
          break;

        default:
          throw std::invalid_argument("Map matrix has faulty enumeration.");
          return false;
      }
    }
  }
  return true;
}

bool Map::BuildPath() {
  m_path.clear();
  bool endFlag = false;

  if (m_start.first < 0 || m_start.second < 0) {
    throw std::invalid_argument("Start tile is missing.");
    return false;
  } else if (m_end.first < 0 || m_end.second < 0) {
    throw std::invalid_argument("End tile is missing.");
    return false;
  }

  m_path.push_back(m_start);
  std::pair<int, int> previous_position;
  std::pair<int, int> position = m_start;

intact:;
  while (!endFlag) {
    if (position == m_end) {
      endFlag = true;
      m_path.push_back(m_end);
      break;
    }

    std::vector<std::pair<int, int>> neighbors =
        GetNeighbors(position.first, position.second);
    for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
      if (m_grid[*iter] != TileType::towerTile && *iter != previous_position) {
        previous_position = position;
        position = *iter;
        m_path.push_back(*iter);
        goto intact;
      }
    }
    return false;  // The path is not intact
  }
  if (m_path.front() != m_start || m_path.back() != m_end) {
    throw std::invalid_argument(
        "Path building failed (Start or end not in place).");
    return false;
  }

  return true;
}

const std::pair<int, int> Map::GetStart() const { return m_start; }

const std::pair<int, int> Map::GetEnd() const { return m_end; }

TileType Map::GetPos(std::pair<int, int> coordinate) const {
  return m_grid.at(coordinate);
}

const std::map<std::pair<int, int>, TileType>& Map::GetGrid() const {
  return m_grid;
}

bool Map::Edit(std::pair<int, int> coordinate, TileType tile) {
  if (coordinate.first >= m_width || coordinate.first < 0 ||
      coordinate.second >= m_height || coordinate.second < 0) {
    return false;
  }
  if (tile < 0 || tile > 3) {
    return false;
  }
  m_grid[coordinate] = tile;
  return true;
}