#include "gamestate.hpp"

#include "button.hpp"
#include "endstate.hpp"
#include "game.hpp"

#define ANIMATION_LENGTH 10  // 30 frames is 1/2 second
#define TILE_SIZE 30
#define PROJECTILE_RADIUS 5

GameState::GameState(GUI& gui, sf::RenderWindow& window, Difficulty difficulty,
                     const std::string& filename)
    : State(gui, window),
      m_gameOver(false),
      m_buildPhase(true),
      m_roundNum(0),
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
    //Projectile color
    m_projectile.setFillColor(sf::Color(255, 0, 0));
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
      m_gui.createButton("Give up", 915, 670);
  m_buttons[10] = m_gui.createButton("Advance to the next round", 915, 620);

  // Initialize the selected tile square shape
  m_selectedShape = sf::RectangleShape(sf::Vector2f(30, 30));
  m_selectedShape.setFillColor(sf::Color(0, 255, 255, 64));
  m_selectedShape.setOutlineThickness(4);
  m_selectedShape.setOutlineColor(sf::Color::Cyan);
}

void GameState::Run() {
  this->PollEvents();
  this->Draw();
  // If the game is over, we change the state to endstate
  if (m_gameOver) {
    m_gui.changeState(new EndState(m_gui, m_window, m_gameLogic.GetScore()));
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
                  break;
                case Action::DestroyTower:
                  m_gameLogic.DestroyTower(std::make_pair(m_selX, m_selY));
                  break;
                case 9:
                  m_gui.changeState(new EndState(m_gui, m_window, m_gameLogic.GetScore()));
                  m_buttons[9]->addHighlight();
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
                m_gui.changeState(
                    new EndState(m_gui, m_window, m_gameLogic.GetScore()));
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

    // Draw the selected tile square
    if (m_selX >= 0 || m_selY >= 0) {
      m_selectedShape.setPosition(
          sf::Vector2f(m_selX * TILE_SIZE, m_selY * TILE_SIZE));
      m_window.draw(m_selectedShape);
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

    // Quit button
    m_buttons[9]->drawButton(m_window);

    // Towers
    for (auto* at : m_gameLogic.GetAttackingTowers()) {
      m_window.draw(at->GetSprite());
    }
    for (auto* st : m_gameLogic.GetSupportTowers()) {
      m_window.draw(st->GetSprite());
    }

    // Draw attacks
    for(const auto& [from, to]: m_gameLogic.GetAttacks()){
      int32_t x = from.first * TILE_SIZE, y = from.second * TILE_SIZE;
      int32_t x2 = to.first * TILE_SIZE, y2 = to.second * TILE_SIZE;
      x = x + m_frameInTick * (x2 - x) / ANIMATION_LENGTH;
      y = y + m_frameInTick * (y2 - y) / ANIMATION_LENGTH;
      m_projectile.setPosition(x + TILE_SIZE / 2 - PROJECTILE_RADIUS, y + TILE_SIZE / 2 - PROJECTILE_RADIUS);
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
