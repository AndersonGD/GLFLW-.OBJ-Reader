#ifndef FACE_H
#define FACE_H

#include <vector>
using namespace std;

class Face
{
private:
	vector<int> *_idsVertex;
	vector<int> *_idsNormal;
	vector<int> *_idsTextureMap;
public:
	Face(void);
	~Face(void);

	int GetNumberOfVertices();

	void setVertex(int id);
	void setNormal(int id);
	void setTextureMap(int id);

	int GetNormal(int id) { return _idsNormal->at(id); }
	int GetVertex(int id) { return _idsVertex->at(id); }
	int GetTextureMap(int id) { return _idsTextureMap->at(id); }

	bool HasTextureMap();
	bool HasNormal();

	int GetSizeOfVertices();

};
#endif
