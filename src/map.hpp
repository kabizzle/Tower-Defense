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
   * @param length Limit of y-coordinate of the map.
   */
  Map(int width, int length) : m_width(width), m_length(length) {}
  ~Map() = default;

  /**
   * @brief Initialize a map from a text file to m_grid.
   *
   * @param filename
   * @return true
   * @return false
   */
  bool InitializeMap(const std::string& filename);

  /**
   * @brief Get the Path object
   *
   * @return std::vector<std::pair<int, int>>
   */
  const std::vector<std::pair<int, int>>& GetPath() const;

 private:
  int m_width, m_length;
  std::map<std::pair<int, int>, int> m_grid;
  std::pair<int, int> m_start, m_end;
  std::vector<std::pair<int, int>> m_path;

  std::vector<std::pair<int, int>> GetNeighbors(int x, int y);
  bool ValidateMap();
  bool BuildPath();
};