#include "Material.h"


Material::Material(void)
{
	_Kd = NULL;
	_Ka = NULL;
	_Ks = NULL;
	_Ns = NULL;
}


Material::~Material(void)
{
}

void Material::SetKd(float x, float y, float z){
	_Kd = new glm::vec3(x,y,z);
}

void Material::SetKa(float x, float y, float z){
	_Ka = new glm::vec3(x,y,z);
}

void Material::SetKs(float x, float y, float z){
	_Ks = new glm::vec3(x,y,z);
}

void Material::SetNs(float ns){
	_Ns = ns;
}

void Material::SetName(string id) {
	name = id;
}

bool Material::HasKd(){
	if(_Kd != NULL){
		return true;
	}
	return false;
}

bool Material::HasKa(){
	if(_Ka != NULL){
		return true;
	}
	return false;
}

bool Material::HasKs(){
	if(_Ks != NULL){
		return true;
	}
	return false;
}

bool Material::HasNs(){
	if(_Ns != NULL){
		return true;
	}
	return false;
}