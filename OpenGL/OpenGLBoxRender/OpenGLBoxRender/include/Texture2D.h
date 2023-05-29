#pragma once
#include <string>
#include "GL/glew.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	bool loadTexture(const std::string& filename, bool generateMipMaps = true);
	void bind(GLuint texUint = 0);
	void unbind(GLuint texUint = 0);

private:
	GLuint mTexture;

};

