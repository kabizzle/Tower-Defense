#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief A class to add elements to the Graphical User Interface
 * 
 */
class GUI {
public:
    explicit GUI(sf::RenderWindow& window);
    void draw_display();

private:
    sf::RenderWindow& m_window; // window that displays game
};