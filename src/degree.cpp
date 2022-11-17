#include "degree.hpp"

Degree::Degree(uint32_t cr, uint32_t speed, const std::string& imageName, const std::list<std::pair<Enemy, uint32_t>>& decendants)
  : Assignment(cr, speed, imageName), m_decendants(decendants) { }

uint32_t Degree::TakeDmg(uint32_t dmg){
    if(this->m_curCr > dmg){
      this->m_curCr -= dmg;
      return 0;
    } else {
      /**
       * @brief TODO must also return the decendants to Map somehow OR make Map spawn them
       * 
       */
      return this ->m_maxCr;
    }
  }