#include "gamestate.hpp"

#include "button.hpp"
#include "endstate.hpp"
#include "game.hpp"

#define ANIMATION_LENGTH 10  // 30 frames is 1/2 second
#define TILE_SIZE 30

GameState::GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
                     const std::string& filename)
    : State(gui, window),
      m_gameOver(false),
      m_buildPhase(true),
      m_roundNum(0),
      m_frameInTick(0),
      m_gameLogic(Game(30, 20, filename, difficulty)),
      m_selX(-1),
      m_selY(-1) {
  // Initialize the map tiles
  for (auto& [coords, tile] : m_gameLogic.GetMap().GetGrid()) {
    sf::Sprite sprite;
    switch (tile) {
      case towerTile:
        sprite = Renderables::getTowertileSprite();
        break;
      case startTile:
        sprite = Renderables::getStarttileSprite();
        break;
      case pathTile:
        sprite = Renderables::getPathtileSprite();
        break;
      case endTile:
        sprite = Renderables::getEndtileSprite();
        break;
    }
    sprite.setPosition(TILE_SIZE * coords.first, TILE_SIZE * coords.second);
    m_mapTileSprites.push_back(sprite);
  }

  // Initialize the buttons
  m_buttons[Action::BuyFreshman] = m_gui.createButton("Freshman", 915, 15);
  m_buttons[Action::BuyTeekkari] = m_gui.createButton("Teekkari", 915, 55);
  m_buttons[Action::BuyBachelor] = m_gui.createButton("Bachelor", 915, 95);
  m_buttons[Action::BuyMaster] = m_gui.createButton("Master", 915, 135);
  m_buttons[Action::BuyDoctor] = m_gui.createButton("Doctor", 915, 175);
  m_buttons[Action::BuyCalculator] = m_gui.createButton("Calculator", 915, 215);
  m_buttons[Action::BuyCoffeeTable] =
      m_gui.createButton("CoffeeTable", 915, 255);
  m_buttons[Action::UpgradeTower] =
      m_gui.createButton("Upgrade selected tower", 915, 295);
  m_buttons[Action::DestroyTower] =
      m_gui.createButton("Destroy selected tower", 915, 335);
  m_buttons[9 /* The next int after last enum */] =
      m_gui.createButton("Quit", 915, 670);
  m_buttons[10] = m_gui.createButton("Advance to the next round", 915, 620);
}

void GameState::Run() {
  this->PollEvents();
  this->Draw();
  // If the game is over, we change the state to endstate
  if (m_gameOver) {
    m_gui.changeState(
        new EndState(m_gui, m_window, 15 /* m_gameLogic.GetScore()*/));
  }
}

void GameState::PollEvents() {
  if (m_buildPhase) {
    // PollEvents in the Build phase
    while (m_window.pollEvent(m_event)) {
      if (m_event.type == sf::Event::Closed) m_window.close();

      if (this->m_event.type == sf::Event::MouseButtonPressed) {
        if (this->m_event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "the left button was pressed" << std::endl;
          sf::Vector2f mouse =
              m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
          // Check if the mouse press was inside the map area
          int32_t xInt = static_cast<int32_t>(mouse.x);
          int32_t yInt = static_cast<int32_t>(mouse.y);
          if (xInt < 900 && yInt < 600) {
            // Find which tile is selected
            int32_t gridX = xInt / TILE_SIZE;
            int32_t gridY = yInt / TILE_SIZE;
          } else {
            for (auto b : m_buttons) {
              if (!b.second->getGlobalBounds().contains(mouse)) continue;

              switch (b.first) {
                case Action::BuyFreshman:

                  break;
                case Action::BuyTeekkari:

                  break;
                case Action::BuyBachelor:

                  break;
                case Action::BuyMaster:

                  break;
                case Action::BuyDoctor:

                  break;
                case Action::BuyCalculator:

                  break;
                case Action::BuyCoffeeTable:

                  break;
                case Action::UpgradeTower:

                  break;
                case Action::DestroyTower:

                  break;
                case 9:
                  m_gui.changeState(new EndState(
                      m_gui, m_window, 15 /* m_gameLogic.GetScore()*/));
                  m_buttons[0]->addHighlight();
                  break;
                case 10:
                  // Advance to the next wave
                  m_roundNum = m_gameLogic.StartNextRound();
                  m_frameInTick = 0;
                  m_buildPhase = false;
                  break;
              }
            }
          }
        }
      }
    }
  } else {
    // PollEvents in the Wave phase
    while (m_window.pollEvent(m_event)) {
      if (m_event.type == sf::Event::Closed) m_window.close();
      if (this->m_event.type == sf::Event::MouseButtonPressed) {
        if (this->m_event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "the left button was pressed" << std::endl;
          sf::Vector2f mouse =
              m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

          for (auto b : m_buttons) {
            if (!b.second->getGlobalBounds().contains(mouse)) continue;

            switch (b.first) {
              case 9:
                m_gui.changeState(new EndState(m_gui, m_window,
                                               15 /* m_gameLogic.GetScore()*/));
                m_buttons[0]->addHighlight();
                break;
            }
          }
        }
      }
    }
  }
}

