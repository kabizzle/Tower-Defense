#include "renderables.hpp"

Renderables::Renderables() {
    if (!bachelor_1.loadFromFile("src/images/bachelor.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!bachelor_2.loadFromFile("src/images/bachelor.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }
}