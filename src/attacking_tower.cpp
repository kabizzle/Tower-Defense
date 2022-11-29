#include "attacking_tower.hpp"

AttackingTower::AttackingTower(uint32_t power, uint32_t range, uint32_t health, std::pair<int32_t, int32_t> coords, const Map& map, const std::string& imageName)
  : Tower(range, coords, imageName), m_basePower(power), m_health(health), m_maxHealth(health), m_buffs(1.0f) {
  //Check the path from map to see which coordinated are accessible
  //NOTE: Required by the old overload of Attack
  auto rIter = map.GetPath().crbegin(), rIterEnd = map.GetPath().crend();
  for(; rIter != rIterEnd; rIter++) {
    //Check the distance of this coordinate pair from the coordinates of the tower
    auto& c = *rIter;
    float d = UtilFunctions::distance(*rIter, coords);
    if(d <= range) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRange.push_back(c);
    }
  }
  //NOTE: For the new overload
  const std::vector<std::pair<int32_t, int32_t>>& path = map.GetPath();
  for(uint32_t i = path.size() - 1; i >= 0; i--) {
    auto& c = path[i];
    float d = UtilFunctions::distance(c, coords);
    if(d <= range) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRangeInd.push_back(i);
    }
  }
}

void AttackingTower::Attack(std::map<std::pair<int32_t, int32_t>, std::list<Assignment*>>& enemies) {
  //Start going through the accessible coordinates and find the first non-dead enemy to attack
  for(const auto& c: m_inRange){
    for(auto e: enemies[c]){
      if(e->IsAlive()){
        uint32_t dmgToTower = e->TakeDmg(m_basePower * m_buffs, enemies[c]);
        m_health = dmgToTower < m_health ? m_health - dmgToTower : 0;
        return;
      }
    }
  }
  //After the attack, reset the buffs to 0.0
  m_buffs = 1.0f;
}

void AttackingTower::Attack(std::vector<std::list<Assignment*>>& enemies) {
  //Start going through the accessible indices and find the first non-dead enemy to attack
  for(uint32_t i: m_inRangeInd) {
    for(auto e: enemies[i]){
      if(e->IsAlive()){
        uint32_t dmgToTower = e->TakeDmg(m_basePower * m_buffs, enemies[i]);
        m_health = dmgToTower < m_health ? m_health - dmgToTower : 0;
        return;
      }
    }
  }
  //After the attack, reset the buffs to 0.0
  m_buffs = 1.0f;
}

void AttackingTower::ApplyBuff(float b) { m_buffs += b; }

bool AttackingTower::IsFunctional() const { return m_health > 0; }

void AttackingTower::Heal(uint32_t h) {
  m_health += h;
  if(m_health > m_maxHealth) {
    m_health = m_maxHealth;
  }
}


AttackingTower* AttackingTower::Freshman(std::pair<int32_t, int32_t> coords, const Map& map) {
  return new AttackingTower(1, 7, 40, coords, map, "freshman");
}