#include "assignment.hpp"

Assignment::Assignment(uint32_t cr, uint32_t speed, const std::string& imageName)
  : Renderable(imageName), m_maxCr(cr), m_curCr(cr), m_speed(speed), m_timeRemainder(0) { }

uint32_t Assignment::Advance(uint32_t t) {
  m_timeRemainder += t;
  uint32_t ret = m_timeRemainder / m_speed;
  m_timeRemainder %= m_speed;
  return ret;
}

uint32_t Assignment::TakeDmg(uint32_t dmg){
    if(m_curCr > dmg){
      m_curCr -= dmg;
      return 0;
    } else {
      return m_maxCr;
    }
  }

std::ostream& operator<<(std::ostream& os, const Assignment& as) {
  os << "Assignment: " << as.ImgPath() << std::endl;
  return os;
}