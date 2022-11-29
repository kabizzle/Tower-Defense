#include "attacking_tower.hpp"

AttackingTower::AttackingTower(uint32_t power, uint32_t range, uint32_t health, uint32_t upgCost, std::pair<int32_t, int32_t> coords, const Map& map, const std::string& imageName)
  : Tower(range, coords, imageName), m_basePower(power), m_maxHealth(health),
    m_health(health), m_upgCost(upgCost), m_level(1),
    m_buffs(1.0f), m_map(map) {
  //Check the path from map to see which coordinated are accessible
  Priv_UpdateRange(range);
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
  uint32_t dmgToGiveOut = m_basePower * m_buffs;
  for(uint32_t i: m_inRangeInd) {
    for(auto e: enemies[i]){
      if(e->IsAlive()){
        if(dmgToGiveOut <= e->CrLeft()) {
          //The last bit of dmg the tower has left
          uint32_t dmgToTower = e->TakeDmg(dmgToGiveOut, enemies[i]);
          m_health = dmgToTower < m_health ? m_health - dmgToTower : 0;
          return;
        } else {
          uint32_t dmgUsed = e->CrLeft();
          uint32_t dmgToTower = e->TakeDmg(dmgUsed, enemies[i]);
          m_health = dmgToTower < m_health ? m_health - dmgToTower : 0;
          //If the tower loses all its health, it cannot continue dealing dmg during this tick
          if(!this->IsFunctional()) {
            return;
          }
          dmgToGiveOut -= dmgUsed;
        }
        
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

bool AttackingTower::IsUpgradeable(uint32_t money) const {
  return money >= (m_level * m_upgCost);
}

bool AttackingTower::Upgrade() {
  if(m_level == 3) {
    //Cannot upgrade level 3 towers
    return false;
  }
  m_basePower += m_basePower;
  m_maxHealth += m_maxHealth / 2;
  m_level++;
  m_range += 2;
  Priv_UpdateRange(m_range);
  if(m_level == 2) {
    AddSuffix("_upgraded");
  } else {
    AddSuffix("_twice");
  }
}


AttackingTower* AttackingTower::Freshman(std::pair<int32_t, int32_t> coords, const Map& map) {
  return new AttackingTower(1, 7, 40, 20, coords, map, "freshman");
}

void AttackingTower::Priv_UpdateRange(uint32_t newRange) {
  //NOTE: Required by the old overload of Attack
  auto rIter = m_map.GetPath().crbegin(), rIterEnd = m_map.GetPath().crend();
  for(; rIter != rIterEnd; rIter++) {
    //Check the distance of this coordinate pair from the coordinates of the tower
    auto& c = *rIter;
    float d = UtilFunctions::distance(*rIter, m_coords);
    if(d <= newRange) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRange.push_back(c);
    }
  }
  //NOTE: For the new overload
  const std::vector<std::pair<int32_t, int32_t>>& path = m_map.GetPath();
  for(uint32_t i = path.size() - 1; i >= 0; i--) {
    auto& c = path[i];
    float d = UtilFunctions::distance(c, m_coords);
    if(d <= newRange) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRangeInd.push_back(i);
    }
  }
}