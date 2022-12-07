#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Highscores {
public:
    /**
     * @brief Construct a new Highscores object. Loads and sorts saved high scores.
     * 
     * @param filename name of the file containing high scores.
     */
    Highscores(const std::string& filename = "../highscores.txt");

    /**
     * @brief Get the top 10 of high scores.
     * 
     * @return vector of strings in format "<ranking>. <name> <score>"
     */
    std::vector<std::string> GetTop10();

    /**
     * @brief Saves new score to highscores. Can be only done once.
     * 
     * @param name name of the player, cannot contain ':'
     * @param score  score of the player
     * @return if adding score was successful
     */
    bool AddScore(const std::string& name, uint32_t score);

private:
    std::vector<std::pair<std::string, uint32_t>> m_highscores;
    std::string m_filename;
    bool m_saved;

    void Priv_LoadHighscores();
    void Priv_SortHighscores();
};