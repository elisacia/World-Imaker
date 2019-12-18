#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/Controls.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/Overlay.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Scene.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/File.hpp>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <glimac/common.hpp>

using namespace glimac;

int main(int argc, char** argv) {    

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "World Imaker");

    // Initialize Imgui
    Overlay overlay;
    overlay.initImgui(windowManager.m_window,&windowManager.m_glContext);
    int actionGui =0;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }


    // Shaders
    FilePath applicationPath(argv[0]);
    ShaderProgram shader1(applicationPath,"colorcube.fs.glsl");
    ShaderProgram shader2(applicationPath,"colorcursor.fs.glsl");

    //Program program = loadProgram(applicationPath.dirPath() + "../shaders/color.vs.glsl",applicationPath.dirPath() + "../shaders/color.fs.glsl");
    //program.use();

    GLint uMVP_location, uMV_location, uNormal_location, uCubeType_location_location;

    // Initialize the cursor 
    Cursor cursor;
    glm::vec3 cursorPos;

    std::vector <glm::vec3> list_ctrl;
    readFile(applicationPath,"Control.txt",list_ctrl);

    for(glm::vec3 &c: list_ctrl)
    {
           std::cout<<c<<std::endl;
    }

    // list_ctrl.push_back(glm::vec3(0.0, 0.0, 9.0));
    // list_ctrl.push_back(glm::vec3(9.0, 9.0, 0.0));
    // Initialize a nb_cubes ground height
    
    std::vector <Cube> list_cubes;
    setGround(list_cubes, VOLUME);

    // Create Cubes Buffers + uniform location  
    for(Cube &c: list_cubes)
    {
        c.create_vbo_vao();
        c.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location,uCubeType_location_location, shader1);
    }

    // Create Cursor Buffers + uniform location  
    cursor.create_vbo_vao();
    cursor.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, shader2);

    // Load camera
    FreeFlyCamera camera;


    // Application loop
    bool done = false;
    while(!done) {
        // glm::mat4 ViewMatrix = camera.getViewMatrix();
        SDL_Event e;

        // Draw Imgui Windows
        overlay.beginFrame(windowManager.m_window);     
        overlay.drawOverlay(actionGui);
       
       // Event controller
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; 
            }
            cursorPos = cursor.getCursorPos();

            move_camera_key_pressed(e, camera); // Camera events
            move_cursor_key_pressed(e, cursor); // Cursor events
            sculpt_cubes(e,list_cubes,cursor,cursorPos,VOLUME,actionGui); // Scuplting events
            
            if (actionGui==5 || actionGui==6 || actionGui==7) paint_cubes(list_cubes,cursor,cursorPos,VOLUME,actionGui); // Painting events
            
            if (actionGui==8)cleanScene(list_cubes, VOLUME);

            if (actionGui==9)applyRbf(list_cubes, list_ctrl, FunctionType::Gaussian);

            actionGui=0;

             } 
            
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Draw Cubes
        shader1.m_program.use();
        for(Cube &c: list_cubes)
        {
            glUniform1i(shader1.uCubeType_location, c.getType());
            c.render(uMVP_location, uMV_location, uNormal_location, camera);
        }

        // Draw Cursor
        shader2.m_program.use();
        cursor.updateVertices();
        cursor.renderCursor(uMVP_location, uMV_location, uNormal_location, camera);


        overlay.endFrame(windowManager.m_window);
        windowManager.swapBuffers();

    
    }

    for(Cube &c: list_cubes)
    {
        c.liberate_resources();
    }
    
    return EXIT_SUCCESS;
}