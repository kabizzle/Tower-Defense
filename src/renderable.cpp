#include "renderable.hpp"

Renderable::Renderable(const std::string& imageName)
  : m_imageName(std::string(IMGDIR) + "/" + imageName) { }

const std::string& Renderable::ImgPath() const {
  return m_imageName;
}

//g++ -std=c++17 -o testi ../tests/enemy_factory_test.cpp enemy_factory.cpp assignment.cpp renderable.cpp