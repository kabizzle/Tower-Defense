#include "support_towers.hpp"
#include "utils.hpp"
#include "renderables.hpp"

SupportTower::SupportTower(uint32_t range, const std::pair<int32_t, int32_t>& coords,
                           const std::string& imageName, const std::vector<sf::Sprite>& sprites)
  : Tower(range, coords, imageName, sprites) { }

std::ostream& operator<<(std::ostream& os, const SupportTower& st) {
  os << "Support tower: " << st.ImgPath()  << " in (" << st.m_coords.first << "," << st.m_coords.second << ")" << std::endl;
  return os;
}

bool SupportTower::IsUpgradeable(uint32_t money) const { return false; }

SupportTower* SupportTower::Calculator(const std::pair<int32_t, int32_t>& coords) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getCalculatorSprite());
  return new BuffTower(5, coords, 0.5f, "calculator", sprites);
}

SupportTower* SupportTower::CoffeeTable(const std::pair<int32_t, int32_t>& coords) {
  std::vector<sf::Sprite> sprites;
  sprites.emplace_back(Renderables::getCoffeeTableSprite());
  return new HealTower(5, coords, 30, "coffee_table", sprites);
}


BuffTower::BuffTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, float buffStrength,
                     const std::string& imageName, const std::vector<sf::Sprite>& sprites)
  : SupportTower(range, coords, imageName, sprites), m_buffStrength(buffStrength) { }

void BuffTower::Act(std::list<AttackingTower*>& towers) {
  for(AttackingTower* t : towers){
    float d = UtilFunctions::distance(t->GetCoords(), this->GetCoords());
    if(d <= m_range) {
      t->ApplyBuff(m_buffStrength);
    }
  }
}



HealTower::HealTower(uint32_t range, const std::pair<int32_t, int32_t>& coords, uint32_t healStrength,
                     const std::string& imageName, const std::vector<sf::Sprite>& sprites)
  : SupportTower(range, coords, imageName, sprites), m_healStrength(healStrength) { }

void HealTower::Act(std::list<AttackingTower*>& towers) {
  for(AttackingTower* t : towers){
    float d = UtilFunctions::distance(t->GetCoords(), this->GetCoords());
    if(d <= m_range) {
      t->Heal(m_healStrength);
    }
  }
}