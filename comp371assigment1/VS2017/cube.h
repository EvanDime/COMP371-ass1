#ifndef __CUBE__H_
#define __CUBE__H_
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
class Cube
{
public:
	Cube(glm::vec3);
	glm::vec3 GetColor();
	glm::vec3* GetVertices();
protected:
	glm::vec3 gColor;
	glm::vec3* vertices;
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 uv;
	};
};

#endif