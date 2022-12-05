/**
 * @file map_test.cpp
 * @brief Used to test the Map class.
 */
#include "../src/map.hpp"

#include <iostream>

int main() {
  Map map1 = Map(30, 20);

  try {
    map1.InitializeMap("testmap1.txt");
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  std::cout << "Map initialization complete." << std::endl;
  return 0;
}
