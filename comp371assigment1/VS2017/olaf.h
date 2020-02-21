#ifndef __OLAF__H_
#define __OLAF__H_
#include <iostream>
#include <list>
#include "cube2.h"

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
class Olaf
{
public:
	Olaf(int);
	void Draw();
	void Update(glm::mat4);
	GLuint  olafVAO;
	void Rotate(float, glm::vec3);
	void Translate(glm::vec3);
	void Scale(glm::vec3);
	void Nuke();
	void UpdateWorld(glm::mat4);
	void ResetWorld();
	Cube2 armL;
	Cube2 armR;
private:
	GLuint mWorldMatrixLocation;
	glm::mat4 changes;
	glm::mat4 world;
	Cube2 head;
	Cube2 scarf;
	Cube2 scarf2;
	Cube2 mask;
	Cube2 eyeL;
	Cube2 eyeR;
	Cube2 nose;
	Cube2 shoe1;
	Cube2 shoe2;
	Cube2 hat;
	Cube2 hat2;
	Cube2 footR;
	Cube2 footL;
	Cube2 chest;
	Cube2 button1;
	Cube2 button2;
	Cube2 button3;
};

#endif