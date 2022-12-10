#pragma once 

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

/**
 * @brief A class which handles the textures for different sprites
 * One instance of this class must be constructed somewhere in the code
 * before any static getters are accessed!
 */
class Renderables {
public:
    Renderables();

    static sf::Sprite& getBachelor1Sprite();
    static sf::Sprite& getBachelor2Sprite();
    static sf::Sprite& getBachelor3Sprite();
    static sf::Sprite& getBachelorsThesisSprite();
    static sf::Sprite& getBackgroundSprite();
    static sf::Sprite& getBscSprite();
    static sf::Sprite& getCalculatorSprite();
    static sf::Sprite& getCoffeeTableSprite();
    static sf::Sprite& getDoctor1Sprite();
    static sf::Sprite& getDoctor2Sprite();
    static sf::Sprite& getDoctor3Sprite();
    static sf::Sprite& getDoctoralThesisSprite();
    static sf::Sprite& getDscSprite();
    static sf::Sprite& getEndtileSprite();
    static sf::Sprite& getEssaySprite();
    static sf::Sprite& getFreshman1Sprite();
    static sf::Sprite& getFreshman2Sprite();
    static sf::Sprite& getFreshman3Sprite();
    static sf::Sprite& getHomeworkSprite();
    static sf::Sprite& getMaster1Sprite();
    static sf::Sprite& getMaster2Sprite();
    static sf::Sprite& getMaster3Sprite();
    static sf::Sprite& getMastersThesisSprite();
    static sf::Sprite& getMenuBackgroundSprite();
    static sf::Sprite& getMscSprite();
    static sf::Sprite& getPathtileSprite();
    static sf::Sprite& getProjectSprite();
    static sf::Sprite& getStarttileSprite();
    static sf::Sprite& getTeekkari1Sprite();
    static sf::Sprite& getTeekkari2Sprite();
    static sf::Sprite& getTeekkari3Sprite();
    static sf::Sprite& getTowertileSprite();
    static sf::Sound& getAttackSound();
    static sf::Sound& getSelectSound();

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
    sf::Texture menu_background;
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
    sf::Sprite menu_background_sprite;
    sf::Sprite msc_sprite;
    sf::Sprite pathTile_sprite;
    sf::Sprite project_sprite;
    sf::Sprite startTile_sprite;
    sf::Sprite teekkari_1_sprite;
    sf::Sprite teekkari_2_sprite;
    sf::Sprite teekkari_3_sprite;
    sf::Sprite towerTile_sprite;

    sf::SoundBuffer attack;
    sf::SoundBuffer select;

    sf::Sound attack_sound;
    sf::Sound select_sound;

    /**
     * @brief A static pointer to an instance of this class
     * Is initialized when an instance is constructed somewhere in the program
     */
    static Renderables* s_instance;
};


