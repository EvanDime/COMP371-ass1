#include <iostream>
#include <list>
#include <string>
#include <fstream>

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
#include <../../VS2017/Shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <../../VS2017/stb_image.h>



using namespace glm;
using namespace std;


//Reads a file
std::string readFile(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


std::string getVertexShaderSource(char *source)
{	return readFile(source);
}


std::string getFragmentShaderSource(char* source)
{
	return readFile(source);
}


GLuint loadTexture(const char* filename)
{
	// Step1 Create and bind textures
	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	assert(textureId != 0);


	glBindTexture(GL_TEXTURE_2D, textureId);

	// Step2 Set filter parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Step3 Load Textures with dimension data
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
		return 0;
	}

	// Step4 Upload the texture to the PU
	GLenum format = 0;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
		0, format, GL_UNSIGNED_BYTE, data);

	// Step5 Free resources
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureId;
}

int compileAndLinkShaders()
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderStr = getVertexShaderSource("vertex.glsl");
	const char* vertexShaderSource = vertShaderStr.c_str();
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
	std::string fragShaderStr = getFragmentShaderSource("fragment.glsl");
	const char* fragmentShaderSource = fragShaderStr.c_str();
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

int compileAndLinkShaders2()
{
	// compile and link shader program
	// return shader program id
	// ------------------------------------

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderStr = getVertexShaderSource("sphereVertex.glsl");
	const char* vertexShaderSource = vertShaderStr.c_str();
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
	std::string fragShaderStr = getFragmentShaderSource("sphereFragment.glsl");
	const char* fragmentShaderSource = fragShaderStr.c_str();
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

	//Textures
	//GLuint brickTextureID = loadTexture("Textures/brick.jpg");
	//GLuint cementTextureID = loadTexture("Textures/cement.jpg");

	// Create Window and rendering context using GLFW, resolution is  1024x768
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Assigment 02 - Evan Dimopoulos", NULL, NULL);
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
	//for animations
	float time = 0;
	float winkTime = 0;
	bool walking = false;
	bool winking = false;
	bool blinking = false;
	bool direction = false;
	bool eye = false;

	// putple-ish background
	glClearColor(0.1f, 0.0f, 0.2f, 1.0f);

	// Compile and link shaders here ...
	int shaderProgram = compileAndLinkShaders();
	int shaderProgram2 = compileAndLinkShaders2();
	glUseProgram(shaderProgram);

	///////////////camera setup

	Camera camera = Camera(shaderProgram2);
	// For frame time
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	int lastXstate = GLFW_RELEASE;
	int lastMouseRightState = GLFW_RELEASE;
	int lastMouseMiddleState = GLFW_RELEASE;

	double lastMousePosX, lastMousePosY;
	
	float cameraHorizontalAngle = 90.0f;
	float cameraVerticalAngle = 0.0f;

	/////////////////////////
	glEnable(GL_DEPTH_TEST);
	GLuint mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	bool clickCheck = false;
	bool swapFloor = false;
	GLuint snowTextureID = loadTexture("../Assets/snow.jpg");

	// Define and upload geometry to the GPU here ...
	Cube2 axisX = Cube2(vec3(1.0f, 0.0f, 0.0f), translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f)), shaderProgram);
	Cube2 axisZ = Cube2(vec3(0.0f, 1.0f, 0.0f), translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f)), shaderProgram);
	Cube2 axisY = Cube2(vec3(0.0f, 0.0f, 1.0f), translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f)), shaderProgram);
	Grid grid = Grid(vec3(1.0f, 1.0f, 0.0f), shaderProgram);
	Cube2 floor = Cube2(vec3(0.8f, 0.8f, 0.8f), translate(mat4(1.0f), vec3(0.0f, -0.08f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.01f, 100.0f)), shaderProgram);
	Olaf olaf = Olaf(shaderProgram,shaderProgram);
	//Other
	glEnable(GL_CULL_FACE);
	// Entering Main Loop
	glActiveTexture(GL_TEXTURE0);
	GLuint textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");
	glBindTexture(GL_TEXTURE_2D, snowTextureID);
	glUniform1i(textureLocation, 0);
 	while (!glfwWindowShouldClose(window))
	{

		bool shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
				// frame time calculation
		float dt = glfwGetTime() - lastFrameTime;

		lastFrameTime += dt;

		// Each frame, reset color of each pixel to glClearColor
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw the main objects
		axisX.Draw();
		axisY.Draw();
		axisZ.Draw();
		if(swapFloor)
			grid.Draw();
		else 
			floor.Draw();
		olaf.Draw();
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
			olaf.AnimateWalk(dt, true);
			olaf.Translate(vec3(0.0, 0.0, -0.001));
			if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
			{
				olaf.Rotate(radians(0.05f), vec3(0.0f, 1.0f, 0.0f));

			}
			if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			{
				olaf.Rotate(radians(-0.05f), vec3(0.0f, 1.0f, 0.0f));
			}
		}
		//SHIFT + D
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && shift) 
		{
			olaf.Translate(vec3(-0.01, 0.0, 0.0));
		}
		//SHIFT + W
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && shift) 
		{
			olaf.AnimateWalk(dt, false);
			olaf.Translate(vec3(0.0, 0.0, 0.001));
			if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
			{
				olaf.Rotate(radians(0.05f), vec3(0.0f, 1.0f, 0.0f));

			}
			if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			{
				olaf.Rotate(radians(-0.05f), vec3(0.0f, 1.0f, 0.0f));
			}
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
		
		if (lastXstate == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			swapFloor = !swapFloor;
		}
		lastXstate = glfwGetKey(window, GLFW_KEY_X);


		if (walking) {
			olaf.AnimateWalk(dt , direction);
			time = time + dt * 400;
			if(direction)
				olaf.Translate(vec3(0.0, 0.0, -0.001));
			else
				olaf.Translate(vec3(0.0, 0.0, 0.001));

			if (time > 360)
				walking = false;
		}

		if (winking) {
			olaf.AnimateWink(dt, eye);
			winkTime = winkTime + dt * 400;
			if (winkTime > 180)
				winking = false;
		}

		if (blinking)
		{
			olaf.AnimateBlink(dt);
			winkTime = winkTime + dt * 400;
			if (winkTime > 180)
				blinking = false;
		}
		//C
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && shift && !winking && !blinking)
		{
			//olaf.eyeL.Scale(vec3(1.00f, 1.01f, 1.00f));
			winking = true;
			eye = true;
			winkTime = 0;
		}

		//SHIFT + C
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !shift && !winking && !blinking)
		{
			winking = true;
			eye = false;
			winkTime = 0;
		}

		//B
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !shift && !blinking && !winking)
		{
			blinking = true;
			winkTime = 0;
		}

		//Z
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && shift && !walking)
		{

			walking = true;
			direction = true;
			time = 0;
		}

		//SHIFT + Z
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS  && !shift && !walking)
		{

			walking = true;
			direction = false;
			time = 0;
		}

		//SPACE
		//I know the function can be called relocate or something, but i decided on Nuke
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
			floor.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(1.0f, 0.0f, 0.0f)));

		}
		//up arrrow
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
			floor.UpdateWorld(rotate(mat4(1.0f), radians(0.01f), vec3(0.0f, 1.0f, 0.0f)));
		}
		//down arrrow
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
			floor.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(0.0f, 1.0f, 0.0f)));
		}
		//right arrrow
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !shift)
		{
			olaf.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			grid.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisX.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisY.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			axisZ.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
			floor.UpdateWorld(rotate(mat4(1.0f), radians(-0.01f), vec3(1.0f, 0.0f, 0.0f)));
		}
		//SHIFT + backspace , my laptop does not have a home button so i used shift backspace)
		if ((glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && shift) || (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS))
		{
			cameraHorizontalAngle = 90.0f;
			cameraVerticalAngle = 0.0f;
			vec3 cameraPosition1(0.0f, 10.0f, 35.0f);
			vec3 cameraLookAt1(0.0f, 0.0f, -1.0f);
			vec3 cameraUp1(0.0f, 1.0f, 0.0f);
			camera.cameraPosition = cameraPosition1;
			camera.cameraLookAt = cameraLookAt1;
			camera.cameraUp = cameraUp1;
			//reset the changes done to the world (world here mean everything but the camera)
			olaf.ResetWorld();
			grid.ResetWorld();
			axisX.ResetWorld();
			axisY.ResetWorld();
			axisZ.ResetWorld();
		}

		//Get states for the mouse click events
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

			//See if we need to zoom in/out
			if (lastMouseLeftState == GLFW_PRESS) {
				camera.cameraPosition -= camera.cameraLookAt * dy * 0.1f;
			}

			//see if we need to pan left/right
			if (lastMouseRightState == GLFW_PRESS) {
				camera.cameraPosition += cameraSideVector * dx * 0.1f;
			}

			//see if we need to rotate the camera
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


