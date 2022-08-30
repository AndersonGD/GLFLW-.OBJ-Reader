#include "Mesh.h"


Mesh::Mesh(void)
{
	_vertex = new vector<glm::vec3*>;
	_normal = new vector<glm::vec3*>;
	_textureMap = new vector<glm::vec2*>;
	_faces = new vector<Face*>;
	_groups = new vector<Group*>;
	_mtlibPath = "";
}


Mesh::~Mesh(void)
{
}

void Mesh::addVertex(float x, float y, float z){
	glm::vec3 *vertex;
	vertex = new glm::vec3(x,y,z);
	_vertex->push_back(vertex);
}

void Mesh::addNormal(float x, float y, float z){
	glm::vec3 *vertex;
	vertex = new glm::vec3(x,y,z);
	_normal->push_back(vertex);
}

void Mesh::addTexturemap(float x, float y){
	glm::vec2 *vertex;
	vertex = new glm::vec2(x,y);
	_textureMap->push_back(vertex);
}

void Mesh::addFace(){
	Face* face;
	face = new Face;
	_faces->push_back(face);
	_groups->back()->addFace(face);
}

Face* Mesh::getActualFace() {
	return _faces->back();
}

void Mesh::addGroup(){
	Group* group;
	group = new Group;
	_groups->push_back(group);
}

void Mesh::SetMtLibPath(string path){
	_mtlibPath = path;
}

Group* Mesh::getActualGroup() {
	return _groups->back();
}

Group* Mesh::getGroup(int i){
	return _groups->at(i);
}

int Mesh::sizeOfGroup() {
	return _groups->size();
}