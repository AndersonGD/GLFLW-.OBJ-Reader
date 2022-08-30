#ifndef GROUP_H
#define GROUP_H

#include "Face.h"

class Group
{
private:
	vector<Face*> *_faces;
	string name;
	string material;
public:
	Group(void);
	~Group(void);

	void addFace(Face* face);
	void SetName(string n);
	void SetMaterial(string mt);

	string GetMaterial(){return material;}

	int GetSizeOfFaces();
	Face* getFace(int i);
};
#endif
