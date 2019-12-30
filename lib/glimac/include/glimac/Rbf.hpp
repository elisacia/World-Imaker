#ifndef RBF_HPP 
#define RBF_HPP

#pragma once

#include <vector>
#include <glimac/Cube.hpp>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <Eigen/Dense>

namespace glimac{

enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsiolon * r^2))
    };

 class ControlPoint
{
public:
    glm::vec3 m_position;
    float m_value;
};


    float getRBF(FunctionType type, const glm::vec3 vecA, const glm::vec3 vecB, const float epsilon);
    Eigen::VectorXf caclulRBF(std::vector <ControlPoint> &list_controls, FunctionType type,  const float epsilon);
    void applyRBF(std::vector <Cube> &list_cubes,  std::vector <ControlPoint> &list_controls, FunctionType type);

}



#endif 