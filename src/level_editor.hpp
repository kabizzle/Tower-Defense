#pragma once

#include "map.hpp"

class LevelEditor {
 public:
  LevelEditor(int width, int height, std::string& mapPath);

  bool Edit(std::pair<int, int> coordinate, tileType tile);

  bool Save();

  const Map& GetMap() const;

  bool Validate();

 private:
  Map m_map;
  int m_width;
  int m_height;
  std::string m_mapPath;
};