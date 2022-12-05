#pragma once

#include <string>

#define IMGDIR "/placeholder"

/**
 * @brief A class which encapsulates the renderable objects (enemies and towers)
 * Is not supposed to be directly instanciated, so the constructor is protected
 */
class Renderable
{
public:
  /**
   * @brief Returns the path to the image of this renderable object, for rendering purposes
   * 
   * @return Path to the image for rendering purposes
   */
  const std::string ImgPath() const;

protected:
  Renderable(const std::string& imageName);

  /**
   * @brief Is used by the towers to alter the image name to update the look of upgraded towers
   */
  void AddSuffix(const std::string& suffix);

private:
  std::string m_imageName;
};