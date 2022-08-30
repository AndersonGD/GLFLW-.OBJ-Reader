#ifndef RENDER3D_H
#define RENDER3D_H

#include <Windows.h>
#include "Mesh.h"
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class Render3D
{
private:
	Mesh* mesh;
public:
	Render3D();
	Render3D(Mesh* mesh);
	~Render3D();

	void render();

	void setMesh(Mesh *m);
};
#endif
