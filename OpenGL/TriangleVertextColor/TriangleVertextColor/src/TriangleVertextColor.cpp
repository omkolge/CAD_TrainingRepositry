//#include<iostream>
//#include<sstream>
//
//#define GLEW_STATIC
//#include"GL/glew.h"
//#include"GLFW/glfw3.h"
//#include<cmath>
//
//const char* APP_TITLE = "Introduction to Modern OpenGL -- Hello Traingle";
//const int gWindowWidth = 800;
//const int gWindowHeight = 600;
//
//// Shaders
//const GLchar* vertexShaderSrc =
//"#version 330 core\n"
//"layout (location = 0) in vec3 pos;"
//"layout (location = 1) in vec3 color;"
//"\n"
//"out vec3 vert_color;"
//"void main()"
//"{"
//"    vert_color = color;"
//"    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
//"}";
//
//const GLchar* fragmentShaderSrc =
//"#version 330 core\n"
//"in vec3 vert_color;"
//"out vec4 frag_color;"
//"void main()"
//"{"
//"    frag_color = vec4(vert_color, 1.0f);"
//"}";
//
//
//GLFWwindow* gWindow = NULL;
//
////close window after pressing esc key
//void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);//this func have mandate to with this parameters
//bool initOpenGL();
////void rotateVerticesColor(GLfloat* vertices, int count, GLfloat speed);
//int main()
//{
//	//cout << "Welcome To OpenGL" << endl;
//	if (!initOpenGL())
//	{
//		std::cerr << "GLFW initialization failed" << std::endl;
//		return false;
//	}
//	// 1. Set up an array of vertices for a triangle
//	GLfloat vert_pos[] = {
//		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// Top
//		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  	// Right 
//		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f 	// Left
//	};
//
//	// 2. Set up buffers on the GPU
//	GLuint vbo, vao;
//
//	GLfloat rotationSpeed = 30.0f;
//	GLfloat currentTime = 0.0f;
//
//	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);		// "bind" or set as the current buffer we are working with
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_DYNAMIC_DRAW);// copy the data from CPU to GPU "GL_STATIC_DRAW" "GL_DYNAMIC_DRAW" GL_STREAM_DRAW
//
//	glGenVertexArrays(1, &vao);				// Tell OpenGL to create new Vertex Array Object
//	glBindVertexArray(vao);					// Make it the current one
//
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, NULL);
//	glEnableVertexAttribArray(0);	// Enable the first attribute or attribute "0"
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
//	glEnableVertexAttribArray(1);
//
//	//position
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//	//color
//	//glBindBuffer(GL_ARRAY_BUFFER, vbo2);
//
//
//	// 3. Create vertex shader
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, &vertexShaderSrc, NULL);
//	glCompileShader(vs);
//
//	// Check for compile errors
//	GLint result;
//	GLchar infoLog[512];
//	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
//		std::cout << "Error! Vertex shader failed to compile. " << infoLog << std::endl;
//	}
//
//	// 4. Create fragment shader
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, &fragmentShaderSrc, NULL);
//	glCompileShader(fs);
//
//	// Check for compile errors
//	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(fs, sizeof(infoLog), NULL, infoLog);
//		std::cout << "Error! Fragment shader failed to compile. " << infoLog << std::endl;
//	}
//
//	// 5. Create shader program and link shaders to program
//	GLint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vs);
//	glAttachShader(shaderProgram, fs);
//	glLinkProgram(shaderProgram);
//	GLuint colorLocation = glGetAttribLocation(shaderProgram, "vertexShaderSrc");
//	// Check for linker errors
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
//	if (!result)
//	{
//		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
//		std::cout << "Error! Shader program linker failure " << infoLog << std::endl;
//	}
//
//
//	// Clean up shaders, do not need them anymore since they are linked to a shader program
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//
//	while (!glfwWindowShouldClose(gWindow))
//	{
//
//		// Poll for and process events
//		glfwPollEvents();
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		// Clear the screen
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		currentTime += glfwGetTime() * rotationSpeed;
//		for (int i = 0; i < 18; i += 6) {
//			if (vert_pos[i + 3] == 1.0)
//				vert_pos[i + 3] = 0.0f;
//			else
//				vert_pos[i + 3] = 1.0f;
//
//			if (vert_pos[i + 4] == 0)
//				vert_pos[i + 4] = 1.0f;
//			else
//				vert_pos[i + 4] = 0.0f;
//
//			if (vert_pos[i + 5] == 0)
//				vert_pos[i + 5] = 1.0f;
//			else
//				vert_pos[i + 5] = 0.0f;
//
//		}
//		// Render the triangle
//		glUseProgram(shaderProgram);
//		glBindVertexArray(vao);
//
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_DYNAMIC_DRAW);
//		glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(colorLocation);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glBindVertexArray(0);
//
//
//		// Swap front and back buffers
//		glfwSwapBuffers(gWindow);
//	}
//
//	// Clean up
//	glDeleteProgram(shaderProgram);
//	glDeleteVertexArrays(1, &vao);
//	glDeleteBuffers(1, &vbo);
//	glfwTerminate();
//	return 0;
//}
//
////close window after pressing esc key
//void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//
//}
//
//// Initialize GLFW and OpenGL
//bool initOpenGL()
//{
//	if (!glfwInit())
//	{
//		std::cerr << "GLFW intialization failed " << std::endl;
//		return false;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
//
//	if (gWindow == NULL)
//	{
//		std::cerr << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return false;
//	}
//	glfwMakeContextCurrent(gWindow);
//	glfwSetKeyCallback(gWindow, glfw_onKey);
//	glewExperimental = GL_TRUE;
//	if (glewInit() != 0)
//	{
//		std::cerr << "GLEW intialization failed " << std::endl;
//		return false;
//
//	}
//	glClearColor(0.11f, 1.10f, 6.60f, 0.16f);
//	return true;
//}



