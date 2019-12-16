#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/GameController.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Cursor.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

using namespace glimac;

void move_camera_key_pressed(SDL_Event &e, FreeFlyCamera &camera)
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

void move_cursor_key_pressed(SDL_Event &e, Cursor &cursor)
{

switch(e.key.keysym.scancode)
    {
        case SDL_SCANCODE_LEFT:
            cursor.updatePosX(-0.5f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_RIGHT:
            cursor.updatePosX(0.5f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_UP:
            cursor.updatePosY(0.5f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDL_SCANCODE_DOWN:
            cursor.updatePosY(-0.5f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;

    }


 switch(e.key.keysym.sym)
    {
        case SDLK_n:
            cursor.updatePosZ(-0.5f);
            std::cout<<cursor.getCursorPos()<<std::endl;
            break;
        case SDLK_b:
            cursor.updatePosZ(0.5f);
             std::cout<<cursor.getCursorPos()<<std::endl;
            break;
    }

}

void sculpt_cubes(SDL_Event &e, std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, int volume)
{
    float index= cursorPos.z*volume+cursorPos.x+cursorPos.y*volume*volume;
     switch(e.key.keysym.sym)
    {
        case SDLK_w:
            cursorPos = cursor.getCursorPos();
            std::cout<<cursorPos<<std::endl;
            list_cubes[index].removeCube();
            break;

        case SDLK_x:
            cursorPos = cursor.getCursorPos();
            std::cout<<cursorPos<<std::endl;
            list_cubes[index].addCube();
            break;
    }

}


int main(int argc, char** argv) {    

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "World Imaker");

    Overlay overlay;

    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "../shaders/color.vs.glsl",applicationPath.dirPath() + "../shaders/color.fs.glsl");
    program.use();


    GLint uMVP_location, uMV_location, uNormal_location;

    unsigned int nb_cubes=3;
    std::vector <Cube> list_cubes;

    Cursor cursor;
    glm::vec3 cursorPos;

    int volume=10;
    bool visibility=true;
    for (int k = 0; k < volume; ++k)
    {
        if (k>=nb_cubes) visibility= false;
        for (int j = 0; j < volume; ++j)
        {
            for (int i = 0; i < volume; ++i)
            {
            list_cubes.push_back( Cube(glm::vec3(i,k,j), glm::vec3(0.2 + i/5.0, i/5.0, 0.2 + i*0.1),visibility) );
            }

        }
    }


    // for (int j = 0; j < 10; ++j)
    // {
    //    for (int k = 0; k < 10; ++k)
    //    {
    //        for (unsigned int i=0; i<nb_cubes; i++)
    //         {

    //             list_cubes.push_back( Cube(glm::vec3(i,j,k), glm::vec3(0.2 + i/5.0, i/5.0, 0.2 + i*0.1),true) );
    //         }

    //         for (unsigned int i=nb_cubes; i<10; i++)
    //         {
    //             list_cubes.push_back( Cube(glm::vec3(i,j,k), glm::vec3(0.2 + i/5.0, i/5.0, 0.2 + i*0.1),false) );
    //         }


    //    }
    // }
    

    for(Cube &c: list_cubes)
    {
        c.create_vbo_vao();
        c.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);
    }

    

    //Load camera
    FreeFlyCamera camera;



    // Application loop
    bool done = false;
    while(!done) {

        glm::mat4 ViewMatrix = camera.getViewMatrix();

        SDL_Event e;



        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }


            move_camera_key_pressed(e, camera);
            move_cursor_key_pressed(e, cursor);
            sculpt_cubes(e,list_cubes,cursor,cursorPos,volume);

             }

            
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        overlay.beginFrame(windowManager.m_window);

        for(Cube &c: list_cubes)
        {
            c.render(uMVP_location, uMV_location, uNormal_location, camera);
        }

        cursor.create_vbo_vao();
        cursor.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);


         cursor.renderCursor(uMVP_location, uMV_location, uNormal_location, camera);

         overlay.drawOverlay();

        overlay.endFrame(windowManager.m_window);


        windowManager.swapBuffers();

    
    }

    for(Cube &c: list_cubes)
    {
        c.liberate_resources();
    }


    return EXIT_SUCCESS;
}