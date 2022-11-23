#include "attacking_tower.hpp"

AttackingTower::AttackingTower(uint32_t power, uint32_t range, uint32_t health, std::pair<int32_t, int32_t> coords, const Map& map, const std::string& imageName)
  : Tower(range, coords, imageName), m_basePower(power), m_health(health), m_buffs(0.0f) {
    //Check the path from map to see which coordinated are accessible
  auto rIter = map.GetPath().crbegin(), rIterEnd = map.GetPath().crend();
  int32_t thisX = coords.first, thisY = coords.second;
  for(; rIter != rIterEnd; rIter++) {
    //Check the distance of this coordinate pair from the coordinates of the tower
    auto& c = *rIter;
    float d = hypot((c.first - thisX), (c.second - thisY));
    if(d <= range) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRange.push_back(c);
    }
  }
}

void AttackingTower::Attack(std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>> enemies) {
  //Start going through the accessible coordinates and find the first non-dead enemy to attack
  for(const auto& c: m_inRange){
    for(auto e: enemies[c]){
      if(e->IsAlive()){
        m_health -= e->TakeDmg(m_basePower * m_buffs, enemies[c]);
        return;
      }
    }
  }
}

void AttackingTower::ApplyBuff(float b) { m_buffs += b; }