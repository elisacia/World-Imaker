#include "glimac/Overlay.hpp"




#include <iostream>

namespace glimac {

    Overlay::~Overlay() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }
    void Overlay::initImgui(SDL_Window* window,SDL_GLContext* glContext) const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(window, glContext);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    void Overlay::beginFrame(SDL_Window* window) const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }






    float Overlay::drawOverlay(int &action) const {

        // render your GUI
    ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH-250, 10));
    ImGui::SetNextWindowSize(ImVec2(240, WINDOW_HEIGHT-20));
    ImGui::Begin("ACTIONS");
   

    static bool check = false;
    static float brushSize=1.0f;


    if (ImGui::Button("REMOVE CUBE")){
        if (check==true) action=50; 
        else action=5;
    }

    if (ImGui::Button("ADD CUBE")){
        if (check==true) action=60; 
        else action=6;
    }

    if (ImGui::Button("EXTRUDE COLUMN"))  action=7;

    if (ImGui::Button("DIG COLUMN"))  action=8;

    if (ImGui::Button("PAINT RED CUBE")){
        if (check==true) action=10; 
        else action=1;
    }  

    if (ImGui::Button("PAINT WHITE CUBE")){
        if (check==true) action=20; 
        else action=2;
    }  

    if (ImGui::Button("PAINT YELLOW CUBE")){
        if (check==true) action=30; 
        else action=3;
    }  

    if (ImGui::Button("CLEAN ALL"))  action=4;

    if (ImGui::Button("SCENE GENERATOR"))  action=9;

    ImGui::Checkbox("Large selection", &check);

    ImGui::SliderFloat("Brush size", &brushSize, 1.0f, 10.0f);

    ImGui::End();

    return 1.0f/brushSize;

    }





    void Overlay::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    
}
