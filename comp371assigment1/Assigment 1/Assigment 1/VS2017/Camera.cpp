


#include <../../VS2017/camera.h>


using namespace glm;
using namespace std;

Camera::Camera( int shaderProgram) 
{

	// Camera parameters for view transform
	vec3 cameraPosition1(0.0f, 10.0f, 35.0f);
	vec3 cameraLookAt1(0.0f, -1.0f, -1.0f);
	vec3 cameraUp1(0.0f, 1.0f, 0.0f);
	cameraPosition = cameraPosition1;
	cameraLookAt = cameraLookAt1;
	cameraUp = cameraUp1;
	// Other camera parameters
	bool  cameraFirstPerson = true; // press 1 or 2 to toggle this variable

	// Spinning cube at camera position
	float spinningCubeAngle = 0.0f;

	// Set projection matrix for shader, this won't change 1024x768
	mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
		1024.0f / 768.0f,  // aspect ratio
		0.01f, 250.0f);   // near and far (near > 0)

	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Set initial view matrix
	state = lookAt(cameraPosition,  // eye
		cameraPosition + cameraLookAt,  // center
		cameraUp); // up

	 mCameraLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(mCameraLocation, 1, GL_FALSE, &state[0][0]);

}

void Camera::Update()
{
	state = lookAt(cameraPosition,  // eye
		cameraPosition + cameraLookAt,  // center
		cameraUp); // up
	glUniformMatrix4fv(mCameraLocation, 1, GL_FALSE, &state[0][0]);
}




