#include "Render3D.h"
#include "Resources.h"


Render3D::Render3D(Mesh* mesh) {
	this->mesh = mesh;
}

Render3D::Render3D()
{
}


Render3D::~Render3D()
{
}

void Render3D::render() {

	GLenum PRIM = GL_TRIANGLES;
	int nv = 3;

	glBegin(PRIM);
	int a = mesh->sizeOfGroup();
	for (int i = 0; i < a; i++) {

		Group* group = mesh->getGroup(i);

		
			Material *mat = Resources::GetInstance()->GetMaterial(group->GetMaterial());
			if (mat != NULL) {
				if (mat->HasKa()) {
					GLfloat ambient[] = { mat->GetKa()->x, mat->GetKa()->y, mat->GetKa()->z, 1.0 };
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				}

				if (mat->HasKd()) {
					GLfloat diffuse[] = { mat->GetKd()->x, mat->GetKd()->y, mat->GetKd()->z, 1.0 };
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				}

				if (mat->HasKs()) {
					GLfloat specular[] = { mat->GetKs()->x, mat->GetKs()->y, mat->GetKs()->z, 1.0 };
					glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				}

				if (mat->HasNs()) {
					GLfloat shininess[] = { mat->GetNs() };
					glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
				}

			}
			int s = group->GetSizeOfFaces();

			for (int j = 0; j < s; j++) {

			Face* face = group->getFace(j);

			int sv = face->GetSizeOfVertices();

			if (nv > 4) {
				glEnd();
				glBegin(GL_POLYGON);
			}
			

			else if (sv != nv) {

				nv = sv;

				if (PRIM == GL_TRIANGLES) {
					PRIM == GL_POLYGON;
				}
				else {
					PRIM == GL_TRIANGLES;
				}

				glEnd();
				glBegin(PRIM);

			}

			//render
			int numV = face->GetNumberOfVertices();
			for (int k = 0; k < numV; k++) {
				int idVertex = face->GetVertex(k);

				if (face->HasNormal()) {
					int idNormal = face->GetNormal(k);
					glNormal3f(mesh->GetNormalX(idNormal), mesh->GetNormalY(idNormal), mesh->GetNormalZ(idNormal));
				}

				if (face->HasTextureMap()) {
					int idTexture = face->GetTextureMap(k);
					glTexCoord2f(mesh->GetTextureMapX(idTexture), mesh->GetTextureMapY(idTexture));
				}

				glVertex3f(mesh->GetVertexX(idVertex), mesh->GetVertexY(idVertex), mesh->GetVertexZ(idVertex));
			}
		}
	}

}

void Render3D::setMesh(Mesh *m) {
	mesh = m;
}