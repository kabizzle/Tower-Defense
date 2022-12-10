#include "assignment.hpp"

Assignment::Assignment(uint32_t cr, uint32_t timeToMove,
                       const std::string& name, const sf::Sprite& sprite)
    : Renderable(name, sprite),
      m_maxCr(cr),
      m_curCr(cr),
      m_timeToMove(timeToMove),
      m_timeRemainder(0),
      m_movedLastTick(false) {}

bool Assignment::Advance() {
  m_timeRemainder++;
  if (m_timeRemainder >= m_timeToMove) {
    m_timeRemainder = 0;
    m_movedLastTick = true;
  } else {
    m_movedLastTick = false;
  }
  return m_movedLastTick;
}

bool Assignment::MovedLastTick() const { return m_movedLastTick; }

bool Assignment::IsAlive() const { return m_curCr > 0; }

uint32_t Assignment::CrLeft() const { return m_curCr; }

uint32_t Assignment::GetCredits() const { return m_maxCr; }

uint32_t Assignment::TakeDmg(uint32_t dmg, std::list<Assignment*>& location) {
  (void)location;  // This one doesn't need the location
  if (m_curCr > dmg) {
    m_curCr -= dmg;
  } else {
    m_curCr = 0;
  }
  return 0;
}

std::ostream& operator<<(std::ostream& os, const Assignment& as) {
  os << "Enemy: " << as.EntityName() << "\t\tHealth: " << as.m_curCr << std::endl;
  return os;
}