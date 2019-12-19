#pragma once
#include <glimac/common.hpp>

class FreeFlyCamera{

public:
    FreeFlyCamera();
    void computeDirectionVectors();
    inline void moveLeft(float t) {m_Position += t * m_LeftVector; computeDirectionVectors();};
    inline void moveFront(float t){m_Position += t * m_FrontVector; computeDirectionVectors();};
    inline void rotateLeft(float degrees){m_fPhi += glm::radians(degrees);computeDirectionVectors();};
    inline void rotateUp(float degrees){m_fTheta += glm::radians(degrees);computeDirectionVectors();};
    inline void moveUp(float t){m_Position += t * m_UpVector;computeDirectionVectors();};

    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

};