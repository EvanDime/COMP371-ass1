#ifndef __GRID__H_
#define __GRID__H_
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <../../VS2017/cube2.h>

class Grid
{
public:
	Grid(glm::vec3, int);
	void Draw();
	void Update(glm::mat4);
	void UpdateWorld(glm::mat4);
	void Rotate(float, glm::vec3);
	void ResetWorld();
private:
	GLuint  gridVAO;
	int mWorldMatrixLocation;
	glm::mat4 changes;
	glm::mat4 world;
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};

#endif