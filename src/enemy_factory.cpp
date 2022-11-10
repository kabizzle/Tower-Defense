#include "enemy_factory.hpp"

EnemyFactory::EnemyFactory(Difficulty diff)
  : m_diff(diff), m_round(1) { }

EnemyFactory::~EnemyFactory() { 
  Priv_Free();
}

const std::list<std::pair<uint32_t, Assignment*>>& EnemyFactory::NextRound() {
  //Free previous
  Priv_Free();
  //Empty collections
  m_roundEnemies.clear();
  m_lateEnemies.clear();
  //Get types of enemies on the next round
  uint32_t typesInRound = Priv_NextNum();
  //Loop through all the possible enemies and add to the collection m_roundEnemies
  uint32_t tOffset = 0;
  for(uint32_t e = Enemy::Homework; e < 9; e++){
    if((typesInRound >> e) & 1){
      //This type is present, so we add them
      for(uint32_t i = 0; i < m_batchSizes[e]; i++){
        m_roundEnemies.emplace_back(tOffset, Priv_CreateEnemy(static_cast<Enemy>(e)));
      }
      //We update the batch size
      m_batchSizes[e] += m_batchSizeDeltas[e];
      //Update timeOffset
      tOffset++;
    }
  }
  m_round++;
  return m_roundEnemies;
}

Assignment* EnemyFactory::CreateEnemy(Enemy e) {
  Assignment* newlyAdded = Priv_CreateEnemy(e);
  m_lateEnemies.push_back(newlyAdded);
  return newlyAdded;
}

uint32_t EnemyFactory::GetRound() const { return m_round; }

std::ostream& operator<<(std::ostream& os, const EnemyFactory& ef) {
  os << "Enemy factory on round " << ef.m_round << " with the following enemies allocated:\n"
     << "*** " << ef.m_roundEnemies.size() << " enemies for the round initially:\n";
  for(auto [n, e] : ef.m_roundEnemies) {
    os << *e;
  }
  os << "*** " << ef.m_lateEnemies.size() << " enemies spawned during the round:\n";
  for(auto e : ef.m_lateEnemies) {
    os << *e;
  }
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

Assignment* EnemyFactory::Priv_CreateEnemy(Enemy e) {
  switch (e)
  {
  case Homework:
    return new Assignment(1, 30, "homework");
  case Essay:
    return new Assignment(3, 25, "essay");
  case Project:
    return new Assignment(5, 15, "project");
  case B_Thesis:
    return new Assignment(10, 10, "B_thesis");
  case M_Thesis:
    return new Assignment(30, 5, "M_thesis");
  case D_Thesis:
    return new Assignment(50, 2, "D_thesis");
  case BSc:
    return new Degree(180, 2, std::string("BSc"), {
                      {Enemy::B_Thesis, 1}, {Enemy::Project, 10},
                      {Enemy::Essay, 10}, {Enemy::Homework, 20}
                    });
  case MSc:
    return new Degree(300, 1, std::string("MSc"), {
                      {Enemy::BSc, 1}, {Enemy::M_Thesis, 1},
                      {Enemy::Project, 20}, {Enemy::Essay, 25},
                      {Enemy::Homework, 40}
                    });
  case DSc:
    return new Degree(500, 1, std::string("DSc"), {
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

void EnemyFactory::Priv_Free() {
  //Iterate over the enemies still left in the main enemy collection
  for(auto [n, e]: m_roundEnemies){
    delete e;
  }
  //Iterate over the extra enemies spawned during the round
  for(auto e : m_lateEnemies){
    delete e;
  }
}