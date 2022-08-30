#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include "Group.h"

class Mesh
{
private:
	string _mtlibPath;
	vector<glm::vec3*> *_vertex;
	vector<glm::vec3*> *_normal;
	vector<glm::vec2*> *_textureMap; 
	vector<Face*> *_faces;
	vector<Group*> *_groups;
public:
	Mesh(void);
	~Mesh(void);

	void SetMtLibPath(string path);
	void addVertex(float x, float y, float z);
	void addNormal(float x, float y, float z);
	void addTexturemap(float x, float y);
	void addFace();
	void addGroup();

	Face* getActualFace();
	Group* getActualGroup();
	Group* getGroup(int i);

	float GetVertexX(int id) { return _vertex->at(id)->x; }
	float GetVertexY(int id) { return _vertex->at(id)->y; }
	float GetVertexZ(int id) { return _vertex->at(id)->z; }

	float GetNormalX(int id) { return _normal->at(id)->x; }
	float GetNormalY(int id) { return _normal->at(id)->y; }
	float GetNormalZ(int id) { return _normal->at(id)->z; }

	float GetTextureMapX(int id) { return _textureMap->at(id)->x; }
	float GetTextureMapY(int id) { return _textureMap->at(id)->y; }

	int sizeOfGroup();
};
#endif
