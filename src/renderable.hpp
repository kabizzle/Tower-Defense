#pragma once

#include <string>

#define IMGDIR "/placeholder"

/**
 * @brief A class which encapsulates the renderable objects (enemies and towers)
 * 
 */
class Renderable
{
public:
  /**
   * @brief Returns the path to the image of this renderable object, for rendering purposes
   * 
   * @return Path to the image for rendering purposes
   */
  const std::string& ImgPath() const;

protected:
  Renderable(const std::string& imageName)
    : m_imageName(imageName) { }
  ~Renderable();

private:
  std::string m_imageName;
};