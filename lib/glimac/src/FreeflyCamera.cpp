#include <glimac/FreeFlyCamera.hpp>
#include <iostream>

FreeFlyCamera::FreeFlyCamera(){
    m_Position = glm::vec3(2*VOLUME/3,8.0f,2*VOLUME);
    m_fPhi = M_PI;
    m_fTheta = 0.0;
    computeDirectionVectors();
}

void FreeFlyCamera::computeDirectionVectors(){
    float radPhi = m_fPhi;
    float radTheta = m_fTheta;
    m_FrontVector = glm::vec3(cos(radTheta)*sin(radPhi), sin(radTheta), cos(radTheta)*cos(radPhi));
    m_LeftVector = glm::vec3(sin(radPhi+(M_PI/2.0)), 0, cos(radPhi+(M_PI/2.0)));
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

glm::mat4 FreeFlyCamera::getViewMatrix() const{
    //Point
    glm::mat4 MV = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    return MV;
}