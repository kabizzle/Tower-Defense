#pragma once

#include <exception>
#include <fstream>
#include <map>
#include <string>
#include <vector>

/**
 * @brief Grid tile enumeration representing different kinds of map positions.
 *
 */
enum tileType { towerTile, startTile, pathTile, endTile };

/**
 * @brief Map class that represents the grid map system behind each unique
 * level.
 *
 */
class Map {
 public:
  /**
   * @brief Construct a new Map object
   *
   * @param width Limit of x-coordinate of the map.
   * @param height Limit of y-coordinate of the map.
   */
  Map(int width, int height) : m_width(width), m_height(height) {}

  /**
   * @brief Initialize a map from a text file to m_grid.
   *
   * @param filename
   * @return true
   * @return false
   */
  bool InitializeMap(const std::string& filename);

  /**
   * @brief Get the Start object
   *
   * @return std::pair<int, int>
   */
  const std::pair<int, int> GetStart() const;

  /**
   * @brief Get the End object
   *
   * @return std::pair<int, int>
   */
  const std::pair<int, int> GetEnd() const;

  /**
   * @brief Get the tile at position (x, y)
   *
   * @param coordinate
   * @return int (tile enumeration 0-3)
   */
  int GetPos(std::pair<int, int> coordinate) const;

  /**
   * @brief Get the Grid object
   *
   * @return const std::map<std::pair<int, int>, int>
   */
  const std::map<std::pair<int, int>, int>& GetGrid() const;

  /**
   * @brief Get the Path object
   *
   * @return const std::vector<std::pair<int, int>>&
   */
  const std::vector<std::pair<int, int>>& GetPath() const;

  /**
   * @brief Change a tile on the map to another.
   *
   * @param coordinate
   * @param tile
   * @return true if editing was successful
   * @return false if editing was not successful.
   */
  bool Edit(std::pair<int, int> coordinate, int tile);

  /**
   * @brief Validate the current m_grid. (Called by InitializeMap).
   *
   * @return true if map is valid
   * @return false if map is not valid
   */
  bool ValidateMap();

  /**
   * @brief Build the path of the current map in m_path.
   *
   * @return true if path is built successfully
   * @return false if path cannot be built.
   */
  bool BuildPath();

  /**
   * @brief Get the vertical and horizontal neighbors of (x, y).
   *
   * @param x
   * @param y
   * @return std::vector<std::pair<int, int>>
   */
  std::vector<std::pair<int, int>> GetNeighbors(int x, int y);

  /**
   * @brief Test
   *
   * @param coordinate
   * @param tile
   * @return true if position is valid
   * @return false if position is invalid
   */
  bool TestTilePos(std::pair<int, int> coordinate, int tile);

 private:
  int m_width, m_height;
  std::map<std::pair<int, int>, int> m_grid;
  std::pair<int, int> m_start, m_end;
  std::vector<std::pair<int, int>> m_path;
};
