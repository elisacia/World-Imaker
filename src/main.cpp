#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstddef>
#include <math.h>
#include <glimac/SDLWindowManager.hpp> 
#include <glimac/Controls.hpp>
#include <glimac/Overlay.hpp>
#include <glimac/Cube.hpp>

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

    // Initialize the light
    glm::vec4 LightDir=(glm::vec4(-6.f, -6.f,-2.f,0.));

    // Initialize the cursor 
    Cursor cursor;
    glm::vec3 cursorPos;

    // Initialize controls points for RBF
    std::vector <ControlPoint> list_ctrl;
    readFileControl(applicationPath,"Control.txt",list_ctrl);

    // Initialize a nb_cubes ground height
    std::vector <Cube> list_cubes;
    setGround(list_cubes, VOLUME);

    // Create Cubes Buffers + uniform location  
    for(Cube &c: list_cubes)
    {
        c.createBuffer();
        c.createUniformLocation(uMVP_location, uMV_location, uNormal_location,uCubeType_location, shader1);
    }

    // Create Cursor Buffers + uniform location  
    cursor.createBuffer();
    cursor.createUniformLocation(uMVP_location, uMV_location, uNormal_location, shader2);

    // Load camera
    FreeFlyCamera camera;

    // Initialization for Imgui
    float brushCursor;

    // Application loop
    bool done = false;
    while(!done) {
        glm::mat4 ViewMatrix = camera.getViewMatrix();
        SDL_Event e;

        //Background color
        glClearColor(0.1f,0.1f,0.1f,1.0);

        // Draw Imgui Windows
        overlay.beginFrame(windowManager.m_window);     
        brushCursor = overlay.drawOverlay(actionGui,LightDir);
       
       // Event controller
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; 
            }
            cursorPos = cursor.getCursorPos();

            moveCamera(e, camera); // Camera events
            moveCursor(e, cursor); // Cursor events
            sculptCubes(e,list_cubes,cursor,cursorPos,VOLUME,actionGui,brushCursor); // Scuplting events
            saveControl(applicationPath,"Scene.txt",list_cubes,actionGui);
            
            if (actionGui==1 || actionGui==10|| actionGui==2 || actionGui==20 || actionGui==3 || actionGui==30) 
            paintCubes(list_cubes,cursor,cursorPos,VOLUME,actionGui,brushCursor); // Painting events
            
            if (actionGui==4)cleanScene(list_cubes, VOLUME);

            if (actionGui==9)applyRBF(list_cubes, list_ctrl, FunctionType::Gaussian);

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
            c.renderCube(uMVP_location, uMV_location, uNormal_location, camera);
        }
    
        glm::vec4 tmpLightDir(glm::mat3(ViewMatrix)*glm::vec3(LightDir),LightDir.w);
        glUniform4f(uLightDir_location,tmpLightDir.x,tmpLightDir.y,tmpLightDir.z,tmpLightDir.w);

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
        c.freeRessources();
    }
    
    return EXIT_SUCCESS;
}