#include <vector>
#include <iostream>
#include <glimac/Cursor.hpp>
#include <glimac/common.hpp>

namespace glimac {

void Cursor::updatePosX(float direction){
  m_position.x += direction;

  if(m_position.x < 0){
    m_position.x = 0;
  }
  else if (m_position.x >= VOLUME){
     m_position.x = VOLUME-1;
  }
}

void Cursor::updatePosY(float direction){
  m_position.y += direction;

  if(m_position.y < 0){
    m_position.y = 0;
  }
  else if (m_position.y >= VOLUME){
     m_position.y = VOLUME-1;
  }
}

void Cursor::updatePosZ(float direction){
  m_position.z += direction;
  
  if(m_position.z < 0){
    m_position.z = 0;
  }
  else if (m_position.z >= VOLUME){
     m_position.z = VOLUME-1;
  }
}

void Cursor::renderCursor(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera) {
  glm::mat4 camera_VM = camera.getViewMatrix();

  glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f); 
  glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
  glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  
  glBindVertexArray(m_vao);
      glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
      glUniformMatrix4fv(uMV_location, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
      glUniformMatrix4fv(uNormal_location, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glDisable(GL_DEPTH_TEST);
   glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
   glEnable(GL_DEPTH_TEST);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBindVertexArray(0);
}

void Cursor::create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, const ShaderProgram &shader1) 
{
    uMVP_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVPMatrix" );
    uMV_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVMatrix" );
    uNormal_location = glGetUniformLocation(shader1.m_program.getGLId(), "uNormalMatrix" );
}

void Cursor::updateVertices()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  Vertex3DColor vertices[] = {
                  
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(0.f, 0.f, 1.f)), //0 0 front
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(1.f, 0.f, 0.f)), //0 1 right
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(0.f, 1.f, 0.f)), //0 2 up

                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(0.f, 0.f, 1.f)), //1 3 front
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(0.f, 1.f, 0.f)), //1 4 up
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position, glm::vec3(-1.f, 0.f, 0.f)), //1 5 left
                    
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(0.f, 0.f, 1.f)), //2 6 front
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(-1.f, 0.f, 0.f)), //2 7 left
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(0.f, -1.f, 0.f)), //2 8 down

                    Vertex3DColor(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position,glm::vec3(0.f, 0.f, 1.f)), //3 9 front
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position,glm::vec3(1.f, 0.f, 0.f)), //3 10 right
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position,glm::vec3(0.f, -1.f, 0.f)), //3 11 down

                    Vertex3DColor(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position,glm::vec3(0.f, 0.f, -1.f)), //4 12 back
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position,glm::vec3(1.f, 0.f, 0.f)), //4 13 right
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position,glm::vec3(0.f, -1.f, 0.f)), //4 14 down
                    
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position,glm::vec3(0.f, 1.f, 0.f)), //5 15 up
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position,glm::vec3(0.f, 0.f, -1.f)), //5 16 back
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position,glm::vec3(1.f, 0.f, 0.f)), //5 17 right
                    
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(0.f, 1.f, 0.f)), //6 18 up 
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(0.f, 0.f, -1.f)), //6 19 back
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(-1.f, 0.f, 0.f)), //6 20 left
                    
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(-1.f, 0.f, 0.f)), //7 21 left
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(0.f, 0.f, -1.f)), //7 22 back
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(0.f, -1.f, 0.f))  //7 23 down
                          };
                

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}


