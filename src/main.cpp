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
#include <glimac/Cursor.hpp>
#include <glimac/File.hpp>
#include <glm/glm.hpp>
#include <glimac/Rbf.hpp>
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

    // Uniform Locations
    GLint uMVP_location, uMV_location, uNormal_location,uCubeType_location;
    GLint uLightDir_location;
    GLint uLightPoint_location;
    uLightDir_location = glGetUniformLocation(shader1.m_program.getGLId(), "uLightDir" );
    uLightPoint_location = glGetUniformLocation(shader1.m_program.getGLId(), "uLightPoint" );

    glm::vec3 LightDir=glm::normalize(glm::vec3(0.f));
    glm::vec3 LightPoint=glm::normalize(glm::vec3(-1.0f));

    // Initialize the cursor 
    Cursor cursor;
    glm::vec3 cursorPos;

    std::vector <ControlPoint> list_ctrl;
    readFile(applicationPath,"Control.txt",list_ctrl);

    // Initialize a nb_cubes ground height
    
    std::vector <Cube> list_cubes;
    setGround(list_cubes, VOLUME);

    // Create Cubes Buffers + uniform location  
    for(Cube &c: list_cubes)
    {
        c.create_vbo_vao();
        c.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location,uCubeType_location, shader1);

    }

    // Create Cursor Buffers + uniform location  
    cursor.create_vbo_vao();
    cursor.create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, shader2);

    // Load camera
    FreeFlyCamera camera;

    float brushCursor;

    // Application loop
    bool done = false;
    while(!done) {
        glm::mat4 ViewMatrix = camera.getViewMatrix();
        SDL_Event e;

        //Background color
        //glClearColor(1.0,1.0,1.0,1.0);

        // Draw Imgui Windows
        overlay.beginFrame(windowManager.m_window);     
        brushCursor = overlay.drawOverlay(actionGui,LightDir);
       
       // Event controller
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; 
            }
            cursorPos = cursor.getCursorPos();

            move_camera_key_pressed(e, camera); // Camera events
            move_cursor_key_pressed(e, cursor); // Cursor events
            sculpt_cubes(e,list_cubes,cursor,cursorPos,VOLUME,actionGui,brushCursor); // Scuplting events
            
            if (actionGui==1 || actionGui==10|| actionGui==2 || actionGui==20 || actionGui==3 || actionGui==30) 
            paint_cubes(list_cubes,cursor,cursorPos,VOLUME,actionGui,brushCursor); // Painting events
            
            if (actionGui==4)cleanScene(list_cubes, VOLUME);

            if (actionGui==9)applyRbf(list_cubes, list_ctrl, FunctionType::Gaussian);

            if (actionGui==11)resetGround(list_cubes, VOLUME);

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


        // glm::vec3 tmpLightDir(glm::mat3(camera.getViewMatrix())*glm::vec3(1.0f,1.0f,1.0f));
        // glUniform3fv(shader1.uLightDir_location, 1, glm::value_ptr(tmpLightDir));
        // glm::vec3 tmpLightIntensity(1.0f,1.0f,1.0f);
        // glUniform3f(shader1.uLightIntensity_location, 1.0f,1.0f, 1.0f);
    
        glUniform3f(uLightDir_location,LightDir.x,LightDir.y,LightDir.z);
        glUniform3f(uLightPoint_location,LightPoint.x,LightPoint.y,LightPoint.z);

        // Draw Cursor
        shader2.m_program.use();
        cursor.updateVertices();
        cursor.renderCursor(uMVP_location, uMV_location, uNormal_location, camera);

        overlay.endFrame(windowManager.m_window);
        windowManager.swapBuffers();

    }
    // Liberate allocations
    for(Cube &c: list_cubes)
    {
        c.liberate_resources();
    }
    
    return EXIT_SUCCESS;
}