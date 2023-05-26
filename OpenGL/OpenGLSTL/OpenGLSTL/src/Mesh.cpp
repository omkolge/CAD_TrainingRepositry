#include "Mesh.h"
#include<iostream>
#include<sstream>
#include<fstream>

Mesh::Mesh() :mLoaded(false)
{
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}


bool Mesh::loadSTL(const std::string& filename)
{
	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector <glm::vec3> tempNormals;
	std::vector <glm::vec3> tempVertices;

	if (filename.find(".stl") != std::string::npos || filename.find(".STL") != std::string::npos) {
		std::ifstream fin(filename, std::ios::in);
		if (!fin) {
			std::cerr << "Cannot open " << filename << std::endl;
			return false;
		}
		std::cout << "Loading STL file " << filename << " ..." << std::endl;

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
				mVertices.push_back(meshVertex);
			}
		}
		fin.close();

		initBuffers();

		return (mLoaded = true);
	}
	return false;
}
void Mesh::draw()
{
	if (!mLoaded)
		return;
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0); //basically we are doing unbinding in this line
}

void Mesh::initBuffers()
{
	glGenBuffers(1, &mVBO);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);		// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);// copy the data from CPU to GPU "GL_STATIC_DRAW" "GL_DYNAMIC_DRAW" GL_STREAM_DRAW

	// The vertex array object (VAO) is a little descriptor that defines which data from vertex buffer objects should be used as input 
	// variables to vertex shaders. in our case - use our only VBO, and say 'every three floats is a variable'
	// Modern OGL requires that we use a vertex array object
	glGenVertexArrays(1, &mVAO);				// Tell OpenGL to create new Vertex Array Object
	glBindVertexArray(mVAO);					// Make it the current one


	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glEnableVertexAttribArray(0);	// Enable the first attribute or attribute "0"

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	//texcoords
	/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);*/
	glBindVertexArray(0);
}
