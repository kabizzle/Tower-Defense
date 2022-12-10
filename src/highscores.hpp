#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "enemy_factory.hpp"

/**
 * @brief A class used to handle the high score savings at the end of game
 */
class Highscores {
public:
  /**
   * @brief Construct a new Highscores object. Loads and sorts saved high scores.
   * @param filename name of the file containing high scores.
   */
  Highscores(const std::string& filename = "highscores.txt");

  /**
   * @brief Default destructor
   */
  ~Highscores() = default;
  
  /**
   * @brief Get the top 10 of high scores.
   * 
   * @return std::vector<std::string> A vector of strings in format "<ranking>. <name>: <score> (<difficulty>)"
   */
  std::vector<std::string> GetTop10();

  /**
   * @brief Get the top 10 of high scores as string.
   * 
   * @return std::string with all scores in format "<ranking>. <name>: <score> (<difficulty>)" seperated by newline
   */
  std::string GetTop10asString();

  /**
   * @brief Saves new score to highscores. Can be only done once.
   * 
   * @param name name of the player, cannot contain ':'
   * @param score  score of the player
   * @param difficulty difficulty of the game
   * @return bool if adding score was successful
   */
  bool AddScore(const std::string& name, uint32_t score, Difficulty difficulty);

private:
  std::vector<std::tuple<std::string, uint32_t, Difficulty>> m_highscores;
  std::string m_filename;
  bool m_saved;

  //Private functions

  /**
   * @brief Private. Helper function to load the scores
   */
  void Priv_LoadHighscores();

  /**
   * @brief Private. Helper function to sort the scores
   */
  void Priv_SortHighscores();
};