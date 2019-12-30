#ifndef CUBE_HPP 
#define CUBE_HPP

#pragma once

#include <glimac/FreeFlyCamera.hpp>
#include <vector>

namespace glimac {

class Vertex3D
{    
 public:
    glm::vec3 m_position;
    glm::vec3 m_normal;
    Vertex3D();
    Vertex3D(glm::vec3 position,glm::vec3 normal )
        :m_position(position), m_normal(normal) {}
};

class Cube
{
  protected:
    GLuint m_vbo; 
    GLuint m_vao; 
    glm::vec3 m_position;
    glm::vec3 m_color;
    int m_type = 1;
     //1=Red
     //2=Blue
     //3=Yellow

    bool m_selected = false;
    bool m_visible = false;

  public:
    Cube() : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
    Cube(glm::vec3 position, glm::vec3 color, bool visible) : m_vbo(0), m_vao(0), m_position(position), m_color(color), m_visible(visible) {}
    void createBuffer();
    void renderCube(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera) const;
    void freeRessources();
    void createUniformLocation(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uCubeType_location,const ShaderProgram &shader1);
    inline void addCube() {m_visible=true;};
    inline void removeCube() {m_visible=false;};
    inline bool isVisible()const {return m_visible;} ;
    inline  int getType()const {return m_type;} ;
    inline void setType(int type)  {m_type=type;};
    inline glm::vec3 getPosition() const {return m_position;} ;
    inline void setPosition(glm::vec3 position) {m_position=position;};
    inline glm::vec3 getColor() {return m_color;};
};

    void setGround(std::vector <Cube> &list_cubes, const int volume);
    void resetGround(std::vector <Cube> &list_cubes, const int volume);

}

#endif 
