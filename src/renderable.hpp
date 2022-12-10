#pragma once

#include <string>
#include "renderables.hpp"

/**
 * @brief A class which encapsulates the renderable objects (enemies and towers)
 * Is not supposed to be directly instanciated, so the constructor is protected
 */
class Renderable
{
public:
  /**
   * @brief A virtual destructor
   */
  virtual ~Renderable() { }

  /**
   * @brief Get the name of the entity
   * Mainly for debugging
   * @return const std::string&
   */
  const std::string& EntityName() const;

  /**
   * @brief Get the Sprite of this entity
   * For rendering purposes
   * @return sf::Sprite& 
   */
  sf::Sprite& GetSprite();

protected:
  std::string m_entityName;
  sf::Sprite m_sprite;

  //Protected functions

  /**
   * @brief Construct a new Renderable object
   * @param entityName The name
   * @param sprite The sprite used by the entity
   */
  Renderable(const std::string& entityName, const sf::Sprite& sprite);

  /**
   * @brief Set the Sprite object
   * Used by the towers when they are upgraded
   * @param newSprite A ref to the new sprite
   */
  void SetSprite(const sf::Sprite& newSprite);
};