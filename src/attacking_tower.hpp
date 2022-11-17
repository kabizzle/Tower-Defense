#pragma once

#include "tower.hpp"

class AttackingTower : public Tower
{
public:
  AttackingTower(uint32_t power, uint32_t range, uint32_t health, const std::string& imageName);

  //TODO, needs some way of accessing the map
  void Act();

private:
  /* data */
};