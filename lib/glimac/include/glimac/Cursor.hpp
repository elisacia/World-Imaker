#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <glimac/Cube.hpp>

#include <glimac/common.hpp>

using namespace glimac;


class Cursor:public Cube {

public:
    Cursor();
      glm::vec3 getCursorPos();
      void updatePosX(float direction);
      void updatePosY(float direction);
      void updatePosZ(float direction);
      void updateVertices();
      void renderCursor(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, FreeFlyCamera &camera);
      void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, ShaderProgram &shader2);

};