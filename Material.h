#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>
using namespace std;

class Material
{
private:
	glm::vec3* _Kd;
	glm::vec3* _Ka;
	glm::vec3* _Ks;
	float _Ns;
	unsigned int _idTexture;
	string name;
	//image* Texture

public:

	void SetKd(float x, float y, float z);
	void SetKa(float x, float y, float z);
	void SetKs(float x, float y, float z);
	void SetNs(float ns);
	void SetName(string id);

	glm::vec3* GetKd(){return _Kd;}
	glm::vec3* GetKa(){return _Ka;}
	glm::vec3* GetKs(){return _Ks;}
	float GetNs(){return _Ns;}

	bool HasKd();
	bool HasKa();
	bool HasKs();
	bool HasNs();

	string GetName(){return name;}
	unsigned int GetIdTexture(){return _idTexture;}
	//void deleteTexture(){;}

	Material(void);
	~Material(void);
};
#endif
