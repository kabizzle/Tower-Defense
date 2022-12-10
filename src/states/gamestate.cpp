#include "gamestate.hpp"

#include "button.hpp"
#include "endstate.hpp"
#include "game.hpp"

#define ANIMATION_LENGTH 20  // 30 frames is 1/2 second
#define TILE_SIZE 30
#define PROJECTILE_RADIUS 5

GameState::GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
                     const std::string& filename)
    : State(gui, window),
      m_gameOver(false),
      m_buildPhase(true),
      m_roundNum(0),
      m_gameSpeed(1),
      m_frameInTick(0),
      m_gameLogic(Game(30, 20, filename, difficulty)),
      m_projectile(sf::CircleShape(PROJECTILE_RADIUS)),
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
    // Projectile color
    m_projectile.setFillColor(sf::Color(255, 0, 0));
  }

  // Initialize the buttons
  m_buttons[Action::BuyFreshman] =
      m_gui.CreateTowerButton(TowerType::Freshman, 915, 15);
  m_buttons[Action::BuyTeekkari] =
      m_gui.CreateTowerButton(TowerType::Teekkari, 915, 55);
  m_buttons[Action::BuyBachelor] =
      m_gui.CreateTowerButton(TowerType::Bachelor, 915, 95);
  m_buttons[Action::BuyMaster] =
      m_gui.CreateTowerButton(TowerType::Master, 915, 135);
  m_buttons[Action::BuyDoctor] =
      m_gui.CreateTowerButton(TowerType::Doctor, 915, 175);
  m_buttons[Action::BuyCalculator] =
      m_gui.CreateTowerButton(TowerType::Calculator, 915, 215);
  m_buttons[Action::BuyCoffeeTable] =
      m_gui.CreateTowerButton(TowerType::CoffeeTable, 915, 255);
  m_buttons[Action::UpgradeTower] =
      m_gui.CreateButton("Upgrade tower", 915, 295);
  m_buttons[Action::DestroyTower] =
      m_gui.CreateButton("Destroy tower", 915, 335);
  m_buttons[9] = m_gui.CreateButton("Next round", 915, 620);
  // During both phases
  m_buttons[10] = m_gui.CreateButton("Give up", 915, 670);
  // During enemy phase
  m_buttons[11] = m_gui.CreateButton("Gamespeed 1x", 915, 15);
  m_buttons[12] = m_gui.CreateButton("Gamespeed 2x", 915, 55);
  m_buttons[13] = m_gui.CreateButton("Gamespeed 5x", 915, 95);
  m_buttons[14] = m_gui.CreateButton("Gamespeed 10x", 915, 135);
  m_buttons[15] = m_gui.CreateButton("Gamespeed 20x", 915, 175);

  // 1x speed is the default
  m_buttons[11]->addHighlight();

  // Initialize the selected tile square shape
  m_selectedShape = sf::RectangleShape(sf::Vector2f(30, 30));
  m_selectedShape.setFillColor(sf::Color(0, 255, 255, 64));
  m_selectedShape.setOutlineThickness(4);
  m_selectedShape.setOutlineColor(sf::Color::Cyan);

  // Initialize text for health, money and score
  Priv_InitializeText(m_roundNumText, 30, 624);
  Priv_InitializeText(m_healthText, 30, 672);
  Priv_InitializeText(m_moneyText, 400, 624);
  Priv_InitializeText(m_scoreText, 400, 672);

  // Initialize circles for drawing range
  m_rangeCircle.setFillColor(sf::Color::Transparent);
  m_rangeCircle.setOutlineThickness(4);
  m_rangeCircle.setOutlineColor(sf::Color::Black);
  m_upgradeRange.setFillColor(sf::Color::Transparent);
  m_upgradeRange.setOutlineThickness(4);
  m_upgradeRange.setOutlineColor(sf::Color::Green);
}

