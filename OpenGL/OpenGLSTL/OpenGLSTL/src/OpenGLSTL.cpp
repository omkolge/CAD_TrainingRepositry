#include<iostream>
#include<sstream>
#include<string>
#include"ShaderProgram.h"
#include"Texture2D.h"
#include"Camera.h"
#include"Mesh.h"

#define GLEW_STATIC
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/glm.hpp"


const char* APP_TITLE = "Introduction to Modern OpenGL-- Loading STL Model ";
int gWindowHeight = 768;
int gWindowWidth = 1024;
bool gWireFrame = false;

GLFWwindow* gWindow = NULL;

//close window after pressing esc key
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);//this func have mandate to with this parameters
bool initOpenGL();
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);

//void glfw_onMouseMove(GLFWwindow* window, double posX, double posY);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);

float gCubeAngle = 0.0f;
OrbitCamera orbitCamera;
float gYaw = 0.0f;
float gPitch = 0.0f;
float gRadius = 10.0f;

FPSCamera fpsCamera(glm::vec3(0.0f, 3.0f, 10.0f));
const double ZOOM_SENSITIVITY = -3.0;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;

//const float MOUSE_SENSITIVITY = 0.25f;
int main()
{
	//cout << "Welcome To OpenGL" << endl;
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("basic.vert", "basic.frag");

	//Model Positions

	glm::vec3 modelPos[] = {
		glm::vec3(0.0f, 0.0f, -5.0f),	//unknown
		glm::vec3(-2.0f, 0.0f, -5.0f),	//sphere
		glm::vec3(0.0f, 0.0f, -5.0f),	// GEAR-DIA-18.STL
		glm::vec3(0.0f, 0.0f, -5.0f),	//GAS-CYLINDER-TOP.STL
	};

	// Model scale
	glm::vec3 modelScale[] = {
	glm::vec3(0.01f, 0.010f, 0.010f),		//unknown
	glm::vec3(0.5f, 0.5f, 0.5f),			//sphere
	glm::vec3(1.0f, 1.0f, 1.0f),			// GEAR-DIA-18.STL
	glm::vec3(0.01f, 0.010f, 0.010f)		//GAS-CYLINDER-TOP.STL
	};

	//Load meshes and vertex
	const int numModels = 4;
	Mesh mesh[numModels];
	//Texture2D texture[numModels];
	mesh[0].loadSTL("stl/unknown.stl");
	mesh[1].loadSTL("stl/sphere.stl");
	mesh[2].loadSTL("stl/GEAR-DIA-18.STL");
	mesh[3].loadSTL("stl/GAS-CYLINDER-TOP.STL");
	/*mesh[0].loadOBJ("models/crate.obj");
	mesh[1].loadOBJ("models/woodcrate.obj");
	mesh[2].loadOBJ("models/robot.obj");
	mesh[3].loadOBJ("models/floor.obj");*/

	/*texture[0].loadTexture("crate.jpg", true);
	texture[1].loadTexture("woodcrate_diffuse.jpg", true);
	texture[2].loadTexture("robot_diffuse.jpg", true);
	texture[3].loadTexture("tile_floor.jpg", true);*/

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(gWindow))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		// Poll for and process events
		glfwPollEvents();
		update(deltaTime);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 model(1.0), view(1.0), projection(1.0);

		view = fpsCamera.getViewMatrix();//glm::lookAt(camPos, targetPos, up);

		// Create the projection matrix
		projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 200.0f);

		// Render the triangle
		shaderProgram.use();

		shaderProgram.setUniform("view", view);
		shaderProgram.setUniform("projection", projection);

		for (int i = 0; i < numModels; i++)
		{
			model = glm::translate(glm::mat4(1.0), modelPos[i]) * glm::scale(glm::mat4(1.0), modelScale[i]);
			shaderProgram.setUniform("model", model);

			//texture[i].bind(0);
			mesh[i].draw();
			//texture[i].unbind(0);
		}

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);
		lastTime = currentTime;
	}
	glfwTerminate();
	return 0;
}

//close window after pressing esc key
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		gWireFrame = !gWireFrame;
		if (gWireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

}

// Initialize GLFW and OpenGL
bool initOpenGL()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW intialization failed " << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);

	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(gWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW intialization failed " << std::endl;
		return false;

	}
	//callback
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);
	//glfwSetCursorPosCallback(gWindow, glfw_onMouseMove);
	glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

	// Hides and grabs cursor, unlimited movement
	glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);


	glClearColor(0.11f, 1.10f, 6.60f, 0.16f);
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	gWindowWidth = width;
	gWindowHeight = height;
	glViewport(0, 0, gWindowWidth, gWindowHeight);
}

//void glfw_onMouseMove(GLFWwindow* window, double posX, double posY)
//{
//	static glm::vec2 lastMousePos = glm::vec2(0, 0);
//
//	//updates angle based on left mouse button input to orbit around the cube
//	if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) == 1)
//	{
//
//		gYaw -= ((float)posX - lastMousePos.x) * MOUSE_SENSITIVITY;
//		gPitch += ((float)posY - lastMousePos.y) * MOUSE_SENSITIVITY;
//	}
//
//	if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_RIGHT) == 1)
//	{
//		float dx = 0.01f * ((float)posX - lastMousePos.x);
//		float dy= 0.01f * ((float)posY - lastMousePos.y);
//		gRadius += dx - dy;
//	}
//	lastMousePos.x = (float)posX;
//	lastMousePos.y = (float)posY;
//}
// Called by GLFW when the mouse wheel is rotated

void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITIVITY;

	fov = glm::clamp(fov, 1.0, 120.0);

	fpsCamera.setFOV((float)fov);
}

void update(double elapsedTime)
{
	// Camera orientation
	double mouseX, mouseY;

	// Get the current mouse cursor position delta
	glfwGetCursorPos(gWindow, &mouseX, &mouseY);

	// Rotate the camera the difference in mouse distance from the center screen.  Multiply this delta by a speed scaler
	fpsCamera.rotate((float)(gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	// Clamp mouse cursor to center of screen
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	// Camera FPS movement

	// Forward/backward
	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

	// Strafe left/right
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());

	// Up/down
	if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getUp());
	else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getUp());
}