#pragma once

#include "map.hpp"

/**
 * @brief The logical core of the level editor state
 */
class LevelEditor {
public:
  /**
   * @brief Construct a new Level Editor object
   * 
   * @param width The width of the map
   * @param height The height of the map
   * @param mapPath Where the map file is located
   */
  LevelEditor(int32_t width, int32_t height, std::string& mapPath);

  /**
   * @brief Default destructor
   */
  ~LevelEditor() = default;

  /**
   * @brief Edit a tile at the coordinates
   * 
   * @param coordinate The location of the edit
   * @param tile What to change the tile into
   * @return bool Whether the editing was successfull
   */
  bool Edit(std::pair<int32_t, int32_t> coordinate, TileType tile);

  /**
   * @brief Saves the map to file
   * May throw an exception
   * @return bool Whether the saving was successfull
   */
  bool Save();

  /**
   * @brief Get the Map object
   * @return const Map& 
   */
  const Map& GetMap() const;

  /**
   * @brief Checks if the map is valid
   * @return bool
   */
  bool Validate();

 private:
  Map m_map;
  int32_t m_width;
  int32_t m_height;
  std::string m_mapPath;
};