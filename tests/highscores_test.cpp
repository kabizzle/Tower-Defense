#include <fstream>
#include <iostream>

#include "../src/highscores.hpp"

int main() {
    std::ofstream os("highscores_testfile.txt", std::ios::trunc);
    os << "asd:123" << std::endl;
    os << "qwerty:456" << std::endl;
    os.close();

    std::cout << "Testing loading of high scores and printing top scores:" << std::endl;
    Highscores hs("highscores_testfile.txt");
    for (auto line : hs.GetTop10()) std::cout << line << std::endl;

    std::cout << "Testing adding of new score:" << std::endl;
    hs.AddScore("zxc", 789);
    for (auto line : hs.GetTop10()) std::cout << line << std::endl;

    std::cout << "Testing that new score can only be saved once:" << std::endl;
    hs.AddScore("lol", 0);
    for (auto line : hs.GetTop10()) std::cout << line << std::endl;

    std::cout << "Testing that creating new Highscore object with same file works:" << std::endl;
    Highscores hs2("highscores_testfile.txt");
    for (auto line : hs2.GetTop10()) std::cout << line << std::endl;

    return 0;
}