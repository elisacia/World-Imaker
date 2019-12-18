#ifndef RBF_HPP 
#define RBF_HPP

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <glimac/Cube.hpp>
#include <glimac/common.hpp>
#include <math.h>
#include <algorithm>
#include <numeric>


namespace glimac {

enum class FunctionType
    {
        Gaussian,         // f(r) = exp(-(epsilon * r)^2)
        ThinPlateSpline,  // f(r) = (r^2) * log(r)
        InverseQuadratic, // f(r) = (1 + (epsilon * r)^2)^(-1)
        BiharmonicSpline, // f(r) = r
        Multiquadric,     // f(r) = sqrt(1 + (epsiolon * r^2))
    };

    float getRBF(FunctionType type, const glm::vec3 vecA, const glm::vec3 vecB, const float epsilon);

    void applyRbf(std::vector <Cube> &list_cubes,  std::vector <glm::vec3> &list_controls, FunctionType type);

}



#endif 