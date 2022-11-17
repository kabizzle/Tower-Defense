#pragma once

#include <list>

#include "degree.hpp"

enum Difficulty {
  Easy,
  Medium,
  Hard
};

/**
 * @brief A class which handles the logic about what enemies come and how much of during each round
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
 * This class handles the memory management of the allocated Assignment instances, it frees all the enemies either
 *    when next round starts or when it is destructed.
 * 
 */
class EnemyFactory
{
public:
  /**
   * @brief Constructs a new Enemy Factory object
   * 
   * @param diff The difficulty of the game, scales the HP of the enemies
   */
  EnemyFactory(Difficulty diff);

  /**
   * @brief Copying is not allowed
   */
  EnemyFactory(const EnemyFactory& other) = delete;
  EnemyFactory& operator=(const EnemyFactory& other) = delete;

  /**
   * @brief Destroys the Enemy Factory object, releases all allocated enemies
   */
  ~EnemyFactory();

  /**
   * @brief Gives the enemy composition of the next round
   * Also frees the previously allocated enemies
   * @return A reference to a container where the enemies are in order of their arrival
   */
  const std::list<std::pair<uint32_t, Assignment*>>& NextRound();

  /**
   * @brief TODO gives any round desired
   * 
   * @param r 
   * @return std::map<uint32_t, Assignment*>& 
   */
  const std::list<std::pair<uint32_t, Assignment*>>& Round(uint32_t r);

  /**
   * @brief Creates an Enemy object
   * For external use. Since this class must keep track of the allocated enemies, this version
   * adds the enemy to the collection m_lateEnemies
   * @return A dynamically allocated enemy
   */
  Assignment* CreateEnemy(Enemy e);

  uint32_t GetRound() const;

  friend std::ostream& operator<<(std::ostream& os, const EnemyFactory& ef);

private:
  Difficulty m_diff;
  uint32_t m_round;
  uint32_t m_nums[3] = {1, 1, 1};   //< Used in the internal logic to get the enemy composition of each round
  std::list<std::pair<uint32_t, Assignment*>> m_roundEnemies;
  std::list<Assignment*> m_lateEnemies;
  uint32_t m_batchSizes[9] = {0}, m_batchSizeDeltas[9] = {10, 5, 3, 2, 2, 2, 1, 1, 1};

  //Private functions

  /**
   * @brief Uses m_nums to calculate the next one in the sequence
   * @return the next number in the sequence
   */
  uint32_t Priv_NextNum();

  /**
   * @brief Creates an enemy based on the enumeration
   * 
   * The function is for the classes other methods to call when constructing the initial layout of the class.
   * A publicly available version CreateEnemy for the need to spawn other enemies when one dies
   * 
   * @param e The enumeration of the enemy to be created
   * @return A DYNAMICALLY allocated enemy
   */
  Assignment* Priv_CreateEnemy(Enemy e);

  /**
   * @brief Used by destructor and NextRound to free the previously allocated enemies
   * 
   */
  void Priv_Free();
};
