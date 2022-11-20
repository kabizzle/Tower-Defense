#include "assignment.hpp"

Assignment::Assignment(uint32_t cr, uint32_t timeToMove, const std::string& imageName)
  : Renderable(imageName), m_maxCr(cr), m_curCr(cr), m_timeToMove(timeToMove), m_timeRemainder(0) { }

bool Assignment::Advance() {
  m_timeRemainder++;
  if(m_timeRemainder >= m_timeToMove) {
    m_timeRemainder = 0;
    return true;
  } else {
    return false;
  }
}

bool Assignment::IsAlive() const { return m_curCr > 0; }

uint32_t Assignment::GetCredits() const { return m_maxCr; }

uint32_t Assignment::TakeDmg(uint32_t dmg, std::list<Assignment*>& location){
    if(m_curCr > dmg){
      m_curCr -= dmg;
    } else {
      m_curCr = 0;
    }
    return 0;
  }

std::ostream& operator<<(std::ostream& os, const Assignment& as) {
  os << "Assignment: " << as.ImgPath() << std::endl;
  return os;
}