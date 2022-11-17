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
 * Method InitializeMap is used to initialize the map tiles (path) from a text
 * file.
 */
class Map {
 public:
  Map(int width, int length) : m_width(width), m_length(length) {}
  ~Map() = default;

  /* Used to initialize a map text file to m_grid.*/
  bool InitializeMap(const std::string& filename);

 private:
  /* Store the map width (x grows to right) and length (y grows down).*/
  int m_width, m_length;

  /* Stores the map grid itself. */
  std::map<std::pair<int, int>, int> m_grid;

  /* Store the path start and end coordinates. */
  std::pair<int, int> m_start, m_end;

  /* Stores the path in order from start to finish. */
  std::vector<std::pair<int, int>> m_path;

  /*Helper functions below:*/
  std::vector<std::pair<int, int>> GetNeighbors(int x, int y);
  bool ValidateMap();  // Used to validate the m_grid created in initialization.
  bool BuildPath();    // Used to build m_path from the m_grid created.
};