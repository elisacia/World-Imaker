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


namespace glimac {
	void readFile(const FilePath &applicationPath,std::string filename,std::vector <glm::vec3> &list_ctrl);
}

#endif