GameState::~GameState() {
  for (auto [i, button] : m_buttons) {
    delete button;
  }
}

void GameState::Run() {
  this->Priv_PollEvents();
  this->Priv_Draw();
  // If the game is over, we change the state to endstate
  if (m_gameOver) {
    m_gui.ChangeState(new EndState(m_gui, m_window, m_gameLogic.GetScore(),
                                   m_gameLogic.GetDifficulty()));
  }
}

void GameState::Priv_PollEvents() {
  if (m_buildPhase) {
    // PollEvents in the Build phase
    while (m_window.pollEvent(m_event)) {
      if (m_event.type == sf::Event::Closed) m_window.close();

      if (this->m_event.type == sf::Event::MouseButtonPressed) {
        if (this->m_event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mouse =
              m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
          // Check if the mouse press was inside the map area
          int32_t xInt = static_cast<int32_t>(mouse.x);
          int32_t yInt = static_cast<int32_t>(mouse.y);
          if (xInt < 900 && yInt < 600) {
            // Find which tile is selected
            m_selX = xInt / TILE_SIZE;
            m_selY = yInt / TILE_SIZE;

          } else {
            for (auto b : m_buttons) {
              if (!b.second->getGlobalBounds().contains(mouse)) continue;

              switch (b.first) {
                case Action::BuyFreshman:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Freshman);
                  break;
                case Action::BuyTeekkari:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Teekkari);
                  break;
                case Action::BuyBachelor:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Bachelor);
                  break;
                case Action::BuyMaster:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Master);
                  break;
                case Action::BuyDoctor:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Doctor);
                  break;
                case Action::BuyCalculator:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::Calculator);
                  break;
                case Action::BuyCoffeeTable:
                  m_gameLogic.CreateTower(std::make_pair(m_selX, m_selY),
                                          TowerType::CoffeeTable);
                  break;
                case Action::UpgradeTower:
                  m_gameLogic.UpgradeTower(std::make_pair(m_selX, m_selY));
                  // Draw uprage range only if it can be upgraded again
                  m_drawUpgradeRange = m_gameLogic.IsActionPossible(
                      std::make_pair(m_selX, m_selY), Action::UpgradeTower);
                  break;
                case Action::DestroyTower:
                  m_gameLogic.DestroyTower(std::make_pair(m_selX, m_selY));
                  break;
                case 9:
                  // Advance to the next wave
                  m_roundNum = m_gameLogic.StartNextRound();
                  m_frameInTick = 0;
                  m_buildPhase = false;
                  break;
                case 10:
                  m_gui.ChangeState(new EndState(m_gui, m_window,
                                                 m_gameLogic.GetScore(),
                                                 m_gameLogic.GetDifficulty()));
                  m_buttons[10]->addHighlight();
                  break;
                default:
                  // For to skip over some buttons only visible during enemy
                  // phase
                  break;
              }
            }
          }
        }
        // Don't draw range after mouse button is pressed
        m_drawRange = false;
      }
      // Check if the range circle has to be drawn
      if (m_event.type == sf::Event::MouseMoved) {
        // Reset to false
        m_drawRange = false;
        // Check if tower could be built to selected tile
        if (m_gameLogic.IsActionPossible(std::make_pair(m_selX, m_selY),
                                         Action::BuyFreshman)) {
          for (uint32_t action = 0; action <= 6; action++) {
            // Check if mouse is hovering at TowerButton
            if (m_buttons[action]->getGlobalBounds().contains(
                    m_event.mouseMove.x, m_event.mouseMove.y)) {
              m_drawRange = true;
              uint32_t range = TILE_SIZE * Tower::towerRanges.at(
                                               static_cast<TowerType>(action));
              Priv_ChangeCircle(m_rangeCircle, range);
            }
          }
        }
        m_drawUpgradeRange = false;
        // Check if tower can be upgraded in selected tile
        if (m_gameLogic.IsActionPossible(std::make_pair(m_selX, m_selY),
                                         Action::UpgradeTower)) {
          // Check if mouse is hovering at UpgradeButton
          if (m_buttons[Action::UpgradeTower]->getGlobalBounds().contains(
                  m_event.mouseMove.x, m_event.mouseMove.y)) {
            m_drawUpgradeRange = true;
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
          sf::Vector2f mouse =
              m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

          for (auto [i, button] : m_buttons) {
            if (!button->getGlobalBounds().contains(mouse)) continue;

            switch (i) {
              case 10:
                m_gui.ChangeState(new EndState(m_gui, m_window,
                                               m_gameLogic.GetScore(),
                                               m_gameLogic.GetDifficulty()));
                m_buttons[0]->addHighlight();
                break;
              case 11:
                m_gameSpeed = 1;
                Priv_ClearSpeedHighlights();
                button->addHighlight();
                break;
              case 12:
                m_gameSpeed = 2;
                Priv_ClearSpeedHighlights();
                button->addHighlight();
                break;
              case 13:
                m_gameSpeed = 5;
                Priv_ClearSpeedHighlights();
                button->addHighlight();
                break;
              case 14:
                m_gameSpeed = 10;
                Priv_ClearSpeedHighlights();
                button->addHighlight();
                break;
              case 15:
                m_gameSpeed = 20;
                Priv_ClearSpeedHighlights();
                button->addHighlight();
                break;
              default:
                // For those buttons which don't matter in this phase
                break;
            }
          }
        }
      }
    }
  }
  // Update text
  m_healthText.setString("Health: " + std::to_string(m_gameLogic.GetHealth()));
  m_moneyText.setString("Money: " + std::to_string(m_gameLogic.GetMoney()) +
                        " cr");
  m_scoreText.setString("Score: " + std::to_string(m_gameLogic.GetScore()));
  m_roundNumText.setString("Round:  " + std::to_string(m_roundNum));
}

