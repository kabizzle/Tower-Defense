#pragma once 

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

class Renderables {
public:
    Renderables();

    sf::Sprite& getBachelor1Sprite();
    sf::Sprite& getBachelor2Sprite();
    sf::Sprite& getBachelor3Sprite();
    sf::Sprite& getBachelorsThesisSprite();
    sf::Sprite& getBackgroundSprite();
    sf::Sprite& getBscSprite();
    sf::Sprite& getCalculatorSprite();
    sf::Sprite& getCoffeeTableSprite();
    sf::Sprite& getDoctor1Sprite();
    sf::Sprite& getDoctor2Sprite();
    sf::Sprite& getDoctor3Sprite();
    sf::Sprite& getDoctoralThesisSprite();
    sf::Sprite& getDscSprite();
    sf::Sprite& getEndtileSprite();
    sf::Sprite& getEssaySprite();
    sf::Sprite& getFreshman1Sprite();
    sf::Sprite& getFreshman2Sprite();
    sf::Sprite& getFreshman3Sprite();
    sf::Sprite& getHomeworkSprite();
    sf::Sprite& getMaster1Sprite();
    sf::Sprite& getMaster2Sprite();
    sf::Sprite& getMaster3Sprite();
    sf::Sprite& getMastersThesisSprite();
    sf::Sprite& getMscSprite();
    sf::Sprite& getPathtileSprite();
    sf::Sprite& getProjectSprite();
    sf::Sprite& getStarttileSprite();
    sf::Sprite& getTeekkari1Sprite();
    sf::Sprite& getTeekkari2Sprite();
    sf::Sprite& getTeekari3Sprite();
    sf::Sprite& getTowertileSprite();

private:
    sf::Texture bachelor_1;
    sf::Texture bachelor_2;
    sf::Texture bachelor_3;
    sf::Texture bachelors_thesis;
    sf::Texture background;
    sf::Texture bsc;
    sf::Texture calculator;
    sf::Texture coffee_table;
    sf::Texture doctor_1;
    sf::Texture doctor_2;
    sf::Texture doctor_3;
    sf::Texture doctoral_thesis;
    sf::Texture dsc;
    sf::Texture endTile;
    sf::Texture essay;
    sf::Texture freshman_1;
    sf::Texture freshman_2;
    sf::Texture freshman_3;
    sf::Texture homework;
    sf::Texture master_1;
    sf::Texture master_2;
    sf::Texture master_3;
    sf::Texture masters_thesis;
    sf::Texture msc;
    sf::Texture pathTile;
    sf::Texture project;
    sf::Texture startTile;
    sf::Texture teekkari_1;
    sf::Texture teekkari_2;
    sf::Texture teekkari_3;
    sf::Texture towerTile;

    sf::Sprite bachelor_1_sprite;
    sf::Sprite bachelor_2_sprite;
    sf::Sprite bachelor_3_sprite;
    sf::Sprite bachelors_thesis_sprite;
    sf::Sprite background_sprite;
    sf::Sprite bsc_sprite;
    sf::Sprite calculator_sprite;
    sf::Sprite coffee_table_sprite;
    sf::Sprite doctor_1_sprite;
    sf::Sprite doctor_2_sprite;
    sf::Sprite doctor_3_sprite;
    sf::Sprite doctoral_thesis_sprite;
    sf::Sprite dsc_sprite;
    sf::Sprite endTile_sprite;
    sf::Sprite essay_sprite;
    sf::Sprite freshman_1_sprite;
    sf::Sprite freshman_2_sprite;
    sf::Sprite freshman_3_sprite;
    sf::Sprite homework_sprite;
    sf::Sprite master_1_sprite;
    sf::Sprite master_2_sprite;
    sf::Sprite master_3_sprite;
    sf::Sprite masters_thesis_sprite;
    sf::Sprite msc_sprite;
    sf::Sprite pathTile_sprite;
    sf::Sprite project_sprite;
    sf::Sprite startTile_sprite;
    sf::Sprite teekkari_1_sprite;
    sf::Sprite teekkari_2_sprite;
    sf::Sprite teekkari_3_sprite;
    sf::Sprite towerTile_sprite;
};


class Button {
public: 
    Button(std::string text, int x, int y);

private:
    sf::Sprite m_button;
};