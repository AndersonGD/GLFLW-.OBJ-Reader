#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include "Material.h"
#include "Render3D.h"

class Resources
{
private:
	map <string, Material*> *materials_;
	static Resources *_instance;
public:
	Resources(void);
	~Resources();

	static Resources* GetInstance();

	Material* GetMaterial(string name);
	void AddMaterial(string name, Material* mt);
};
#endif
