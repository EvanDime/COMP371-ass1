#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;  // You will need this when you do lighting
layout(location = 2) in vec3 vertexColor; 

// Values that stay constant for the whole mesh.
uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
// Outputs to fragment shader
out vec3 normal;  // You will need this when you do per-fragment lighting
out vec4 v_color;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = viewMatrix * projectionMatrix * worldMatrix * vec4(vertexPosition_modelspace,1);

	normal = vertexNormal_modelspace; // Does this need to be transformed when we pass it to the fragment shader?
	v_color = vec4(vertexColor, 1.0f);
}

