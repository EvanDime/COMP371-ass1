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
#include <../../VS2017/camera.h>
#include <../../VS2017/grid.h>
#include <../../VS2017/olaf.h>





using namespace glm;
using namespace std;

void cameraThings();
const char* getVertexShaderSource()
{
	// For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;"
		"layout (location = 1) in vec3 aColor;"
		""
		"uniform mat4 worldMatrix;"
		"uniform mat4 viewMatrix = mat4(1.0);"  // default value for view matrix (identity)
		"uniform mat4 projectionMatrix = mat4(1.0);"
		""
		"out vec3 vertexColor;"
		"void main()"
		"{"
		"   vertexColor = aColor;"
		"   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
		"   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
		"}";
}


const char* getFragmentShaderSource()
{
	return
		"#version 330 core\n"
		"in vec3 vertexColor;"
		"out vec4 FragColor;"
		"void main()"
		"{"
		"   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);"
		"}";
}


int compileAndLinkShaders()
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------


	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = getVertexShaderSource();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = getFragmentShaderSource();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int main(int argc, char* argv[])
{
	// Initialize GLFW and OpenGL version
	glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

	// Create Window and rendering context using GLFW, resolution is  1024x768
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Assigment 01 - Evan Dimopoulos", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to create GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Compile and link shaders here ...
	int shaderProgram = compileAndLinkShaders();
	glUseProgram(shaderProgram);

	///////////////camera

	Camera camera = Camera(shaderProgram);
	// For frame time
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	int lastMouseRightState = GLFW_RELEASE;
	int lastMouseMiddleState = GLFW_RELEASE;

	double lastMousePosX, lastMousePosY;
	
	float cameraHorizontalAngle = 90.0f;
	float cameraVerticalAngle = 0.0f;

	/////////////////////////
	glEnable(GL_DEPTH_TEST);
	GLuint mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	bool clickCheck = false;

	// Define and upload geometry to the GPU here ...
	Cube2 axisX = Cube2(vec3(1.0f, 0.0f, 0.0f), translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f)), shaderProgram);
	Cube2 axisY = Cube2(vec3(0.0f, 1.0f, 0.0f), translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.03f, 5.0f)), shaderProgram);
	Cube2 axisZ = Cube2(vec3(0.0f, 0.0f, 1.0f), translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f)), shaderProgram);
	Grid grid = Grid(vec3(1.0f, 1.0f, 0.0f), shaderProgram);
	Olaf olaf = Olaf(shaderProgram);
	Olaf olaf2 = Olaf(shaderProgram);
	olaf2.Translate(vec3(6.0f, 0.0f, 0.0f));

	//Other
	glEnable(GL_CULL_FACE);

	// Entering Main Loop
	while (!glfwWindowShouldClose(window))
	{

		bool shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
				// frame time calculation
		float dt = glfwGetTime() - lastFrameTime;
		lastFrameTime += dt;


		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		axisX.Draw();
		axisY.Draw();
		axisZ.Draw();
		grid.Draw();
		olaf.Draw();
		olaf2.Draw();
		
		//////

		///key input
		//SHIFT + A
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && shift) // move camera to the left
		{
			olaf.Translate(vec3(0.01, 0.0, 0.0));
		}
		//SHIFT + S
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && shift) // move camera to the left
		{
			olaf.Translate(vec3(0.0, 0.0, -0.01));
		}
		//SHIFT + D
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && shift) 
		{
			olaf.Translate(vec3(-0.01, 0.0, 0.0));
		}
		//SHIFT + W
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && shift) 
		{
			olaf.Translate(vec3(0.0, 0.0, 0.01));
		}
		//A
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !shift) 
		{
			olaf.Rotate(radians(0.1f), vec3(0.0f, 1.0f, 0.0f));
		}
		// S
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !shift) 
		{
			olaf.Rotate(radians(0.1f), vec3(0.0, 0.0, 1.0));
		}
		//D
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !shift)
		{
			olaf.Rotate(radians(-0.1f), vec3(0.0, 1.0, 0.0));
		}
		// W
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !shift)
		{
			olaf.Rotate(radians(-0.1f), vec3(0.0, 0.0, 1.0));
		}
		//P
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !shift)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);		
		}
		//L
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !shift)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		//T
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !shift)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
		}

		//SPACE
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !shift)
		{
			olaf.Nuke();
		}
		//U
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && !shift)
		{
			olaf.Scale(vec3(1.01f, 1.01f, 1.01f));
		}
		//J
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && !shift)
		{
			olaf.Scale(vec3(0.99f, 0.99f, 0.99f));
		}
		//left arrrow
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));
		}
		//up arrrow
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
		}
		//down arrrow
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
		}
		//right arrrow
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
		}
		//SHIFT + backspace
		if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && shift)
		{
			cameraHorizontalAngle = 90.0f;
			cameraVerticalAngle = 0.0f;
			vec3 cameraPosition1(0.0f, 10.0f, 35.0f);
			vec3 cameraLookAt1(0.0f, 0.0f, -1.0f);
			vec3 cameraUp1(0.0f, 1.0f, 0.0f);
			camera.cameraPosition = cameraPosition1;
			camera.cameraLookAt = cameraLookAt1;
			camera.cameraUp = cameraUp1;
			olaf.ResetWorld();
			grid.ResetWorld();
			axisX.ResetWorld();
			axisY.ResetWorld();
			axisZ.ResetWorld();
		}

		lastMouseLeftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		lastMouseRightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		lastMouseMiddleState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);

		if (!clickCheck && (lastMouseLeftState == GLFW_PRESS || lastMouseRightState == GLFW_PRESS || lastMouseMiddleState == GLFW_PRESS  )) {
			clickCheck = true;
			glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
		}
		if ((lastMouseLeftState == GLFW_RELEASE & lastMouseRightState == GLFW_RELEASE && lastMouseMiddleState == GLFW_RELEASE) && clickCheck) {
			clickCheck = false;
		}
		if (clickCheck) {

			double mousePosX, mousePosY;
			glfwGetCursorPos(window, &mousePosX, &mousePosY);


			float dx = mousePosX - lastMousePosX;
			float dy = mousePosY - lastMousePosY;

			lastMousePosX = mousePosX;
			lastMousePosY = mousePosY;
			float theta = radians(cameraHorizontalAngle);
			float phi = radians(cameraVerticalAngle);
			vec3 cameraSideVector = glm::cross(camera.cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

			if (lastMouseLeftState == GLFW_PRESS) {
				camera.cameraPosition -= camera.cameraLookAt * dy * 0.1f;
			}

			if (lastMouseRightState == GLFW_PRESS) {
				camera.cameraPosition += cameraSideVector * dx * 0.1f;
			}

			if (lastMouseMiddleState == GLFW_PRESS) {
				// Convert to spherical coordinates
				const float cameraAngularSpeed = 60.0f;
				cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
				cameraVerticalAngle -= dy * cameraAngularSpeed * dt;
				cameraVerticalAngle = max(-85.0f, min(85.0f, cameraVerticalAngle));
				if (cameraHorizontalAngle > 360)
				{
					cameraHorizontalAngle -= 360;
				}
				else if (cameraHorizontalAngle < -360)
				{
					cameraHorizontalAngle += 360;
				}
			}
		}

		float theta = radians(cameraHorizontalAngle);
		float phi = radians(cameraVerticalAngle);

		camera.cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
		vec3 cameraSideVector = glm::cross(camera.cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

		glm::normalize(cameraSideVector);
		///update camera
		camera.Update();
		////
		// End frame
		glfwSwapBuffers(window);

		// Detect inputs
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}


