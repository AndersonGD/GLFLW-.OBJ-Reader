#include "Face.h"


Face::Face(void)
{
	_idsVertex = new vector<int>;
	_idsNormal = new vector<int>;
	_idsTextureMap = new vector<int>;
}


Face::~Face(void)
{
}

void Face::setVertex(int id) {
	_idsVertex->push_back(id - 1);
}

void Face::setNormal(int id) {
	_idsNormal->push_back(id - 1);
}

void Face::setTextureMap(int id) {
	_idsTextureMap->push_back(id - 1);
}

int Face::GetNumberOfVertices(){
	return _idsVertex->size();
}

int Face::GetSizeOfVertices() {
	return _idsVertex->size();
}

bool Face::HasTextureMap(){
	return !_idsTextureMap->empty();
}

bool Face::HasNormal(){
	return !_idsNormal->empty();
}