#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include<string>
#include <map>
#define GLEW_STATIC
#include "GL/glew.h"
#include "glm/glm.hpp"


using std::string;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	enum ShaderType
	{
		VERTEX,
		FRAGEMENT,
		PROGRAM
	};
	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void use(); //activate shader program

	GLuint getProgram() const;

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& v);

private:

	string fileToString(const string& filename);
	void  checkCompileErrors(GLuint shader, ShaderType type);
	// We are going to speed up looking for uniforms by keeping their locations in a map
	GLint getUniformLocation(const GLchar* name);


	GLuint mHandle;
	std::map<string, GLint> mUniformLocations;
};
#endif