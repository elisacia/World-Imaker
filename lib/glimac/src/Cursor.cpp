#pragma once

#include <vector>
#include <iostream>
#include <glimac/Cursor.hpp>

#include <glimac/common.hpp>

using namespace glimac;




    Cursor::Cursor(){

    m_position = glm::vec3(0,5,VOLUME-1);

    }



    glm::vec3 Cursor::getCursorPos(){
      return m_position;
    }



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

    void Cursor::renderCursor(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, FreeFlyCamera &camera)
{
    glm::mat4 camera_VM = camera.getViewMatrix();

    //vertical angle of view, ratio width/height of window, near, far 
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f); 
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    //formula: (MV⁻1)^T
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

    //unbind vao
    glBindVertexArray(0);
}



