#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram()
	:mHandle(0)
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mHandle);
}

bool ShaderProgram::loadShaders(const char* vsFilename, const char* fsFilename)
{
	std::string vsString = fileToString(vsFilename);
	std::string fsString = fileToString(fsFilename);
	const GLchar* vsSourePtr = vsString.c_str();
	const GLchar* fsSourePtr = fsString.c_str();


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsSourePtr, NULL);
	glShaderSource(fs, 1, &fsSourePtr, NULL);

	glCompileShader(vs);
	checkCompilerErrors(vs, VERTEX);
	glCompileShader(fs);
	checkCompilerErrors(fs, FRAGMENT);

	mHandle = glCreateProgram();
	glAttachShader(mHandle, vs);
	glAttachShader(mHandle, fs);
	glLinkProgram(mHandle);

	checkCompilerErrors(mHandle, PROGRAM);

	glDeleteShader(vs);
	glDeleteShader(fs);
	mUniformLocations.clear();
	return true;
}

void ShaderProgram::use()
{
	if (mHandle > 0) {
		glUseProgram(mHandle);
	}
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec2& v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec3& v)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec4& v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4& m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

GLuint ShaderProgram::getProgram() const
{
	return mHandle;
}

std::string ShaderProgram::fileToString(const std::string& filename)
{
	std::stringstream ss;
	std::ifstream file;

	try
	{
		file.open(filename, std::ios::in);
		if (!file.fail()) {
			ss << file.rdbuf();
		}
		file.close();
	}
	catch (const std::exception&)
	{
		std::cerr << "Error reading shader filename!" << std::endl;
	}

	return ss.str();
}

void ShaderProgram::checkCompilerErrors(GLuint shader, ShaderType type)
{
	int status = 0;

	if (type == PROGRAM) {
		glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length = 0;
			glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);
			std::string errorlog(length, ' ');
			glGetProgramInfoLog(mHandle, length, &length, &errorlog[0]);
			std::cerr << "Error! Program failed to link. " << errorlog << std::endl;
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::string errorlog(length, ' ');
			glGetShaderInfoLog(shader, length, &length, &errorlog[0]);
			std::cerr << "Error! Shader failed to compile. " << errorlog << std::endl;
		}
	}
}

GLuint ShaderProgram::getUniformLocation(const GLchar* name)
{
	std::map<std::string, GLint>::iterator it = mUniformLocations.find(name);

	if (it == mUniformLocations.end()) {
		mUniformLocations[name] = glGetUniformLocation(mHandle, name);
	}

	return mUniformLocations[name];
}
