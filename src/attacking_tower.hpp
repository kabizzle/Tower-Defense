#pragma once

#include <cmath>

#include "tower.hpp"
#include "assignment.hpp"

class AttackingTower : public Tower
{
public:
  AttackingTower(uint32_t power, uint32_t range, uint32_t health, std::pair<int32_t, int32_t> coords, const Map& map, const std::string& imageName);

  void Attack(std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>> enemies);

  
  void ApplyBuff(float b);


private:
  uint32_t m_basePower, m_health;
  float m_buffs;
  std::vector<std::pair<int32_t, int32_t>> m_inRange;
};