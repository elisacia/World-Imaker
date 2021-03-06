#include <glimac/Cube.hpp>

namespace glimac {

void Cube::createBuffer()
{
    glGenBuffers(1, &m_vbo);
    // Bind buffer vbo to a target
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // Origin + position
    Vertex3D vertices[] = {
                    Vertex3D(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(0.f, 0.f, 1.f)), //0 0 front
                    Vertex3D(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(1.f, 0.f, 0.f)), //0 1 right
                    Vertex3D(glm::vec3(0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(0.f, 1.f, 0.f)), //0 2 up

                    Vertex3D(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(0.f, 0.f, 1.f)), //1 3 front
                    Vertex3D(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(0.f, 1.f, 0.f)), //1 4 up
                    Vertex3D(glm::vec3(-0.5f, 0.5f, 0.5f)+ m_position,  glm::vec3(-1.f, 0.f, 0.f)), //1 5 left
                    
                    Vertex3D(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position,  glm::vec3(0.f, 0.f, 1.f)), //2 6 front
                    Vertex3D(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position,  glm::vec3(-1.f, 0.f, 0.f)), //2 7 left
                    Vertex3D(glm::vec3(-0.5f, -0.5f, 0.5f)+ m_position,  glm::vec3(0.f, -1.f, 0.f)), //2 8 down

                    Vertex3D(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(0.f, 0.f, 1.f)), //3 9 front
                    Vertex3D(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(1.f, 0.f, 0.f)), //3 10 right
                    Vertex3D(glm::vec3(0.5f, -0.5f, 0.5f)+ m_position, glm::vec3(0.f, -1.f, 0.f)), //3 11 down

                    Vertex3D(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(0.f, 0.f, -1.f)), //4 12 back
                    Vertex3D(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(1.f, 0.f, 0.f)), //4 13 right
                    Vertex3D(glm::vec3(0.5f, -0.5f, -0.5f)+ m_position, glm::vec3(0.f, -1.f, 0.f)), //4 14 down
                    
                    Vertex3D(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(0.f, 1.f, 0.f)), //5 15 up
                    Vertex3D(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(0.f, 0.f, -1.f)), //5 16 back
                    Vertex3D(glm::vec3(0.5f, 0.5f, -0.5f)+ m_position, glm::vec3(1.f, 0.f, 0.f)), //5 17 right
                    
                    Vertex3D(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position,  glm::vec3(0.f, 1.f, 0.f)), //6 18 up 
                    Vertex3D(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position,  glm::vec3(0.f, 0.f, -1.f)), //6 19 back
                    Vertex3D(glm::vec3(-0.5f, 0.5f, -0.5f)+ m_position,  glm::vec3(-1.f, 0.f, 0.f)), //6 20 left
                    
                    Vertex3D(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position,  glm::vec3(-1.f, 0.f, 0.f)), //7 21 left
                    Vertex3D(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position,  glm::vec3(0.f, 0.f, -1.f)), //7 22 back
                    Vertex3D(glm::vec3(-0.5f, -0.5f, -0.5f)+ m_position,  glm::vec3(0.f, -1.f, 0.f))  //7 23 down
                          };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Unbind target to avoid modifying it by mistake
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create IBO
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Create indexes : 8 vertices, 6 faces
    uint32_t indexes[36] = {3, 6, 9, //front face 
                            3, 9, 0,
                            12, 16, 22, //back face
                            16, 22, 19,
                            5, 7, 21, //left face
                            5, 20, 21,
                            1, 10, 13, //right face
                            1, 13, 17,
                            8, 11, 14, //down face
                            8, 14, 23,
                            2, 4, 15, //up  face
                            4, 15, 18};

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
    const GLuint VERTEX_ATTR_NORMAL = 1;

    // Bind VBO again
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Where to find vertices and how to read data
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, m_position));
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, m_normal));
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    
    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Cube::createUniformLocation(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uCubeType_location,const ShaderProgram &shader1)
{
    uMVP_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVPMatrix" );
    uMV_location = glGetUniformLocation(shader1.m_program.getGLId(), "uMVMatrix" );
    uNormal_location = glGetUniformLocation(shader1.m_program.getGLId(), "uNormalMatrix" );
    uCubeType_location = glGetUniformLocation(shader1.m_program.getGLId(), "uCubeType" );
}



void Cube::renderCube(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, const FreeFlyCamera &camera) const
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

void Cube::freeRessources()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}



void setGround(std::vector <Cube> &list_cubes, const int volume)
{
    if (list_cubes.empty()==false) list_cubes.clear();

    bool visibility=true;
    unsigned int nb_cubes=3;
    for (int k = 0; k < VOLUME; ++k)
    {
        if (k>=nb_cubes) visibility= false;
        
        for (int j = 0; j < VOLUME; ++j)
        {
            for (int i = 0; i < VOLUME; ++i)
            {
                list_cubes.push_back( Cube(glm::vec3(i,k,j),visibility) );
            }

        }
    }
}
void resetGround(std::vector <Cube> &list_cubes, const int volume)
{
    if (list_cubes.empty()==true) setGround(list_cubes, volume);

    unsigned int index_max=3*volume*volume;
    for (int i = 0; i < index_max; ++i)
                list_cubes[i].addCube();
}



}

