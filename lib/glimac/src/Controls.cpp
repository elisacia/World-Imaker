#include <glimac/Controls.hpp>

namespace glimac {
 
const void move_camera_key_pressed(const SDL_Event &e, FreeFlyCamera &camera) 
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
            camera.rotateUp(1);
            break;
        case SDLK_k:
            camera.rotateUp(-1);
            break;
        case SDLK_j:
            camera.rotateLeft(1);
            break;
        case SDLK_l:
            camera.rotateLeft(-1);
            break;
        case SDLK_a:
            camera.moveUp(1);
            break;
        case SDLK_e:
            camera.moveUp(-1);
            break;
    }
    
}

const void move_cursor_key_pressed(const SDL_Event &e, Cursor &cursor) 
{

if(e.type==SDL_KEYDOWN){

switch(e.key.keysym.scancode)
    {
        case SDL_SCANCODE_LEFT:
            cursor.updatePosX(-1.0f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_RIGHT:
            cursor.updatePosX(1.0f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_UP:
            cursor.updatePosY(1.0f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_DOWN:
            cursor.updatePosY(-1.0f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;

    }


 switch(e.key.keysym.sym)
    {
        case SDLK_n:
            cursor.updatePosZ(-1.0f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDLK_b:
            cursor.updatePosZ(1.0f);
             std::cout<<cursor.getCursorPos()<<std::endl;
            break;
    }

}

}

void sculpt_cubes(SDL_Event &e, std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action)
{
    float index= cursorPos.z*volume+cursorPos.x+cursorPos.y*volume*volume;
    float indexCol= cursorPos.z*volume+cursorPos.x;

    //REMOVE
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_w ) || action == 1){
        std::cout<<cursorPos<<std::endl;
        list_cubes[index].removeCube();
      
    }

    //ADD
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_x ) || action == 2){
        std::cout<<cursorPos<<std::endl;
        list_cubes[index].addCube();
       
    }

    //EXTRUDE
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_c ) || action == 3){
        while (list_cubes[indexCol].isVisible()==true){
                indexCol = indexCol+(volume*volume);
            }
            list_cubes[indexCol].addCube();
       
    }

    //DIG
    if ((e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_v ) || action == 4){
        while (list_cubes[indexCol+(volume*volume)].isVisible()==true){
                indexCol = indexCol+(volume*volume);
            }
            list_cubes[indexCol].removeCube();
       
    }
}


void paint_cubes(std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action)
{
    float index= cursorPos.z*volume+cursorPos.x+cursorPos.y*volume*volume;

    //RED
    if (action == 5){
        list_cubes[index].setType(1);
           std::cout<<list_cubes[index].getType()<<std::endl;
           std::cout<<action<<std::endl;
      
    }

    //YELLOW
    if (action == 6){
        list_cubes[index].setType(2);
           std::cout<<list_cubes[index].getType()<<std::endl;
           std::cout<<action<<std::endl;
       
    }

    //PUNK
    if (action == 7){
            list_cubes[index].setType(3);
            std::cout<<list_cubes[index].getType()<<std::endl;
            std::cout<<action<<std::endl;
       
    }
}

void cleanScene(std::vector <Cube> &list_cubes, const int volume)
{
        for(Cube &c: list_cubes){
            c.removeCube();
        }
}




};

