#pragma once

#include "map.hpp"

class LevelEditor {
 public:
  LevelEditor(int width, int height, int mapNumber;

  bool Edit(std::pair<int, int> coordinate, int tile);

  bool Save();

 private:
  Map m_map;
  int m_width;
  int m_height;
  int m_mapNumber;
  std::string m_mapPath;
};