#pragma once

#include "map.hpp"

class LevelEditor {
 public:
  LevelEditor(int width, int height);
  LevelEditor(int width, int height, const std::string& name);

  bool Edit(std::pair<int, int> coordinate, int tile);

  bool Save(const std::string& mapname);

 private:
  Map m_map;
  int m_width;
  int m_height;
};