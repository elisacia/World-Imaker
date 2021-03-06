#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "Program.hpp"

constexpr int VOLUME = 20; 
constexpr float WINDOW_WIDTH = 1000;
constexpr float WINDOW_HEIGHT = 600; 

namespace glimac {

struct ShaderProgram {

    Program m_program;
    GLint uMVP_location, uMV_location, uNormal_location,uCubeType_location;
    GLint uLightDir_location; 
    GLint uLightPoint_location;
    ShaderProgram(const FilePath &applicationPath, std::string type) : m_program(loadProgram(applicationPath.dirPath() + "../shaders/color.vs.glsl",
                                applicationPath.dirPath() + "../shaders"+ type)){

        uMVP_location = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix" );
        uMV_location = glGetUniformLocation(m_program.getGLId(), "uMVMatrix" );
        uNormal_location = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix" );
        uCubeType_location = glGetUniformLocation(m_program.getGLId(), "uCubeType" );
        uLightDir_location = glGetUniformLocation(m_program.getGLId(), "uLightDir" );
        uLightPoint_location = glGetUniformLocation(m_program.getGLId(), "uLightPoint" );
                
    }
};

}


