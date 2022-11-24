#pragma once

#include <list>

// #include "degree.hpp"
#include "assignment.hpp"

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
 * This class allocates the enemies dynamically, and then the game logic class is responsible for freeing the memory when enemies either reach the
 * end or die
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
   * @brief Destroys the Enemy Factory object, if there were some enemies left in the storage, frees them
   */
  ~EnemyFactory();

  /**
   * @brief Initializes the enemies of the next round
   * After calling this, the enemies which come each tick can be obtained using NextTick()
   * Also frees the previously allocated enemies if the previous round for some reason did not finnish
   */
  void NextRoundInit();

  /**
   * @brief Used to get the enemies which appear on the next game tick
   * Removes them from the objects own collection, so the resposibility is
   * transferred to the object which calls the function
   * The max amound of enemies during the tick for round n is approximately base-2-log(a_n) + 1
   * where a_n is the element of the sequence used to determine the types present
   */
  std::list<Assignment*> NextTick();

  /**
   * @brief TODO initializes any round desired
   */
  void Round(uint32_t r);

  /**
   * @brief Creates an Enemy object
   * Can be used either by this class itself or by the game core to spawn the additional enemies at some location
   * @return A dynamically allocated enemy
   */
  Assignment* CreateEnemy(Enemy e) const;

  /**
   * @brief Tells which round is currently active (in initialized state)
   * 0 means that the first round has yet to be initialized
   */
  uint32_t GetRound() const;

  /**
   * @brief An overload for the stream operator for debugging purposes
   */
  friend std::ostream& operator<<(std::ostream& os, const EnemyFactory& ef);

private:
  Difficulty m_diff;
  uint32_t m_round;
  uint32_t m_nums[3] = {1, 1, 1};   //< Used in the internal logic to get the enemy composition of each round
  std::list<Assignment*> m_roundEnemies;
  uint32_t m_batchSizes[9] = {0}, m_batchSizeDeltas[9] = {10, 5, 3, 2, 2, 2, 1, 1, 1};

  //Private functions

  /**
   * @brief Uses m_nums to calculate the next one in the sequence
   * @return the next number in the sequence
   */
  uint32_t Priv_NextNum();

  /**
   * @brief Used by destructor to free the enemies which are left
   */
  void Priv_Free();
};
