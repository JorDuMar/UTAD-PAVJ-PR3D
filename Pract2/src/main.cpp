#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif



#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../lib/State.h"
#include "../lib/Vertex.h"
#include "../lib/Shader.h"
#include "../lib/Buffer.h"
//#include "../lib/glew/GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/World.h"
#include "../lib/Mesh.h"
#include "../lib/Camera.h"
#include "../lib/Model.h"



#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


std::string readString(const std::string& filename) {
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
}

bool init()
{
	GLenum init = glewInit();
	if (init != GLEW_OK) { return false; }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	std::string vertexShader = readString("./data/vertex.glsl");
	std::string fragmentShader = readString("./data/fragment.glsl");
	
	State::defaultShader = std::make_shared<Shader>(vertexShader.c_str(), fragmentShader.c_str()); 
	return true;
}

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}
	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	
	//Init
	bool bOk = init();

	//Modificar pract
	//Crear Buffer->Mesh->Model (9 triangulos)
	//Crear Camera (pasarle viewmatrix, viewport, color)
	//Crear World y pasarle entidades

  //State::defaultShader->use(); //Se hace en mesh

	World myWorld;
	
	//---------CREATING MESH
	Vertex listVertex[3] = { Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(1, 1, 1)),
													Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(1, 1, 1)),
													Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1, 1, 1))};

	uint16_t listIndex[3] = {0, 1, 2};

	std::shared_ptr<Buffer> triangleBuffer = std::make_shared<Buffer>(listVertex, 3, listIndex, 3);
	std::shared_ptr<Mesh> triangleMesh = std::make_shared<Mesh>();
	triangleMesh->addBuffer(triangleBuffer);

	//----------CREATING CAMERA
	std::shared_ptr<Camera> mainCamera = std::make_shared<Camera>();
	mainCamera->setPosition(glm::vec3(0.f, 0.f, 6.f));
	mainCamera->setRotation(glm::vec3(0.f, 0.f, 0.f));
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	glm::mat4 projMatrix = glm::perspective(glm::radians(60.f), aspect, 0.1f, 100.f); //SE DEBERIA PASAR A CAMERA?
	mainCamera->setProjection(projMatrix);
	glm::ivec4 viewport = glm::ivec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	mainCamera->setViewport(viewport);
	glm::vec3 clearColor = glm::vec3(1.f, 1.f, 1.f);
	mainCamera->setClearColor(clearColor);

	myWorld.addEntity(mainCamera);

	int z = 0;
	int x = -3;
	for (z; z >= -6; z -= 3)
	{
		for (x; x <= 3; x += 3)
		{

			std::shared_ptr<Model> triangleModel = std::make_shared<Model>(triangleMesh);
			triangleModel->setPosition(glm::vec3(static_cast<float>(x), 0.f, static_cast<float>(z)));
			myWorld.addEntity(triangleModel);

		}
		x = -3;
	}

	// main loop
	float angle = 0.f;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		

		myWorld.draw();
		myWorld.update(deltaTime);
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown

	glfwTerminate();
}