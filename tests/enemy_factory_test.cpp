#include <iostream>

#include "../src/enemy_factory.hpp"


int main() {
  std::cout << "CREATING AN ENEMY FACTORY" <<std::endl;
  EnemyFactory ef(Difficulty::Easy);
  std::cout << ef;
  std::cout << "GETTING THE FIRST ROUND" <<std::endl;
  ef.NextRoundInit();
  std::cout << ef;
  std::cout << "GETTING MORE ROUNDS" <<std::endl;
  for(uint32_t r = 2; r < 100; r++){
    ef.NextRoundInit();
    std::cout << ef;
  }
  std::cout << "TEST DONE" <<std::endl;
}