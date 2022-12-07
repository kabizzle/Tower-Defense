#include "endstate.hpp"

EndState::EndState(GUI& gui, sf::RenderWindow& window, uint32_t score)
    :   State(gui, window), m_score(score) {
    // Create buttons
    m_buttons[0] = m_gui.createButton("Main Menu", 30, 30);
    m_buttons[1] = m_gui.createButton("Save score", 30, 70);

    // Create Text objects
    m_text_score.setString("Your score: " + std::to_string(m_score));
    m_text_score.setPosition(30, 110);
    m_text_name.setString("Your name: ");
    m_text_name.setPosition(30, 150);
    m_text_highscores.setString(m_highscores.GetTop10asString());
    m_text_highscores.setPosition(30, 190);
}

EndState::~EndState() {
    for (auto b : m_buttons) {
        delete b.second;
    }
}

void EndState::Priv_PollEvents() {
    while(m_window.pollEvent(m_event)) {
        // Check if the window has been closed
        if (m_event.type == sf::Event::Closed) m_window.close();

        // Check if any button has been pressed
        if (m_event.type == sf::Event::MouseButtonPressed) {
            if (m_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                for (auto b : m_buttons) {
                    if (!b.second->getGlobalBounds().contains(mousePos)) continue; 

                    switch (b.first)
                    {
                    case 0:
                        // Go to Main Menu
                        break;
                    case 1:
                        // Save the score if name is not empty
                        if (!m_input.empty()) m_highscores.AddScore(m_input, m_score);
                        // Update top 10
                        m_text_highscores.setString(m_highscores.GetTop10asString());
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        // Check if text has been entered
        if (m_event.type == sf::Event::TextEntered) {
            char c = static_cast<char>(m_event.text.unicode);
            if (isalpha(c) || c == ' ') {
                m_input += c;
                m_text_name.setString("Your name: " + m_input);
            }
        }

        // Check if backspace has been pressed
        if (m_event.type == sf::Event::KeyPressed) {
            if (m_event.key.code == sf::Keyboard::Backspace) {
                m_input.pop_back();
            }
        }
    }

}

void EndState::Priv_Draw() {
    // Clear background to white
    m_window.clear(sf::Color::White);

    // Draw buttons
    for (auto b : m_buttons) b.second->drawButton(m_window);

    // Draw text objects
    m_window.draw(m_text_name);
    m_window.draw(m_text_score);
    m_window.draw(m_text_highscores);
}

void EndState::Run() {
    Priv_PollEvents();
    Priv_Draw();
}