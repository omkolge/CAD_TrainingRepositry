#pragma once
#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <map>
#include "glm/gtc/type_ptr.hpp"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	
	enum ShaderType {
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use();
	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);

	void setUniform(const GLchar* name, const glm::mat4& m);

	GLuint getProgram() const;

private:
	std::string fileToString(const std::string& filename);
	void checkCompilerErrors(GLuint shader, ShaderType type);
	GLuint getUniformLocation(const GLchar* name);
	
	GLuint mHandle;
	std::map<std::string, GLint> mUniformLocations;
};