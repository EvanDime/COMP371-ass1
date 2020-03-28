#include"cube.h"


using namespace glm;
using namespace std;

Cube::Cube(glm::vec3 color) : gColor(color)
{
}


vec3* Cube::GetVertices()
{
	
	vec3 vertexArray[] = {  // position,                            color
	vec3(-0.5f,-0.5f,-0.5f), gColor, //left - red
	vec3(-0.5f,-0.5f, 0.5f), gColor,
	vec3(-0.5f, 0.5f, 0.5f), gColor,

	vec3(-0.5f,-0.5f,-0.5f), gColor,
	vec3(-0.5f, 0.5f, 0.5f), gColor,
	vec3(-0.5f, 0.5f,-0.5f), gColor,

	vec3(0.5f, 0.5f,-0.5f), gColor, // far - blue
	vec3(-0.5f,-0.5f,-0.5f), gColor,
	vec3(-0.5f, 0.5f,-0.5f), gColor,

	vec3(0.5f, 0.5f,-0.5f), gColor,
	vec3(0.5f,-0.5f,-0.5f), gColor,
	vec3(-0.5f,-0.5f,-0.5f),gColor,

	vec3(0.5f,-0.5f, 0.5f), gColor, // bottom - turquoise
	vec3(-0.5f,-0.5f,-0.5f), gColor,
	vec3(0.5f,-0.5f,-0.5f),gColor,

	vec3(0.5f,-0.5f, 0.5f), gColor,
	vec3(-0.5f,-0.5f, 0.5f), gColor,
	vec3(-0.5f,-0.5f,-0.5f), gColor,

	vec3(-0.5f, 0.5f, 0.5f), gColor, // near - green
	vec3(-0.5f,-0.5f, 0.5f), gColor,
	vec3(0.5f,-0.5f, 0.5f), gColor,

	vec3(0.5f, 0.5f, 0.5f), gColor,
	vec3(-0.5f, 0.5f, 0.5f), gColor,
	vec3(0.5f,-0.5f, 0.5f), gColor,

	vec3(0.5f, 0.5f, 0.5f), gColor, // right - purple
	vec3(0.5f,-0.5f,-0.5f),gColor,
	vec3(0.5f, 0.5f,-0.5f), gColor,

	vec3(0.5f,-0.5f,-0.5f), gColor,
	vec3(0.5f, 0.5f, 0.5f), gColor,
	vec3(0.5f,-0.5f, 0.5f), gColor,

	vec3(0.5f, 0.5f, 0.5f),gColor, // top - yellow
	vec3(0.5f, 0.5f,-0.5f), gColor,
	vec3(-0.5f, 0.5f,-0.5f),gColor,

	vec3(0.5f, 0.5f, 0.5f), gColor,
	vec3(-0.5f, 0.5f,-0.5f), gColor,
	vec3(-0.5f, 0.5f, 0.5f), gColor
	};
	vertices = vertexArray;
	return vertices;
}
