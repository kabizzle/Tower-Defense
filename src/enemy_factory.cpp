#include "enemy_factory.hpp"

#define DETAILED_DEBUG_PRINT 0

EnemyFactory::EnemyFactory(Difficulty diff)
  : m_diff(diff), m_round(0) { }

EnemyFactory::~EnemyFactory() { 
  Priv_Free();
}

void EnemyFactory::NextRoundInit() {
  m_round++;
  //Free previous
  Priv_Free();
  //Empty collections
  m_roundEnemies.clear();
  //Get types of enemies on the next round
  uint32_t typesInRound = Priv_NextNum();
  //Loop through all the possible enemies and add to the collection m_roundEnemies
  for(uint32_t e = Enemy::Homework; e < 9; e++){
    if((typesInRound >> e) & 1){
      //This type is present, so we add them
      m_batchSizes[e] += m_batchSizeDeltas[e];
      //We update the batch size
      for(uint32_t i = 0; i < m_batchSizes[e]; i++){
        m_roundEnemies.emplace_back(CreateEnemy(static_cast<Enemy>(e)));
      }
    }
  }
  return;
}

std::list<Assignment*> EnemyFactory::NextTick() {
  uint32_t maxEn = 1;
  while((m_nums[2] - m_nums[0]) >> maxEn) { maxEn++; }
  std::list<Assignment*> ret;
  //Loop until the collection m_roundEnemies is empty or maxEn amount has been added
  while(!m_roundEnemies.empty() && maxEn > 0) {
    ret.push_back(m_roundEnemies.front());
    m_roundEnemies.pop_front();
    maxEn--;
  }
  return ret;
}

Assignment* EnemyFactory::CreateEnemy(Enemy e) const {
  float hpScale = static_cast<float>(m_diff + 4) / 4.0f;
  switch (e)
  {
  case Homework:
    return new Assignment(1 * hpScale, 1, "homework");
  case Essay:
    return new Assignment(3 * hpScale, 1, "essay");
  case Project:
    return new Assignment(5 * hpScale, 1, "project");
  case B_Thesis:
    return new Assignment(10 * hpScale, 2, "B_thesis");
  case M_Thesis:
    return new Assignment(30 * hpScale, 2, "M_thesis");
  case D_Thesis:
    return new Assignment(50 * hpScale, 2, "D_thesis");
  case BSc:
    return new Degree(180 * hpScale, 4, std::string("BSc"), *this, {
                      {Enemy::B_Thesis, 1}, {Enemy::Project, 10},
                      {Enemy::Essay, 10}, {Enemy::Homework, 20}
                    });
  case MSc:
    return new Degree(300 * hpScale, 4, std::string("MSc"), *this,  {
                      {Enemy::BSc, 1}, {Enemy::M_Thesis, 1},
                      {Enemy::Project, 20}, {Enemy::Essay, 25},
                      {Enemy::Homework, 40}
                    });
  case DSc:
    return new Degree(500 * hpScale, 4, std::string("DSc"), *this,  {
                      {Enemy::MSc, 1}, {Enemy::BSc, 1},
                      {Enemy::D_Thesis, 1}, {Enemy::Project, 50},
                      {Enemy::Essay, 70}, {Enemy::Homework, 100}
                    });
  default:
    return new Assignment(1, 1, "ERROR");
    //TODO - maybe an exeption here
    //break;
  }
}

uint32_t EnemyFactory::GetRound() const { return m_round; }

std::ostream& operator<<(std::ostream& os, const EnemyFactory& ef) {
  os << "Enemy factory initialized for round " << ef.m_round << "; number is " << ef.m_nums[0]
     << " and the enemies allocated:\n"
     << "*** " << ef.m_roundEnemies.size() << " enemies for the round initially:\n";
#if DETAILED_DEBUG_PRINT
  for(auto [n, e] : ef.m_roundEnemies) {
    os << *e;
  }
#else
  for(uint32_t i = 0; i < 9; i++) {
    os << (((ef.m_nums[2] - ef.m_nums[0]) >> i) & 1 ? ef.m_batchSizes[i] : 0) << " - ";
  }
  os << "\n";
#endif
  os << std::flush;
  return os;
}

uint32_t EnemyFactory::Priv_NextNum() {
  uint32_t n = m_nums[0];
  m_nums[0] = m_nums[1];
  m_nums[1] = m_nums[2];
  m_nums[2] = n + m_nums[0];
  return n;
}

void EnemyFactory::Priv_Free() {
  //Iterate over the enemies still left in the enemy collection
  for(auto e: m_roundEnemies){
    delete e;
  }
}