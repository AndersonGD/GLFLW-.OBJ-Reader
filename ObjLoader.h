#ifndef OBJLOADER_H
#define OBJLOADER_H
#define SDL_MAIN_HANDLED

#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include "Mesh.h"
#include "Resources.h"

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	Mesh* loadOBJ(const char* fileName);
	void loadMTL(const char* path);
};
#endif