void GameState::Priv_Draw() {
  m_window.clear();

  // Check which buttons must be enabled
  for (auto [i, button] : m_buttons) {
    // Only the ones where i < 9 need the checks to see if the buttons should be
    // grayed out
    if (i < 9) {
      if (m_gameLogic.IsActionPossible({m_selX, m_selY},
                                       static_cast<Action>(i))) {
        if (i == Action::UpgradeTower) {
          const AttackingTower* tower = static_cast<const AttackingTower*>(
              m_gameLogic.GetTower({m_selX, m_selY}));
          m_buttons[Action::UpgradeTower]->changeText(
              "Upgrade tower " + std::to_string(tower->GetUpgradeCost()) +
              "cr");
        }
        button->enableButton();
      } else {
        if (i == Action::UpgradeTower) {
          m_buttons[Action::UpgradeTower]->changeText("Upgrade tower");
        }
        button->disableButton();
      }
    }
  }

  // Draw the background and shared information between the phases
  Priv_DrawMap();

  // Draw the rest depending on the phase the game is on.
  if (m_buildPhase) {
    // DRAW THE BUILD PHASE:

    // Check if the selected tile contains tower
    const Tower* t = m_gameLogic.GetTower(std::make_pair(m_selX, m_selY));
    if (t) {
      m_drawRange = true;
      Priv_ChangeCircle(m_rangeCircle, TILE_SIZE * t->GetRange());
      if (m_drawUpgradeRange)
        Priv_ChangeCircle(m_upgradeRange, TILE_SIZE * (t->GetRange() + 2));
    }

    // Draw range of tower if needed
    if (m_drawRange) m_window.draw(m_rangeCircle);

    // Draw upgrade range if needed
    if (m_drawUpgradeRange) {
      m_window.draw(m_upgradeRange);
    }

    // Draw background and text
    Priv_DrawBCG();

    // Draw the towers
    for (auto* at : m_gameLogic.GetAttackingTowers()) {
      m_window.draw(at->GetSprite());
    }
    for (auto* st : m_gameLogic.GetSupportTowers()) {
      m_window.draw(st->GetSprite());
    }

    // Draw the selected tile square
    if (m_selX >= 0 || m_selY >= 0) {
      m_selectedShape.setPosition(
          sf::Vector2f(m_selX * TILE_SIZE, m_selY * TILE_SIZE));
      m_window.draw(m_selectedShape);
    }

    // Draw the buttons
    for (auto [i, button] : m_buttons) {
      if (i < 11) {
        button->drawButton(m_window);
      }
    }


  } else {
    // DRAW THE WAVE PHASE:

    // Draw background and text
    Priv_DrawBCG();

    // The game logic is advanced only once per second
    if (m_frameInTick == 0) {
      // call enemyturn and check if game is over
      if (!m_gameLogic.EnemyTurn()) {
        m_gameOver = true;
        return;
      }
      // call tower turn
      if (m_gameLogic.TowerTurn()) {
        // Play enemy death sound here
        Renderables::getAttackSound().play();
      }
      if (m_gameLogic.RoundIsFinished()) {
        m_buildPhase = true;
        m_gameSpeed = 1;
        Priv_ClearSpeedHighlights();
        m_buttons[11]->addHighlight();
        return;
      }
    }

    // Buttons
    for (auto [i, button] : m_buttons) {
      if (i >= 10) {
        button->drawButton(m_window);
      }
    }

    // Towers
    for (auto* at : m_gameLogic.GetAttackingTowers()) {
      m_window.draw(at->GetSprite());
    }
    for (auto* st : m_gameLogic.GetSupportTowers()) {
      m_window.draw(st->GetSprite());
    }

    // Draw attacks
    for (const auto& [from, to] : m_gameLogic.GetAttacks()) {
      int32_t x = from.first * TILE_SIZE, y = from.second * TILE_SIZE;
      int32_t x2 = to.first * TILE_SIZE, y2 = to.second * TILE_SIZE;
      x = x + m_frameInTick * (x2 - x) / ANIMATION_LENGTH;
      y = y + m_frameInTick * (y2 - y) / ANIMATION_LENGTH;
      m_projectile.setPosition(x + TILE_SIZE / 2 - PROJECTILE_RADIUS,
                               y + TILE_SIZE / 2 - PROJECTILE_RADIUS);
      m_window.draw(m_projectile);
    }

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
    m_frameInTick =
        (m_frameInTick >= ANIMATION_LENGTH) ? 0 : m_frameInTick + m_gameSpeed;
  }

  // Display (shared)
  m_window.display();
}

void GameState::Priv_DrawBCG() {
  const auto& bcg = Renderables::getBackgroundSprite();
  m_window.draw(bcg);
  // Draw health, money and score
  m_window.draw(m_healthText);
  m_window.draw(m_moneyText);
  m_window.draw(m_scoreText);
  m_window.draw(m_roundNumText);
}

void GameState::Priv_DrawMap() {
  for (const auto& s : m_mapTileSprites) {
    m_window.draw(s);
  }
}

void GameState::Priv_InitializeText(sf::Text& text, int32_t x, int32_t y) {
  text.setFont(m_gui.GetFont());
  text.setFillColor(sf::Color::White);
  text.setCharacterSize(24);
  text.setPosition(x, y);
}

void GameState::Priv_ClearSpeedHighlights() {
  for (auto [i, button] : m_buttons) {
    if (i > 10) {
      button->removeHighlight();
    }
  }
}

void GameState::Priv_ChangeCircle(sf::CircleShape& circle, uint32_t range) {
  circle.setRadius(range);
  circle.setOrigin(range, range);
  circle.setPosition(m_selX * TILE_SIZE + TILE_SIZE / 2,
                     m_selY * TILE_SIZE + TILE_SIZE / 2);
}