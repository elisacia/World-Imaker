
#include <iostream>
#include <fstream>
#include <algorithm>
#include <glimac/File.hpp>
#include <glm/glm.hpp>

namespace glimac{

void readFileControl(const FilePath &applicationPath,std::string filename,std::vector <ControlPoint> &list_ctrl){
	
	std::ifstream fichier(applicationPath.dirPath() + "../assets/doc"+filename, std::ios::in); 

	if (fichier)
	{

    	std::string line;
   			
		while(getline(fichier, line))
		{
    		ControlPoint control;
    		fichier >> control.m_position.x;
    		fichier >> control.m_position.y;
    		fichier >> control.m_position.z;
    		fichier >> control.m_value;
    			
    		list_ctrl.push_back(control);
    	}

		fichier.close();  
	}
	else std::cerr << "Impossible d'ouvrir le fichier de sauvegarde !" << std::endl; 
}


void saveFile(const FilePath &applicationPath,std::string filename,std::vector <Cube> &list_cube){
       
    std::ofstream fichier(applicationPath.dirPath() + "../assets/doc"+filename, std::ios::out | std::ios::trunc); 

    if(fichier)  
    {      

        for (int i = 0; i < list_cube.size(); ++i)
        {
             fichier << list_cube[i].getPosition().x <<" ";
             fichier << list_cube[i].getPosition().y <<" ";
             fichier << list_cube[i].getPosition().z <<" ";
             fichier << list_cube[i].getType() <<" ";
             fichier << list_cube[i].isVisible()<< std::endl;
         }

        fichier.close();  
    }
    else std::cerr << "Impossible d'enregistrer la scène !" << std::endl;
}

    
void loadFile(const FilePath &applicationPath,std::string filename,std::vector <Cube> &list_cube){

    std::ifstream fichier(applicationPath.dirPath() + "../assets/doc"+filename, std::ios::in); 

    if (fichier)
    {
        std::string line;
        int i=0;

        glm::vec3 position;
        int type;
        bool visibility;
         
        fichier >> position.x ;
        fichier >> position.y ;
        fichier >> position.z ;
        fichier >> type ;
        fichier >> visibility;

        list_cube[0].setPosition(position);
        list_cube[0].setType(type);
        
        if (visibility == true)
        {
          list_cube[0].addCube();
        }
        else list_cube[0].removeCube();

        while(getline(fichier, line))
        {
            i++;  
            glm::vec3 position;
         
            fichier >> position.x ;
            fichier >> position.y ;
            fichier >> position.z ;
            fichier >> type ;
            fichier >> visibility;

            list_cube[i].setPosition(position);
            list_cube[i].setType(type);
            if (visibility == true)
            {
              list_cube[i].addCube();
            }
            else list_cube[i].removeCube();
                        
        }

        fichier.close();  
    }

    else std::cerr << "Impossible de charger la scène !" << std::endl; 

}
   

}

