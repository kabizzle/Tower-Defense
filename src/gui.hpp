#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief A class to add elements to the Graphical User Interface
 * 
 */
class GUI {
public:
    // Constructor
    GUI();

    // Destructor
    ~GUI();
    
    // Initialise variables
    void init();

    // create window
    void render();

    // determine if gui is open
    bool running();

    // Detect events in gui window
    void pollEvents();

    // Renders changed to gui window
    void update();

    // Adds enemy object to gui window
    //TODO: configure with Enemy class
    void addEnemy();

    // move enemy
    void moveEnemies();

private:
    sf::RenderWindow* m_window; // window that displays game
    sf::VideoMode m_videoMode; // dimensions of window
    sf::Event m_event; // events that occur in gui window
    std::vector<sf::RectangleShape> enemies; // list of enemy objects
    float x_velo = 3.f;
    float y_velo = 4.f;

};