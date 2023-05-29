#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh()
	:mLoaded(false)
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

bool Mesh::loadSTL(const std::string& filename)
{
	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec3> tempNormals;

	if (filename.find(".stl") != std::string::npos || filename.find(".STL") != std::string::npos) {
		std::ifstream fin(filename, std::ios::in);
		if (!fin) {
			std::cerr << "Cannot open " << filename << std::endl;
			return false;
		}
		std::cout << "Loading STL  file " << filename << " ..." << std::endl;

		std::string lineBuffer;
		glm::vec3 normal;
		while (std::getline(fin, lineBuffer)) {
			if (lineBuffer.find("facet normal") != std::string::npos)
			{
				std::stringstream ss;
				ss << lineBuffer.substr(lineBuffer.find("facet normal") + 12);
				ss >> normal.x >> normal.y >> normal.z;
			}
			else if (lineBuffer.find("vertex") != std::string::npos) {
				std::stringstream ss;
				ss << lineBuffer.substr(lineBuffer.find("vertex") + 6);
				glm::vec3 vertex;
				ss >> vertex.x >> vertex.y >> vertex.z;
				Vertex meshVertex;
				meshVertex.position = vertex;
				meshVertex.normal = normal;
				box.x_min = std::min(box.x_min, vertex.x);
				box.y_min = std::min(box.y_min, vertex.y);
				box.z_min = std::min(box.z_min, vertex.z);
				box.x_max = std::max(box.x_max, vertex.x);
				box.y_max = std::max(box.y_max, vertex.y);
				box.z_max = std::max(box.z_max, vertex.z);
				mVertices.push_back(meshVertex);
			}
		}
		fin.close();
		
		initBuffers();
		initBuffersforBoundingBox();


		return (mLoaded = true);
	}
	return false;
}

void Mesh::drawModel()
{
	if (!mLoaded) return;
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0);
}


void Mesh::drawBoundingBox()
{
	if (!mLoaded) return;
	glBindVertexArray(bVAO);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

BoundingBox Mesh::getBoundingBox()
{
	return box;
}

void Mesh::initBuffersforBoundingBox()
{
	float vertices[] = {
	box.x_min, box.y_min, box.z_min,
	box.x_max, box.y_min, box.z_min,
	box.x_max, box.y_min, box.z_max,
	box.x_min, box.y_min, box.z_max,
	box.x_min, box.y_max, box.z_min,
	box.x_max, box.y_max, box.z_min,
	box.x_max, box.y_max, box.z_max,
	box.x_min, box.y_max, box.z_max
	};

	unsigned int indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	glGenVertexArrays(1, &bVAO);
	glBindVertexArray(bVAO);

	glGenBuffers(1, &bVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , vertices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &bIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void Mesh::initBuffers()
{
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}