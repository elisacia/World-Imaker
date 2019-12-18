#include <vector>
#include <iostream>
#include <glimac/Rbf.hpp>

namespace glimac {

  //template <typename T>
    float getRBF(FunctionType type, const glm::vec3 v1, const glm::vec3 v2, const float epsilon){
        float d = glm::distance(v1, v2);
        if(type == FunctionType::Gaussian) {
            
            return exp(-epsilon*d*d); 
        }
        else if(type == FunctionType::ThinPlateSpline) {
            return glm::pow(d, 2.0f)*glm::log(d);
        }
        else if(type == FunctionType::InverseQuadratic) {
          return glm::pow(1.0f+(glm::pow((epsilon*d),2.0f)),-1.0f);
        }
        else if(type == FunctionType::BiharmonicSpline) {
          return d;
        }
        else if(type == FunctionType::Multiquadric) {
          return glm::sqrt(1+(epsilon*glm::pow(d,2.0f)));
        }
    }

  
  void applyRbf(std::vector <Cube> &list_cubes, std::vector <glm::vec3> &list_controls, FunctionType type){
    float epsilon=10.0f;
    float value;
    for(Cube &c: list_cubes){
      value=0;
      for (glm::vec3 &control: list_controls){
        value+=getRBF(type, c.getPosition(), control, epsilon);
      }
      if (value > 0.0f )  c.addCube();
      else c.removeCube();
    }  
  }



}


