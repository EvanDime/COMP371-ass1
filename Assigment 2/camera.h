#ifndef __CAMERA__H_
#define __CAMERA__H_
#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
class Camera
{
public:
	Camera(int);
	void Update();
	glm::vec3 cameraPosition;
	glm::vec3 cameraLookAt;
	glm::vec3 cameraUp;

private:
	GLuint mCameraLocation;
	glm::mat4 state;

};

#endif