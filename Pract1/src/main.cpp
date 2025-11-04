#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif



#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../lib/Vertex.h"
#include "../lib/Shader.h"
#include "../lib/Buffer.h"
#include "../lib/glfw/glfw3.h"
#include "../lib/glm/gtc/matrix_transform.hpp"


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
	std::string vertexShader = readString("./data/vertex.glsl");
	std::string fragmentShader = readString("./data/fragment.glsl");

	Shader* shader = new Shader(vertexShader.c_str(), fragmentShader.c_str());
	shader->use();
	
	Vertex listVertex[3] = { Vertex(glm::vec3(0, 0.5f, 0), glm::vec3(1, 1, 1)),
													Vertex(glm::vec3(-0.5f, -0.5f, 0), glm::vec3(1, 1, 1)),
													Vertex(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1, 1, 1))};

	uint16_t listIndex[3] = {0, 1, 2};


	Buffer* buffer = new Buffer(listVertex, 3, listIndex, 3);
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	glm::mat4 projMatrix = glm::perspective(glm::radians(60.f), aspect, 0.1f, 100.f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 6.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), glm::vec3(1.f, 1.f, 1.f));
	int locMVP = shader->getLocation("mvp");

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
		
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//create MVP, send to shader and draw
		angle += 32 * deltaTime;
		angle = fmod(angle, 360.f);
		if (angle < 0.f) { angle += 360.f; }

		int z = 0;
		int x = -3;
		for (z; z >= -6; z -= 3)
		{
			for (x; x <= 3; x += 3)
			{
				glm::mat4 translateMatrix = glm::translate(glm::mat4(), glm::vec3(static_cast<float>(x), 0.f, static_cast<float>(z)));
				glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));

				glm::mat4 modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
				glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;
				shader->setMatrix(locMVP, MVP);
				buffer->draw(*shader);
			}
			x = -3;

		}
		
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	delete shader;
	delete buffer;
	glfwTerminate();
}