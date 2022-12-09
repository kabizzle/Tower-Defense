#include "attacking_tower.hpp"
#include "utils.hpp"

AttackingTower::AttackingTower(uint32_t power, uint32_t range, uint32_t health, uint32_t upgCost,
                               const std::pair<int32_t, int32_t>& coords, const Map& map,
                               const std::string& imageName, const std::vector<sf::Sprite>& sprites)
  : Tower(range, coords, imageName, sprites), m_basePower(power), m_maxHealth(health),
    m_health(health), m_upgCost(upgCost), m_level(1),
    m_buffs(1.0f), m_map(map) {
  //Check the path from map to see which coordinated are accessible
  Priv_UpdateRange(range);
}

void AttackingTower::Attack(std::vector<std::list<Assignment*>>& enemies,
                            std::list<std::pair<std::pair<int32_t, int32_t>,std::pair<int32_t, int32_t>>>& attackCollection) {
  //Start going through the accessible indices and find the first non-dead enemy to attack
  uint32_t dmgToGiveOut = m_basePower * m_buffs;
  for(uint32_t i: m_inRangeInd) {
    for(auto e: enemies[i]){
      if(e->IsAlive()){
        //Tower will attack this enemy, add the action to attackCollection
        attackCollection.emplace_back(this->m_coords, this->m_map.GetPath()[i]);
        uint32_t dmgToThisEnemy = (dmgToGiveOut < e->CrLeft()) ? dmgToGiveOut : e->CrLeft();
        uint32_t dmgToTower = e->TakeDmg(dmgToThisEnemy, enemies[i]);
        m_health = (dmgToTower < m_health) ? m_health - dmgToTower : 0;
        //If the tower loses all its health, it cannot continue dealing dmg during this tick
        if(!this->IsFunctional()) {
          //Change the look a bit
          m_sprite.setColor(sf::Color(255, 255, 255, 80));
          return;
        } else if (dmgToGiveOut == 0) {
          return;
        }
        dmgToGiveOut -= dmgToThisEnemy;
        
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
  //When a tower is healed and becomes functional, the sprite will be changed back
  if(this->IsFunctional()) {
    m_sprite.setColor(sf::Color(255, 255, 255, 255));
  }
}

bool AttackingTower::IsUpgradeable(uint32_t money) const {
  return m_level < 3 && money >= m_upgCost;
}

uint32_t AttackingTower::Upgrade() {
  m_basePower += m_basePower;
  m_maxHealth += m_maxHealth / 2;
  m_range += 2;
  Priv_UpdateRange(m_range);
  auto& newSprite = m_allSprites[m_level];
  newSprite.setPosition(m_coords.first * TILE_SIZE, m_coords.second * TILE_SIZE);
  SetSprite(newSprite);
  m_level++;
  return m_upgCost;
}

std::ostream& operator<<(std::ostream& os, const AttackingTower& at) {
  os << "Attacking tower: " << at.ImgPath()  << " in (" << at.m_coords.first << "," << at.m_coords.second
     << ")\tHP: " << at.m_health << " Pow: " << at.m_basePower << " Buf: " << at.m_buffs << std::endl;
  return os;
}

AttackingTower* AttackingTower::Freshman(const std::pair<int32_t, int32_t>& coords, const Map& map) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getFreshman1Sprite());
  sprites.emplace_back(Renderables::getFreshman2Sprite());
  sprites.emplace_back(Renderables::getFreshman3Sprite());
  return new AttackingTower(1, 7, 40, towerPrices.at(TowerType::Freshman), coords, map, "freshman", sprites);
}

AttackingTower* AttackingTower::Teekkari(const std::pair<int32_t, int32_t>& coords, const Map& map) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getTeekkari1Sprite());
  sprites.emplace_back(Renderables::getTeekkari2Sprite());
  sprites.emplace_back(Renderables::getTeekkari3Sprite());
  return new AttackingTower(5, 7, 80, towerPrices.at(TowerType::Teekkari), coords, map, "teekkari", sprites);
}

AttackingTower* AttackingTower::Bachelor(const std::pair<int32_t, int32_t>& coords, const Map& map) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getBachelor1Sprite());
  sprites.emplace_back(Renderables::getBachelor2Sprite());
  sprites.emplace_back(Renderables::getBachelor3Sprite());
  return new AttackingTower(20, 8, 120, towerPrices.at(TowerType::Bachelor), coords, map, "bachelor", sprites);
}

AttackingTower* AttackingTower::Master(const std::pair<int32_t, int32_t>& coords, const Map& map) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getMaster1Sprite());
  sprites.emplace_back(Renderables::getMaster2Sprite());
  sprites.emplace_back(Renderables::getMaster3Sprite());
  return new AttackingTower(50, 8, 160, towerPrices.at(TowerType::Master), coords, map, "master", sprites);
}

AttackingTower* AttackingTower::Doctor(const std::pair<int32_t, int32_t>& coords, const Map& map) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getDoctor1Sprite());
  sprites.emplace_back(Renderables::getDoctor2Sprite());
  sprites.emplace_back(Renderables::getDoctor3Sprite());
  return new AttackingTower(100, 9, 200, towerPrices.at(TowerType::Doctor), coords, map, "doctor", sprites);
}

void AttackingTower::Priv_UpdateRange(uint32_t newRange) {
  //NOTE: Required by the old overload of Attack
  /*auto rIter = m_map.GetPath().crbegin(), rIterEnd = m_map.GetPath().crend();
  for(; rIter != rIterEnd; rIter++) {
    //Check the distance of this coordinate pair from the coordinates of the tower
    auto& c = *rIter;
    float d = UtilFunctions::distance(*rIter, m_coords);
    if(d <= newRange) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRange.push_back(c);
    }
  }*/
  //NOTE: For the new overload
  const std::vector<std::pair<int32_t, int32_t>>& path = m_map.GetPath();
  for(int32_t i = path.size() - 1; i >= 0; i--) {
    auto& c = path[i];
    float d = UtilFunctions::distance(c, m_coords);
    if(d <= newRange) {
      //If the distance is sufficiently small, add this coordinate pair to the possible target coordinates
      m_inRangeInd.push_back(i);
    }
  }
}