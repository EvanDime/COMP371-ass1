#ifndef __OLAF__H_
#define __OLAF__H_
#include <iostream>
#include <list>
#include "cube2.h"
#include "sphere.h"

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
	Olaf(int, int);
	void Draw(GLuint = NULL, GLuint = NULL);
	void Update(glm::mat4);
	GLuint  olafVAO;
	void Rotate(float, glm::vec3);
	void Translate(glm::vec3);
	void Scale(glm::vec3);
	void Nuke();
	void UpdateWorld(glm::mat4);
	void ResetWorld();
	void AnimateWalk(float, bool = false);
	void AnimateWink(float, bool = false);
	void AnimateBlink(float);
	bool isAnimating();
	bool startWalking(bool);
	Cube2 armL;
	Cube2 armR;
	bool animating;
	Cube2 eyeL;
	Cube2 eyeR;
private:
	GLuint mWorldMatrixLocation;
	glm::mat4 changes;
	glm::mat4 original;
	glm::mat4 world;
	Sphere head;
	Cube2 scarf;
	Cube2 scarf2;
	Cube2 mask;
	Cube2 nose;
	Cube2 shoe1;
	Cube2 shoe2;
	Cube2 hat;
	Cube2 hat2;
	Cube2 footR;
	Cube2 footL;
	Sphere chest;
	Cube2 button1;
	Cube2 button2;
	Cube2 button3;
	unsigned int numOfVertices;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
};

#endif