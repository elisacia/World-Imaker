#ifndef GLIMAC_Overlay
#define GLIMAC_Overlay

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>
#include <glimac/common.hpp>


namespace glimac
{
	class Overlay
	{
		public:
			// Constructor
			Overlay(){};
			//Destructor
			~Overlay();
			void initImgui(SDL_Window* window,SDL_GLContext* glContext) const;
			void beginFrame(SDL_Window* window) const;
			float drawOverlay(int &action,  glm::vec4 &LightDir) const ;
    		void endFrame(SDL_Window* window) const;
    		void clean(SDL_Window* window) const;
    		
	};
}

#endif //GLIMAC_Overlay