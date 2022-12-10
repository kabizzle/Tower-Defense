#pragma once

#include <cmath>
#include <cstdint>
#include <utility>

/**
 * @brief A namespace containing some utility functions needed in the project
 */
namespace UtilFunctions {
  /**
   * @brief Calculates the Euclidean distance between two coordinate pairds
   * @param c1 coordinate 1
   * @param c2 coordinate 2
   * @return float 
   */
  float distance(const std::pair<int32_t, int32_t>& c1,
                 const std::pair<int32_t, int32_t>& c2);
}  // namespace UtilFunctions