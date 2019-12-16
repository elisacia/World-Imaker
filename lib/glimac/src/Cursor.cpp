#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <glimac/Cursor.hpp>

#include <glimac/common.hpp>

using namespace glimac;


    Cursor::Cursor(){

    m_position = glm::vec3(-10,0,0);

    }



    glm::vec3 Cursor::getCursorPos(){
      return m_position;
    }



    void Cursor::updatePosX(float direction){
      m_position.x += direction;

      // if(m_position.x < 0){
      //   m_position.x = 0;
      // }
    }



    void Cursor::updatePosY(float direction){
      m_position.y += direction;
      
      // if(m_position.y < 0){
      //   m_position.y = 0;
      // }
    }



    void Cursor::updatePosZ(float direction){
      m_position.z += direction;
      
      // if(m_position.z < 0){
      //   m_position.z = 0;
      // }
    }



