#include "ObjLoader.h"
#include "Render3D.h"
#include <GLFW\glfw3.h>
#include "FpsLimiter.h"

GLFWwindow *window;
ObjLoader* OBJloader;
Mesh* mesh;
Render3D* render3d;
FpsLimiter* fps;

// angulo da rotação da direção da câmera.
float angulo = 0.0;
// vetor que representa a direção atual da câmera.
float direcaoX = 0.0f, direcaoZ = -1.0f;
// posição X,Z da câmera.
float posicaoX = 0.0f, posicaoZ = 5.0f;

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_specular[] = { 1.0, 1.0, 0.0,1.0 };
GLfloat light_diffuse[] = { 0.50, 0.50, 0.5,1.0 };

int w = 800;
int h = 600;

float _fps;
float _time;


void init();
void load();
void draw();
void light();
void moveCamera();


int main(int argc, char *argv[]){

	init();
	load();

	render3d->setMesh(mesh);
	
	while (!glfwWindowShouldClose(window)) {
		fps->begin();

		_time += 0.1;

		draw();

		
		_fps = fps->end();
		static int frameCounter = 0;
		frameCounter++;

		if (frameCounter == 10000) {
			cout << _fps << endl;
			frameCounter = 0;
		}
		
		//moveCamera();
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void init(){

	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
		cout << "SDL ERROR, could not initialize!";
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		cout << ("IMG_Init: Failed to init required jpg and png support!\n");
		cout << ("IMG_Init: %s\n", IMG_GetError());
		//handle error
	}

	if (!glfwInit()) {
		cout << "GFLW ERROR INIT";
	}


	window = glfwCreateWindow(w, h, "OBJ READER", NULL, NULL);

	if (!window) {
		glfwTerminate();
		cout << "GFLW ERROR WINDOW";
	}

	glfwMakeContextCurrent(window);


	OBJloader = new ObjLoader;
	render3d = new Render3D;
	fps = new FpsLimiter;

	fps->setMaxFPS(60.0f);
	_time = 0.0f;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	light();
	
}

void draw(){
	glClearColor(0, 0.2, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 1.0f, 5.0f,
		0.0f, 0.8f, -1.0f,
		0.0f, 1.0f, 0.0f);

	render3d->render();

	glfwSwapBuffers(window);
	
}

void load(){
	/*mesh = OBJloader->loadOBJ("Audi.obj");
	OBJloader->loadMTL("Audi.mtl");*/

	mesh = OBJloader->loadOBJ("monkey.obj");

	//mesh = OBJloader->loadOBJ("torreDiPisa.obj");
	//OBJloader->loadMTL("torreDiPisa.mtl");

	/*mesh = OBJloader->loadOBJ("car.obj");
	OBJloader->loadMTL("car.mtl");*/
}

void light(){
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void moveCamera() {
	if (glfwGetKey(window, 'S')) {
		posicaoX -= direcaoX * 0.1;
		posicaoZ -= direcaoZ * 0.1;
	}
	else if (glfwGetKey(window, 'W')) {
		posicaoX += direcaoX * 0.1;
		posicaoZ += direcaoZ * 0.1;
	}
	if (glfwGetKey(window, 'A')) {
		posicaoX += direcaoZ * 0.1;
		posicaoZ -= direcaoX * 0.1;
	}
	else if (glfwGetKey(window, 'D')) {
		posicaoX -= direcaoZ * 0.1;
		posicaoZ += direcaoX * 0.1;
	}
}

