//-----------------------------------------------------------------------------
// Mesh.h by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// Basic Mesh class
//-----------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "glm/glm.hpp"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class Mesh
{
public:

	Mesh();
	~Mesh();

	bool loadSTL(const std::string& filename);
	void draw();

private:

	void initBuffers();

	bool mLoaded;
	std::vector<Vertex> mVertices;
	GLuint mVBO, mVAO;
};
#endif //MESH_H
