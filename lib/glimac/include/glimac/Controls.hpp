#ifndef CONTROLS_HPP 
#define CONTROLS_HPP

#pragma once

#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/File.hpp>


namespace glimac {

// Camera events controller
const void moveCamera(const SDL_Event &e, FreeFlyCamera &camera);
// Cursor events controller
const void moveCursor(const SDL_Event &e, Cursor &cursor); 
// Sculpting events controller
void sculptCubes(SDL_Event &e, std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action,const float epsilon); 
// Painting events controller
void paintCubes(std::vector <Cube> &list_cubes, Cursor &cursor, glm::vec3 &cursorPos, const int volume, const int action, const float epsilon);
// Radial Basis Functions
void cleanScene(std::vector <Cube> &list_cubes, const int volume);
// Saving scene
void saveControl(const FilePath &applicationPath,std::string filename,std::vector <Cube> &list_cubes,const int action);

}

#endif