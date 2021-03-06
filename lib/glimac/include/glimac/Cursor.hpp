#ifndef CURSOR_HPP 
#define CURSOR_HPP

#pragma once

#include <vector>
#include <glimac/Cube.hpp>
#include <glimac/common.hpp>

namespace glimac{

class Cursor:public Cube {

public:
      inline Cursor() {m_position = glm::vec3(0,3,VOLUME-1);};
      inline glm::vec3 getCursorPos() const {return m_position;} ;
      void updatePosX(float direction);
      void updatePosY(float direction);
      void updatePosZ(float direction);
      void updateVertices();
      void renderCursor(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera);
      void createUniformLocation(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location,const ShaderProgram &shader2);

};

}

#endif 