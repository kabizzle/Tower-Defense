#pragma once
#include "../game.hpp"
#include "state.hpp"

/**
 * @brief GameState class runs and draws the game part of the software.
 */
class GameState : public State {
 public:
  /**
   * @brief Construct a new Game State object
   *
   * @param gui A ref to the GUI
   * @param window A ref to the window
   * @param difficulty The game difficulty
   * @param filename The name of the map file
   */
  GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
            const std::string& filename);

  /**
   * @brief Destroy the Game State object
   * Frees the buttons
   */
  ~GameState();

  /**
   * @brief Run and draw the game state. (Hosts the loop that Polls GUI events,
   * calls the necessary backend methods and draws the window. Alternates
   * between the building/upgrading phase and running the waves.)
   * Exits the loop and calls GUIs MoveToEndState(int score) when the game is
   * over.
   */
  void Run();

 private:
  bool m_gameOver, m_buildPhase, m_drawRange, m_drawUpgradeRange;
  uint32_t m_roundNum, m_gameSpeed;
  int32_t m_frameInTick;
  Game m_gameLogic;
  std::vector<sf::Sprite> m_mapTileSprites;
  std::map<int32_t, Button*> m_buttons;
  sf::RectangleShape m_selectedShape;
  sf::Text m_scoreText;
  sf::Text m_healthText;
  sf::Text m_moneyText;
  sf::Text m_roundNumText;
  sf::CircleShape m_rangeCircle;
  sf::CircleShape m_upgradeRange;
  sf::CircleShape m_projectile;
  int32_t m_selX,
      m_selY;  // The selected tile on the map, -1, -1 means nothing selected

  // Private functions
  /**
   * @brief Polls the events that have happened in GUI
   */
  void Priv_PollEvents();

  /**
   * @brief Draws the frame to the screen
   */
  void Priv_Draw();

  /**
   * @brief Draws the background to the window
   * Assumes that the window has been properly cleared
   */
  void Priv_DrawBCG();

  /**
   * @brief Draws the map to the window. Assumes
   * that the window has been properly cleared.
   */
  void Priv_DrawMap();


  /**
   * @brief Initializes some text at set location
   * 
   * @param text The text to initialize
   * @param x x-coordinate
   * @param y y-coordinate
   */
  void Priv_InitializeText(sf::Text& text, int32_t x, int32_t y);

  /**
   * @brief Clears highlights from the game speed buttons
   */
  void Priv_ClearSpeedHighlights();

  /**
   * @brief Sets a circle at desired position
   * Used to draw ranges of towers
   * @param circle The cirle used in drawing
   * @param range The range to draw
   */
  void Priv_ChangeCircle(sf::CircleShape& circle, u_int32_t range);
};
