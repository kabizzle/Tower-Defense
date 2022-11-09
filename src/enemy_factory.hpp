#pragma once

#include <map>

#include "degree.hpp"

enum Difficulty {
  Easy,
  Medium,
  Hard
};

/**
 * @brief A class which handles the logic about what enemies come and how much during each round
 * 
 * The logic as in "Which enemies are present in the round?" is as follows:
 *    In addition to the round number m_round, we have a Fibonacci-like sequence, where
 *    a_1 = a_2 = a_3 = 1 and after that a_n = a_(n-2) + a_(n-3). Then, from the binary representation
 *    of a_(m_round) we look at which bits are set, starting from the least significant bits, and the i:th
 *    bit being set means that the i:th enemy type is present.
 *    For example on 6th round a_6 = 3, which is ...0011 in binary, so enemies 0 (Homework) and 1 (Essay)
 *    are present. The numbers a_n in the sequence may also overflow at some point, but that is ok.
 * The logic as in "How many enemies come during the round?" is based on the array m_batchSizes.
 *    After each round an enemy type is present, the batch size will also be incremented according to the deltas.
 * 
 */
class EnemyFactory
{
public:
  EnemyFactory(Difficulty diff) : m_diff(diff), m_round(1), m_nums({1}), m_batchSizes({10, 5, 3, 2, 2}) { }

  //No copying
  EnemyFactory(const EnemyFactory& other) = delete;
  EnemyFactory& operator=(const EnemyFactory& other) = delete;

  ~EnemyFactory();  //Must release the allocated enemies

  std::map<uint32_t, Assignment*>& NextRound(); //Frees the memory of previously allocated enemies

  std::map<uint32_t, Assignment*>& Round(uint32_t r);   //Similar but can give any round

  /**
   * @brief Creates an enemy based on the enumeration
   * 
   * The function may be used by the class itself or from other places, since some enemies
   * spawn new ones when they are defeated
   * 
   * @param e The enumeration of the enemy to be created
   * @return A DYNAMICALLY allocated enemy
   */
  static Assignment* CreateEnemy(Enemy e) {
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
      break;
    }
  }

private:
  Difficulty m_diff;
  uint32_t m_round;
  uint32_t m_nums[3];   //< Used in the internal logic to get the enemy composition of each round
  std::map<uint32_t, Assignment*> m_roundEnemies;
  uint32_t m_batchSizes[9], m_batchSizeDeltas[9];

  //Private functions

  /**
   * @brief Uses m_nums to calculate the next one in the sequence
   * @return the next number in the sequence
   */
  uint32_t nextNum();
};
