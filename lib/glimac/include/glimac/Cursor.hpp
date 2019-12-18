#ifndef CURSOR_HPP 
#define CURSOR_HPP

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <glimac/Cube.hpp>
#include <glimac/common.hpp>

namespace glimac {

class Cursor:public Cube {

public:
    Cursor();
      glm::vec3 getCursorPos();
      void updatePosX(float direction);
      void updatePosY(float direction);
      void updatePosZ(float direction);
      void updateVertices();
      void renderCursor(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera);
      void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location,const ShaderProgram &shader2);

};

}

#endif 