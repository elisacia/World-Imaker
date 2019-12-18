#ifndef CONTROLS_HPP 
#define CONTROLS_HPP

#pragma once

#include <glimac/glm.hpp> 
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Rbf.hpp>
#include <iostream>
#include <SDL2/SDL.h>


namespace glimac {

// Camera events controller
const void move_camera_key_pressed(const SDL_Event &e, FreeFlyCamera &camera);
// Cursor events controller
const void move_cursor_key_pressed(const SDL_Event &e, Cursor &cursor); 
// Sculpting events controller
void sculpt_cubes(SDL_Event &e, std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action,const float epsilon); 
// Painting events controller
void paint_cubes(std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action, const float epsilon);
// Radial Basis Functions
void cleanScene(std::vector <Cube> &list_cubes, const int volume);


}

#endif