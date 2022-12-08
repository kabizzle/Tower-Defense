#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "renderables.hpp"
#include "button.hpp"

class State;

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

    // determine if gui is open
    bool running();

    // Detect events in gui window
    void pollEvents();

    // Renders changed to gui window
    void update();

    // move enemy
    void moveEnemies();


    Button* createButton(std::string text, int x, int y);

    sf::Font& GetFont();

    void changeState(State* state);

    void deleteState();
    
protected:
    Renderables* m_renderables;

private:
    sf::RenderWindow* m_window; // window that displays game
    sf::VideoMode m_videoMode; // dimensions of window
    sf::Event m_event; // events that occur in gui window
    std::vector<sf::Sprite> enemies; // list of enemy objects
    float x_velo = 3.f;
    float y_velo = 4.f;
    sf::Vector2f start;
    sf::Font m_font;
    State* m_state;
    State* m_new_state;

};

// void GUI::addEnemy(std::string type, sf::Vector2f pos) {
//   // if (!this->texture.loadFromFile("src/images/bachelor.png")) {
//   //   std::cout << "Error: Image not found" << std::endl;
//   //   return;
//   // }
//   sf::Texture texture;
//   this->textures.push_back(texture);
//   int size = this->textures.size();
//   if (this->textures_map.find(type) != this->textures_map.end()){
//     if (this->textures[size-1].loadFromFile(this->textures_map[type])) {
//       std::cout << "Error: Image not found" << std::endl; 
//       return;
//     }
//     sf::Sprite enemy(this->textures[size - 1]);
//     enemy.setPosition(pos);
//     this->enemies.push_back(enemy);
//   }
//   else {
//     std::cout << "Texture does not exist" << std::endl;
//     return;
//   }
// }