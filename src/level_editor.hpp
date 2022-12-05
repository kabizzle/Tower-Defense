#include "map.hpp"

class LevelEditor {
 public:
  LevelEditor();
  LevelEditor(const std::string& filename);

  bool Edit(std::pair<int, int> coordinate, int tile);

  bool Save(std::string& name);

 private:
  Map m_map;
};