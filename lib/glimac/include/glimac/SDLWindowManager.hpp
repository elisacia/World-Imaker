#pragma once

#include <cstdint>
#include "SDL2/SDL.h"
#include "glm.hpp"
#include <GL/glew.h>

namespace glimac {

class SDLWindowManager {

    private:   
        static bool m_instanciated;
        bool m_running;
   
    public:     
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        SDLWindowManager(uint32_t width, uint32_t height, const char* title);
        ~SDLWindowManager();
        bool pollEvent(SDL_Event& e);
        bool isKeyPressed(SDL_Keycode key) const;
        // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
        bool isMouseButtonPressed(uint32_t button) const;
        glm::ivec2 getMousePosition() const;
        void swapBuffers();
        // Return the time in seconds
        float getTime() const;
        inline bool isRunning() const { return m_running; }
        inline void exit() { m_running = false; };
    };

}
