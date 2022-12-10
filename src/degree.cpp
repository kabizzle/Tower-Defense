#include "degree.hpp"
#include "enemy_factory.hpp"

Degree::Degree(uint32_t cr, uint32_t timeToMove, const std::string& imageName, const sf::Sprite& sprite, const EnemyFactory& ef, const std::list<std::pair<Enemy, uint32_t>>& decendants)
  : Assignment(cr, timeToMove, imageName, sprite), m_decendants(decendants), m_ef(ef) { }

uint32_t Degree::TakeDmg(uint32_t dmg, std::list<Assignment*>& location){
    if(m_curCr > dmg){
      m_curCr -= dmg;
      return 0;
    } else {
      //The enemy dies, so it will spawn its descendants and return some damage
      m_curCr = 0;
      for(auto [e, n]: m_decendants) {
        try {
          for(uint32_t i = 0; i < n; i++) {
            location.emplace_back(m_ef.CreateEnemy(e));
          }
        } catch (const std::exception& e) {
          std::cerr << "In Degree::TakeDmg an error occured: " << e.what() << std::endl;
        }
      }
      return m_maxCr / 4;
    }
  }