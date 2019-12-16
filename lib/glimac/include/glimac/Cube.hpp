#ifndef WORLD_IMAKER_CUBE_HPP 
#define WORLD_IMAKER_CUBE_HPP

#pragma once

#include "Program.hpp"
#include "FreeFlyCamera.hpp"

namespace glimac{

typedef enum{
  SELECTED, FLAT, TEXTURED
}CubeType;


class Vertex3DColor
{    
 public:
    glm::vec3 m_position;
    glm::vec3 m_color;
    Vertex3DColor();
    Vertex3DColor(glm::vec3 position, glm::vec3 color)
        :m_position(position), m_color(color) {}
};



class Cube
{
protected:
  GLuint m_vbo; //Vertex Buffer Object
  GLuint m_vao; //Vertex Array Object
  glm::vec3 m_position;
  glm::vec3 m_color;
  CubeType m_type;
  bool m_selected = false;
  bool m_visible = false;

public:
  Cube() : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
  Cube(glm::vec3 position, glm::vec3 color, bool visible) : m_vbo(0), m_vao(0), m_position(position), m_color(color), m_visible(visible) {}
  void create_vbo_vao();
  void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, FreeFlyCamera &camera);
  void liberate_resources();
  void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, glimac::Program &program);
  void addCube();
  void removeCube();

  CubeType getType();
};

}

#endif // WORLD_IMAKER_CUBE_HPP
