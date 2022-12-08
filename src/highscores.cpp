#include <algorithm>
#include <fstream>
#include <sstream>

#include "highscores.hpp"

#include <iostream>

Highscores::Highscores(const std::string& filename)
    : m_filename(filename), m_saved(false) {
    Priv_LoadHighscores();
}

std::vector<std::string> Highscores::GetTop10() {
    std::vector<std::string> top10;
    for (int i = 0; i < std::min((int) m_highscores.size(), 10); i++) {
        std::string line = std::to_string(i + 1) + ". " + m_highscores[i].first + " " + std::to_string(m_highscores[i].second);
        top10.push_back(line);
    }
    return top10;
}

std::string Highscores::GetTop10asString() {
    std::stringstream ss;
    for (auto line : GetTop10()) {
        ss << line << std::endl;
    }
    return ss.str();
}

bool Highscores::AddScore(const std::string& name, uint32_t score) {
    // Check if the score is already saved
    if (!m_saved) {
        // Append new score to end of file
        std::ofstream os(m_filename, std::ios::app);
        os << name << ":" << score << std::endl;
        os.close();
        m_saved = true;
        // Add new score to vector and sort it
        m_highscores.push_back(std::make_pair(name, score));
        Priv_SortHighscores();
        return true;
    } else {
        return false;
    }
}

void Highscores::Priv_LoadHighscores() {
    std::ifstream is(m_filename);
    for (std::string line; getline(is, line);) {
        int32_t splitAt = line.find(':');
        std::string name = line.substr(0, splitAt);
        uint32_t score = std::stoul(line.substr(splitAt + 1, line.size() - 1));
        m_highscores.push_back(std::make_pair(name, score));
    }
    is.close();
    Priv_SortHighscores();
}

void Highscores::Priv_SortHighscores() {
    std::sort(m_highscores.begin(), m_highscores.end(),
        [](std::pair<std::string, uint32_t> a, std::pair<std::string, uint32_t> b) {
            return a.second > b.second;
        });
}