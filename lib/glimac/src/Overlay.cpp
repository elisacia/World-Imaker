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
        ImGuiIO &io = ImGui::GetIO();
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

    void Overlay::drawOverlay(int &action) const {

        // render your GUI
    ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH-250, 10));
    ImGui::SetNextWindowSize(ImVec2(240, WINDOW_HEIGHT-20));
    ImGui::Begin("Demo window");
   
    if (ImGui::Button("REMOVE CUBE"))  action=1;

    if (ImGui::Button("ADD CUBE"))  action=2;

    if (ImGui::Button("EXTRUDE COLUMN"))  action=3;

    if (ImGui::Button("DIG COLUMN"))  action=4;

    if (ImGui::Button("PAINT PURPLE CUBE"))  action=5;

    if (ImGui::Button("PAINT PINK CUBE"))  action=6;

    if (ImGui::Button("PAINT BLUE CUBE"))  action=7;

    ImGui::End();

    }


    void Overlay::endFrame(SDL_Window* window) const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    
}
