#pragma once

#include <vector>
#include <string>
#include <limits>
#include <algorithm>

#include "GL/glew.h"
#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	//glm::vec2 texCoords;
};

struct BoundingBox {
	float x_min = std::numeric_limits<float>::max(),
		y_min = std::numeric_limits<float>::max(),
		z_min = std::numeric_limits<float>::max(),
		x_max = std::numeric_limits<float>::min(),
		y_max = std::numeric_limits<float>::min(),
		z_max = std::numeric_limits<float>::min();
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	//bool loadOBJ(const std::string& filename);
	bool loadSTL(const std::string& filename);
	void drawModel();
	void drawBoundingBox();
	BoundingBox getBoundingBox();

private:
	void initBuffers();
	void initBuffersforBoundingBox(); 
	
	bool flag = true;
	bool mLoaded;
	std::vector<Vertex> mVertices;
	GLuint mVBO, mVAO;
	GLuint bVBO, bVAO, bIBO;
	BoundingBox box;
};

