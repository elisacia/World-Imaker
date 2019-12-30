#include <vector>
#include <iostream>
#include <glimac/Rbf.hpp>

namespace glimac {

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
        else return 0.f;
  }


  Eigen::VectorXf calculRBF(std::vector <ControlPoint> &list_controls, FunctionType type,  const float epsilon){
    size_t size=list_controls.size();

    //Definition Matrix A
    Eigen::MatrixXf A=Eigen::MatrixXf::Zero(size,size);
    for (int i = 1; i < size; ++i){
      for (int j = 0; j < i; ++j){
        A(i,j)=getRBF(type, list_controls[i].m_position,list_controls[j].m_position, epsilon);
      }
    }
    Eigen::MatrixXf A_t=A.transpose();
    A=A+A_t;
    A=A+Eigen::MatrixXf::Identity(size,size)*getRBF(type, list_controls[0].m_position,list_controls[0].m_position, epsilon);
    
    //Definition Vector B
    Eigen::VectorXf B(size);
    for (int i=0; i<size; ++i){
      B[i]=list_controls[i].m_value;
    }

    //Definition Vector Solution
    Eigen::ColPivHouseholderQR<Eigen::MatrixXf> qr(A);
    Eigen::VectorXf vec_omega = qr.solve(B);
    return vec_omega;
  }

  
  void applyRBF(std::vector <Cube> &list_cubes, std::vector <ControlPoint> &list_controls, FunctionType type){
    float epsilon=1.f;
    float value;
    Eigen::VectorXf omega=calculRBF(list_controls, type, epsilon);

    for(Cube &c: list_cubes){
      value=0;
      for (int i = 1; i < list_controls.size(); ++i){
        value+= getRBF(type, c.getPosition(), list_controls[i].m_position, epsilon)*omega[i];

      } 
      if (value >= 0.f )  c.addCube();
      else c.removeCube();
    }  
  }



}