#include<iostream>
#include<sstream>

#define GLEW_STATIC
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<cmath>

const char* APP_TITLE = "Introduction to Modern OpenGL -- Hello Traingle";
const int gWindowWidth = 800;
const int gWindowHeight = 600;

// Shaders
const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;"
"layout (location = 1) in vec3 color;"
"\n"
"out vec3 vert_color;"
"void main()"
"{"
"    vert_color = color;"
"    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
"}";

const GLchar* fragmentShaderSrc =
"#version 330 core\n"
"in vec3 vert_color;"
"out vec4 frag_color;"
"void main()"
"{"
"    frag_color = vec4(vert_color, 1.0f);"
"}";


GLFWwindow* gWindow = NULL;

//close window after pressing esc key
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);//this func have mandate to with this parameters
bool initOpenGL();
//void rotateVerticesColor(GLfloat* vertices, int count, GLfloat speed);
int main()
{
	//cout << "Welcome To OpenGL" << endl;
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}
	// 1. Set up an array of vertices for a triangle
	GLfloat vert_pos[] = {
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// Top
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  	// Right 
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f 	   // Left
	};

	// 2. Set up buffers on the GPU
	GLuint vbo, vao;

	GLfloat rotationSpeed = 30.0f;
	GLfloat elapsedTime = 0.0f;



	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);		// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_DYNAMIC_DRAW);// copy the data from CPU to GPU "GL_STATIC_DRAW" "GL_DYNAMIC_DRAW" GL_STREAM_DRAW

	glGenVertexArrays(1, &vao);				// Tell OpenGL to create new Vertex Array Object
	glBindVertexArray(vao);					// Make it the current one


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, NULL);
	glEnableVertexAttribArray(0);	// Enable the first attribute or attribute "0"

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);


	//position
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderSrc, NULL);
	glCompileShader(vs);

	// Check for compile errors
	GLint result;
	GLchar infoLog[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error! Vertex shader failed to compile. " << infoLog << std::endl;
	}

	// 4. Create fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fs);

	// Check for compile errors
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fs, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error! Fragment shader failed to compile. " << infoLog << std::endl;
	}

	// 5. Create shader program and link shaders to program
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	GLuint colorLocation = glGetAttribLocation(shaderProgram, "vertexShaderSrc");
	// Check for linker errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error! Shader program linker failure " << infoLog << std::endl;
	}


	// Clean up shaders, do not need them anymore since they are linked to a shader program
	glDeleteShader(vs);
	glDeleteShader(fs);


	while (!glfwWindowShouldClose(gWindow))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - elapsedTime;
		//currentTime += glfwGetTime() * rotationSpeed;

		if (deltaTime > 0.2) {
			elapsedTime = currentTime;
			GLfloat temp[] = {
						vert_pos[0],  vert_pos[1],  vert_pos[2],  vert_pos[9],  vert_pos[10], vert_pos[11],
						vert_pos[6],  vert_pos[7],  vert_pos[8],  vert_pos[15], vert_pos[16], vert_pos[17],
						vert_pos[12], vert_pos[13], vert_pos[14], vert_pos[3],  vert_pos[4],  vert_pos[5]
			};
			std::memcpy(vert_pos, temp, sizeof(vert_pos));
			deltaTime = 0.0;
		}

		// Render the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vert_pos), vert_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vert_pos), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(colorLocation);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);
	}

	// Clean up
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
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
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glewExperimental = GL_TRUE;
	if (glewInit() != 0)
	{
		std::cerr << "GLEW intialization failed " << std::endl;
		return false;

	}
	glClearColor(0.11f, 1.10f, 6.60f, 0.16f);
	return true;
}