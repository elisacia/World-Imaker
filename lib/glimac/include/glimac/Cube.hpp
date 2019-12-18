#ifndef CUBE_HPP 
#define CUBE_HPP

#pragma once

#include <glimac/Program.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/common.hpp>
#include <glimac/glm.hpp> 
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

namespace glimac {

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
    GLuint m_vbo; 
    GLuint m_vao; 
    glm::vec3 m_position;
    glm::vec3 m_color;
    int m_type = 3;
     //1=Red
     //2=White
     //3=Yellow

    bool m_selected = false;
    bool m_visible = false;

  public:
    Cube() : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
    Cube(glm::vec3 position, glm::vec3 color, bool visible) : m_vbo(0), m_vao(0), m_position(position), m_color(color), m_visible(visible) {}
    void create_vbo_vao();
    void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera) const;
    void liberate_resources();
    void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location,GLint &uCubeType_location, const ShaderProgram &shader);
    void addCube();
    void removeCube();
    bool isVisible() const;
    int getType() const;
    void setType(int type);
    glm::vec3 getPosition() const;
};

    void setGround(std::vector <Cube> &list_cubes, const int volume);

}

#endif 
