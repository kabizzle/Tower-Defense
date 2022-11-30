#include "support_towers.hpp"
#include "utils.hpp"

SupportTower::SupportTower(uint32_t range, std::pair<int32_t, int32_t> coords, const std::string& imageName)
  : Tower(range, coords, imageName) { }



BuffTower::BuffTower(uint32_t range, std::pair<int32_t, int32_t> coords, float buffStrength, const std::string& imageName)
  : SupportTower(range, coords, imageName), m_buffStrength(buffStrength) { }

void BuffTower::Act(std::list<AttackingTower*>& towers) {
  for(AttackingTower* t : towers){
    float d = UtilFunctions::distance(t->GetCoords(), this->GetCoords());
    if(d <= m_range) {
      t->ApplyBuff(m_buffStrength);
    }
  }
}



HealTower::HealTower(uint32_t range, std::pair<int32_t, int32_t> coords, uint32_t healStrength, const std::string& imageName)
  : SupportTower(range, coords, imageName), m_healStrength(healStrength) { }

void HealTower::Act(std::list<AttackingTower*>& towers) {
  for(AttackingTower* t : towers){
    float d = UtilFunctions::distance(t->GetCoords(), this->GetCoords());
    if(d <= m_range) {
      t->Heal(m_healStrength);
    }
  }
}