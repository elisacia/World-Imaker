#include <glimac/Controls.hpp>

namespace glimac {
 
const void moveCamera(const SDL_Event &e, FreeFlyCamera &camera) 
{
    switch(e.key.keysym.sym)
    {
        case SDLK_z:
            camera.moveFront(1);
            break;
        case SDLK_s:
            camera.moveFront(-1);
            break;
        case SDLK_q:
            camera.moveLeft(1);
            break;
        case SDLK_d:
            camera.moveLeft(-1);
            break;
        case SDLK_i:
            camera.rotateUp(2);
            break;
        case SDLK_k:
            camera.rotateUp(-2);
            break;
        case SDLK_j:
            camera.rotateLeft(2);
            break;
        case SDLK_l:
            camera.rotateLeft(-2);
            break;
        case SDLK_a:
            camera.moveUp(1);
            break;
        case SDLK_e:
            camera.moveUp(-1);
            break;
    }
    
}

const void moveCursor(const SDL_Event &e, Cursor &cursor) 
{

if(e.type==SDL_KEYDOWN){

switch(e.key.keysym.scancode)
    {
        case SDL_SCANCODE_LEFT:
            cursor.updatePosX(-1.0f);
            break;
        case SDL_SCANCODE_RIGHT:
            cursor.updatePosX(1.0f);
            break;
        case SDL_SCANCODE_UP:
            cursor.updatePosY(1.0f);
            break;
        case SDL_SCANCODE_DOWN:
            cursor.updatePosY(-1.0f);
            break;

    }


 switch(e.key.keysym.sym)
    {
        case SDLK_n:
            cursor.updatePosZ(-1.0f);
            break;
        case SDLK_b:
            cursor.updatePosZ(1.0f);

            break;
    }

}

}

void sculptCubes(SDL_Event &e, std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action, const float epsilon)
{
    float index= cursorPos.z*volume+cursorPos.x+cursorPos.y*volume*volume;
    float indexCol= cursorPos.z*volume+cursorPos.x;

    //REMOVE
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_w ) || action == 5){
        list_cubes[index].removeCube();
      
    }

    if (action == 50){
       float value;
        for(Cube &c: list_cubes){
            value = getRBF(FunctionType::Gaussian, c.getPosition(), cursorPos, epsilon);
            if (value >= 0.5f )  c.removeCube();
        } 
    }

    //ADD
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_x ) || action == 6){
        list_cubes[index].addCube();
    }

    if (action == 60){
       float value;
        for(Cube &c: list_cubes){
            value = getRBF(FunctionType::Gaussian, c.getPosition(), cursorPos, epsilon);
            if (value >= 0.5f )  c.addCube();
        } 
    }

    //EXTRUDE
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_c ) || action == 7){
        while (list_cubes[indexCol].isVisible()==true){
                indexCol = indexCol+(volume*volume);
            }
            list_cubes[indexCol].addCube();
       
    }

    //DIG
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_v ) || action == 8){
        while (list_cubes[indexCol+(volume*volume)].isVisible()==true){
                indexCol = indexCol+(volume*volume);
            }
            list_cubes[indexCol].removeCube();
       
    }
}


void paintCubes(std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action, const float epsilon)
{
    float index= cursorPos.z*volume+cursorPos.x+cursorPos.y*volume*volume;

    if (action%10 == 0){

        // float epsilon=0.1f;
        float value;
        for(Cube &c: list_cubes){
            value = getRBF(FunctionType::Gaussian, c.getPosition(), cursorPos, epsilon);
            if (value >= 0.5f )  c.setType(action/10);
        } 
    }  
    else list_cubes[index].setType(action);
}

void cleanScene(std::vector <Cube> &list_cubes, const int volume)
{
        for(Cube &c: list_cubes){
            c.removeCube();
            c.setType(1);
        }
}

void saveControl(const FilePath &applicationPath,std::string filename,std::vector <Cube> &list_cubes,const int action){
    if(action== 12) saveFile(applicationPath,filename,list_cubes);
    if(action== 13) loadFile(applicationPath,filename,list_cubes);
}



};

