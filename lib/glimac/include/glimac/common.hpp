#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "Program.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


struct ShaderProgram {

    Program m_program;
    GLint uMVP_location, uMV_location, uNormal_location,uCubeType_location;

    ShaderProgram(const FilePath &applicationPath, std::string type) : m_program(loadProgram(applicationPath.dirPath() + "../shaders/color.vs.glsl",
                                applicationPath.dirPath() + "../shaders"+ type)){

        uMVP_location = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix" );
        uMV_location = glGetUniformLocation(m_program.getGLId(), "uMVMatrix" );
        uNormal_location = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix" );
        uCubeType_location = glGetUniformLocation(m_program.getGLId(), "uCubeType" );
    }
};

}


