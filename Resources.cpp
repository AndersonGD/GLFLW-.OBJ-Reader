#include "Resources.h"

Resources* Resources::_instance = 0;

Resources::Resources(void)
{
	GLuint textures[50];
	glGenTextures(50, textures);
	materials_ = new map<string, Material*>;
}


Resources::~Resources(void)
{
}

Material* Resources::GetMaterial(string name){
	auto temp = materials_->find(name);

	if (temp == materials_->end()){
		return NULL;
	}

	return temp->second;
}

Resources* Resources::GetInstance(){
	if (_instance == 0){
		_instance = new Resources;
	}
	return _instance;
}

void Resources::AddMaterial(string name, Material* mt){
	materials_->insert(make_pair(name, mt));
}