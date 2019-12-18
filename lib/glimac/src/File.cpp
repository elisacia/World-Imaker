
#include <iostream>
#include <fstream>
#include <algorithm>
#include <glimac/File.hpp>
#include <glm/glm.hpp>

namespace glimac{

// ================================
// RECONSTRUCTION TABLEAU APRES LECTURE FICHIER
// ================================
	void readFile(const FilePath &applicationPath,std::string filename,std::vector <ControlPoint> &list_ctrl){
	
		std::ifstream fichier(applicationPath.dirPath() + "../assets/doc"+filename, std::ios::in); 

		if (fichier)
		{

    		std::string line;
   			
   			while(getline(fichier, line))
    		{
        		//if (line.size()>0)
   			//{
        			ControlPoint control;
        			fichier >> control.m_position.x;
        			fichier >> control.m_position.y;
        			fichier >> control.m_position.z;
        			fichier >> control.m_value;
        			
        			list_ctrl.push_back(control);

        		
    		//}
    	}

			fichier.close();  
		}
		 else  
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl; 



	}
}

