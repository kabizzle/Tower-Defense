#pragma once

#include <cmath>
#include <utility>

/**
 * @brief A namespace containing some utility functions needed in the project
 * 
 */
namespace UtilFunctions {
  float distance(const std::pair<int32_t, int32_t>& c1, const std::pair<int32_t, int32_t>& c2) {
    return hypot((c1.first - c2.first), (c1.second - c2.second));
  }
}