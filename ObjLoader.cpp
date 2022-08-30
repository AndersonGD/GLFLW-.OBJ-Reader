#include "ObjLoader.h"



ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

Mesh* ObjLoader::loadOBJ(const char* path) {
	ifstream file(path);

	if (!path) {
		cout << "Erro: " << path << endl;
		return NULL;
	}

	Mesh* mesh;
	mesh = new Mesh;

	string header, linha;
	char buffer[256];
	int contV;

	while (!file.eof()) {

		file >> header;

		if (header == "#") {
			file.getline(buffer, 256);
		}

		else if(header == "mtllib"){
			string linha;
			getline(file, linha);
			mesh->SetMtLibPath(linha);
		}

		else if (header == "v") {
			float x, y, z;
			file >> x >> y >> z;
			mesh->addVertex(x, y, z);
		}

		else if (header == "vt") {
			float x, y;
			file >> x >> y;
			mesh->addTexturemap(x, y);
		}

		else if (header == "vn") {
			float x, y, z;
			file >> x >> y >> z;
			mesh->addNormal(x, y, z);
		}

		else if (header == "g") {
			mesh->addGroup();

			string value = "";
			getline(file, linha);
			int a = linha.length();

			for(int i = 1; i < a; i++){//1 para eliminar o espaço
				value += linha.c_str()[i];
			}

			mesh->getActualGroup()->SetName(value);
			linha.clear();
			value.clear();

		}
		else if(header == "usemtl"){
			string value = "";
			getline(file, linha);
			int a = linha.length();

			for(int i = 1; i < a; i++){//1 para eliminar o espaço
				value += linha.c_str()[i];
			}

			mesh->getActualGroup()->SetMaterial(value);
			linha.clear();
			value.clear();
		}

		else if (header == "f") {

			mesh->addFace();
			int count = 0;
			string value = "";

			int i = 0;	//controle do while para pegar todos os caracteres de indice até a / ou final
			int k = 0;

			getline(file, linha);

			int a = linha.length();

			for (int j = 0; j < a; j++) {

				if (linha.c_str()[j] != '/' && linha.c_str()[j] != ' ')
				{
					if ((j-1) == i) {	//verificar para ver se o caractere atual não faz parte de um indice já incluido
						i = j;
						k = 0;	//offset, quantidade de caracteres que o indice possui EX: 1024 = 4 caracteres

						while (linha.c_str()[i] != '/' && linha.c_str()[i] != ' ' && linha.c_str()[i] != NULL) {	//pegar todos os caracteres de indice EX: indice 103
							value += linha.c_str()[i];
							i++;
							k++;
						}

						if (linha.c_str()[j - 1] == ' ') {	//se o caractere anterior é espaço, significa que é um VERTICE
							count = 1;
						}
						else {

							if (linha.c_str()[j - 1] == '/' && linha.c_str()[j - 2] == '/') {	//se a configuração for V//N ->>>>>>2 barras seguidas atrás do indice atual, então é NORMAL
								count = 3;
							}

							else if (linha.c_str()[j + k] == '/') {	//se houver uma barra depois deste indice só pode ser uma TEXTURA
								count = 2;
							}
							else {
								count = 3;			//se não for nenhuma das outras opções é a configuração completa V/T/N, então é NORMAL
							}

						}
					}
				}

				if (count == 1) {
					mesh->getActualFace()->setVertex(stoi(value));
					value.clear();
					count = 0;
				}
				else if (count == 2) {
					mesh->getActualFace()->setTextureMap(stoi(value));
					value.clear();
					count = 0;
				}
				else if (count == 3) {
					mesh->getActualFace()->setNormal(stoi(value));
					value.clear();
					count = 0;
				}
			}
		}
	}
	return mesh;
}

void ObjLoader::loadMTL(const char* path) {
	ifstream file;
	string header, linha;
	char buffer[256];
	
	file.open(path);
	if (!file.is_open())
	{
		cout << "Impossivel abrir arquivo mtl " << path << endl;
	}
	else
	{

		file >> header;

		while (!file.eof()) {

			if (header != "newmtl") {
				file.getline(buffer, 256);
				file >> header;
			}

			if (header == "newmtl") {

				Material *mt;
				mt = new Material;

				file.getline(buffer, 1024);
				const char * c = &buffer[1];
				mt->SetName(c);

				while (file >> header && header != "newmtl")
				{
					if (header == "Ns")
					{
						float a = 0.0;
						file >> a;
						mt->SetNs(a);
					}
					if (header == "Ka")
					{
						float x, y, z;
						file >> x >> y >> z;
						mt->SetKa(x, y, z);
					}
					if (header == "Kd")
					{
						float x, y, z;
						file >> x >> y >> z;
						mt->SetKd(x, y, z);
					}
					if (header == "Ks")
					{
						float x, y, z;
						file >> x >> y >> z;
						mt->SetKs(x, y, z);
					}
					if (header == "map_Kd")
					{
						file.getline(buffer, 1024);

						const char * c = &buffer[1];

						SDL_Surface* image;
						image = IMG_Load(c);

						printf("Oh My Goodness, an error : %s", IMG_GetError());

						//cria textura
						if (image != NULL) {
							glBindTexture(GL_TEXTURE_2D, mt->GetIdTexture());

							int Mode = GL_RGB;

							if (image->format->BytesPerPixel == 4) {
								Mode = GL_RGBA;
							}

							glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							SDL_FreeSurface(image);
						}
					}
				}
				Resources::GetInstance()->AddMaterial(mt->GetName(), mt);
			}
		}
	}
}