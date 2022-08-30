#include "Group.h"


Group::Group(void)
{
	_faces = new vector<Face*>;
}


Group::~Group(void)
{
}

void Group::addFace(Face* face){
	_faces->push_back(face);
}

int Group::GetSizeOfFaces() {
	return _faces->size();
}

Face* Group::getFace(int i) {
	return _faces->at(i);
}

void Group::SetName(string n){
	name = n;
}

void Group::SetMaterial(string mt){
	material = mt;
}