void GameState::Draw() {
  m_window.clear();
  // Draw the background and shared information between the phases
  Priv_DrawBCG();

  // Draw the rest depending on the phase the game is on.
  if (m_buildPhase) {
    // DRAW THE BUILD PHASE:

    // Draw the towers
    for (auto* at : m_gameLogic.GetAttackingTowers()) {
      m_window.draw(at->GetSprite());
    }
    for (auto* st : m_gameLogic.GetSupportTowers()) {
      m_window.draw(st->GetSprite());
    }

    // Draw the buttons
    for (auto b : m_buttons) {
      b.second->drawButton(m_window);
    }

  } else {
    // DRAW THE WAVE PHASE:

    // The game logic is advanced only once per second
    if (m_frameInTick == 0) {
      // call enemyturn and check if game is over
      if (!m_gameLogic.EnemyTurn()) {
        m_gameOver = true;
        return;
      }
      // call tower turn
      m_gameLogic.TowerTurn();
      if (m_gameLogic.RoundIsFinished()) {
        m_buildPhase = true;
        return;
      }
    }
    // Draw everything

    // Quit button
    m_buttons[9]->drawButton(m_window);

    // Towers
    for (auto* at : m_gameLogic.GetAttackingTowers()) {
      m_window.draw(at->GetSprite());
    }
    for (auto* st : m_gameLogic.GetSupportTowers()) {
      m_window.draw(st->GetSprite());
    }

    // Draw attacks? A sprite for these?
    // m_gameLogic.GetAttacks() (WIP)

    // Enemies
    auto& enemyVec = m_gameLogic.GetEnemies();
    const auto& path = m_gameLogic.GetMap().GetPath();
    for (size_t i = 0; i < enemyVec.size(); i++) {
      for (auto* e : enemyVec[i]) {
        // Check if the enemy has moved or if it is stationary now
        auto& coords = path[i];
        int32_t x = coords.first * TILE_SIZE, y = coords.second * TILE_SIZE;
        if (e->MovedLastTick()) {
          // Must be drawn between the last and current positions
          if (i == 0) {
            std::cerr << "Tried to animate enemies before start" << std::endl;
            continue;
          }
          // Debug
          // std::cout << "Intermediate position" << std::endl;
          // Previous coordinate
          auto& prev = path[i - 1];
          int32_t xP = prev.first * TILE_SIZE, yP = prev.second * TILE_SIZE;
          //(1-t)*x_1 + t*x_2
          // x_1-t*x_1 + t*x_2    t = f/AL
          // x_1-f*x_1/Al + f*x_2/Al
          // x_1+f*(-x_1 + x_2)/Al
          x = xP + m_frameInTick * (x - xP) / ANIMATION_LENGTH;
          y = yP + m_frameInTick * (y - yP) / ANIMATION_LENGTH;
        }
        auto& sprite = e->GetSprite();
        sprite.setPosition(x, y);
        m_window.draw(sprite);
      }
    }
    // Increment / reset the frame counter
    m_frameInTick = (m_frameInTick >= ANIMATION_LENGTH) ? 0 : m_frameInTick + 1;
  }

  // Display (shared)
  m_window.display();
}

void GameState::Priv_DrawBCG() {
  const auto& bcg = Renderables::getBackgroundSprite();
  m_window.draw(bcg);
  for (const auto& s : m_mapTileSprites) {
    m_window.draw(s);
  }
}
