#include "highscores.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

Highscores::Highscores(const std::string& filename)
    : m_filename(filename), m_saved(false) {
  Priv_LoadHighscores();
}

std::vector<std::string> Highscores::GetTop10() {
  std::vector<std::string> top10;
  for (int32_t i = 0; i < std::min(static_cast<int32_t>(m_highscores.size()), 10); i++) {
    std::stringstream line;
    line << std::to_string(i + 1) << ". ";
    line << std::get<0>(m_highscores[i]) << ": ";
    line << std::to_string(std::get<1>(m_highscores[i])) << " (";
    switch (std::get<2>(m_highscores[i])) {
      case 0:
        line << "easy)" << std::flush;
        break;
      case 1:
        line << "medium)" << std::flush;
        break;
      case 2:
        line << "hard)" << std::flush;
        break;
      default:
        line << "unknown)" << std::flush;
        break;
    }
    top10.push_back(line.str());
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

bool Highscores::AddScore(const std::string& name, uint32_t score,
                          Difficulty difficulty) {
  // Check if the score is already saved
  if (!m_saved) {
    // Append new score to end of file
    std::ofstream os(m_filename, std::ios::app);
    os << name << ":" << score << ":" << difficulty << std::endl;
    m_saved = true;
    // Add new score to vector and sort it
    m_highscores.push_back(std::make_tuple(name, score, difficulty));
    Priv_SortHighscores();
    return true;
  } else {
    return false;
  }
}

void Highscores::Priv_LoadHighscores() {
  try {
    std::ifstream is(m_filename);
    for (std::string line; getline(is, line);) {
      int32_t firstSplit = line.find_first_of(':');
      int32_t secondSplit = line.find_last_of(':');
      std::string name = line.substr(0, firstSplit);
      uint32_t score = std::stoul(line.substr(firstSplit + 1, secondSplit));
      Difficulty difficulty = static_cast<Difficulty>(
          std::stoi(line.substr(secondSplit + 1, line.size() - 1)));
      m_highscores.push_back(std::make_tuple(name, score, difficulty));
    }

  } catch (...) {
    std::cerr << "Loading highscores failed." << std::endl;
  }
  Priv_SortHighscores();
}

void Highscores::Priv_SortHighscores() {
  std::sort(m_highscores.begin(), m_highscores.end(),
            [](std::tuple<std::string, uint32_t, Difficulty> a,
               std::tuple<std::string, uint32_t, Difficulty> b) {
              return std::get<1>(a) > std::get<1>(b);
            });
}