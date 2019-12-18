
#include <iostream>
#include <fstream>
#include <algorithm>
#include <glimac/File.hpp>
#include <glm/glm.hpp>

namespace glimac{

// ================================
// RECONSTRUCTION TABLEAU APRES LECTURE FICHIER
// ================================
	void readFile(const FilePath &applicationPath,std::string filename,std::vector <glm::vec3> &list_ctrl){
	
		std::ifstream fichier(applicationPath.dirPath() + "../assets/doc"+filename, std::ios::in); 

		if (fichier)
		{

    		std::string line;
   			
   			while(getline(fichier, line))
    		{
        		//if (line.size()>0)
   			//{
        			glm::vec3 vec;
        			fichier >> vec.x;
        			fichier >> vec.y;
        			fichier >> vec.z;
        			std::cout<<vec<<std::endl;
        			std::cout<<"___________________________"<<std::endl;
        			list_ctrl.push_back(vec);

        		
    		//}
    	}
    	for(glm::vec3 &c: list_ctrl)
				    {
				           std::cout<<c<<std::endl;
				    }	

			fichier.close();  
		}
		 else  
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl; 



	}
}

