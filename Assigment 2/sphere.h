#ifndef __SPHERE_H_
#define __SPHERE_H_
#include <iostream>
#include <list>
#include "sphere.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
class Sphere 
{
public:
	Sphere(glm::vec3, glm::mat4, int);
	Sphere(glm::vec3, glm::mat4,glm::mat4, int);
	void Draw();
	void Update(glm::mat4);
	void UpdateParent(glm::mat4);
	void UpdateWorld(glm::mat4);
	void ResetWorld();
	void RotateParent(float, glm::vec3);
	void Rotate(float, glm::vec3);
	void Translate(glm::vec3);
	void TranslateParent(glm::vec3);
	void Nuke(glm::mat4);
	void Scale(glm::vec3);
	void ScaleParent(glm::vec3);
	GLuint  sphereVAO;
protected:
	GLuint mWorldMatrixLocation;
	glm::mat4 changes;
	glm::mat4 centerSource;
	glm::mat4 originalBuild;
	glm::mat4 world;
	unsigned int numOfVertices;
	int shader;
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};
#endif