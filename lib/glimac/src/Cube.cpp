#include <glimac/Cube.hpp>

namespace glimac {

void Cube::create_vbo_vao()
{
    glGenBuffers(1, &m_vbo);
    // Bind buffer vbo to a target
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // Origin + position
    Vertex3DColor vertices[] = {
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position, m_color), //0
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position, m_color), //1
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position, m_color), //2
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position, m_color), //3
                    Vertex3DColor(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position, m_color), //4
                    Vertex3DColor(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position, m_color), //5
                    Vertex3DColor(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position, m_color), //6
                    Vertex3DColor(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position, m_color) //7
                          };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Unbind target to avoid modifying it by mistake
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create IBO
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Create indexes : 8 vertices, 6 faces
    uint32_t indexes[36] = {0, 1, 3, //top face 
                            1, 3, 2,
                            4, 5, 7, //bottom face
                            5, 7, 6,
                            0, 3, 4, //left face
                            3, 4, 7,
                            1, 2, 5, //right face
                            2, 5, 6,
                            3, 2, 7, //front face
                            2, 7, 6,
                            0, 1, 4, //back  face
                            1, 4, 5};

    // Fill IBO with indexes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(uint32_t), indexes, GL_STATIC_DRAW);
    // Debind before doing the rest
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Create VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    // Bind IBO on target to save IBO in VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    // Bind VBO again
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Where to find vertices and how to read data
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_position));
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, m_color));
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Cube::create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uCubeType_location,const ShaderProgram &shader1)
{
    uMVP_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVPMatrix" );
    uMV_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVMatrix" );
    uNormal_location = glGetUniformLocation(shader1.m_program.getGLId(), "uNormalMatrix" );
    uCubeType_location = glGetUniformLocation(shader1.m_program.getGLId(), "uCubeType" );
}



void Cube::render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera) const
{
    if (m_visible)
    {       
    glm::mat4 camera_VM = camera.getViewMatrix();
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f); 
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    
    glBindVertexArray(m_vao);
        glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
        glUniformMatrix4fv(uMV_location, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
        glUniformMatrix4fv(uNormal_location, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);
    }
}

void Cube::liberate_resources()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Cube::addCube()
{
    m_visible=true;
}

void Cube::removeCube()
{
    m_visible=false;
}

bool Cube::isVisible() const
{
    return m_visible;
}

int Cube::getType() const
{
    return m_type;
}

void Cube::setType(int type)
{
    m_type=type;
}

glm::vec3 Cube::getPosition() const
{
    return m_position;
}

void setGround(std::vector <Cube> &list_cubes, const int volume)
{
    bool visibility=true;
    unsigned int nb_cubes=3;
        for (int k = 0; k < VOLUME; ++k)
        {
            if (k>=nb_cubes) visibility= false;
            
            for (int j = 0; j < VOLUME; ++j)
            {
                for (int i = 0; i < VOLUME; ++i)
                {
                    list_cubes.push_back( Cube(glm::vec3(i,k,j), glm::vec3(0.2 + i/5.0, i/5.0, 0.2 + i*0.1),visibility) );
                }

            }
        }
    }

}

