#ifndef FILE_HPP 
#define FILE_HPP

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstddef>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp> 
#include <glm/glm.hpp> 
#include <glimac/Rbf.hpp>




namespace glimac {
	void readFile(const FilePath &applicationPath,std::string filename,std::vector <ControlPoint> &list_ctrl);
}

#endif