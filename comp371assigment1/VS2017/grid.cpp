#include "grid.h"
#include "cube.h"
using namespace glm;
using namespace std;
Grid::Grid(vec3 color, int shaderProgram)
{
	world = mat4(1.0f);
	mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	//TODO:: get cube to work as a subclass
	Cube cube = Cube(vec3(1.0f, 1.0f, 0.0f));
	// Create a vertex array
	changes = mat4(1.0);

	glGenVertexArrays(1, &gridVAO);
	glBindVertexArray(gridVAO);

	float temp = sizeof(cube);
	vec3 vertexArray[] = {  // position,                            color
	vec3(-0.5f,-0.5f,-0.5f), color, //left - red
	vec3(-0.5f,-0.5f, 0.5f), color,
	vec3(-0.5f, 0.5f, 0.5f), color,

	vec3(-0.5f,-0.5f,-0.5f), color,
	vec3(-0.5f, 0.5f, 0.5f), color,
	vec3(-0.5f, 0.5f,-0.5f), color,

	vec3(0.5f, 0.5f,-0.5f), color, // far - blue
	vec3(-0.5f,-0.5f,-0.5f), color,
	vec3(-0.5f, 0.5f,-0.5f), color,

	vec3(0.5f, 0.5f,-0.5f), color,
	vec3(0.5f,-0.5f,-0.5f), color,
	vec3(-0.5f,-0.5f,-0.5f),color,

	vec3(0.5f,-0.5f, 0.5f), color, // bottom - turquoise
	vec3(-0.5f,-0.5f,-0.5f), color,
	vec3(0.5f,-0.5f,-0.5f),color,

	vec3(0.5f,-0.5f, 0.5f), color,
	vec3(-0.5f,-0.5f, 0.5f), color,
	vec3(-0.5f,-0.5f,-0.5f), color,

	vec3(-0.5f, 0.5f, 0.5f), color, // near - green
	vec3(-0.5f,-0.5f, 0.5f), color,
	vec3(0.5f,-0.5f, 0.5f), color,

	vec3(0.5f, 0.5f, 0.5f), color,
	vec3(-0.5f, 0.5f, 0.5f), color,
	vec3(0.5f,-0.5f, 0.5f), color,

	vec3(0.5f, 0.5f, 0.5f), color, // right - purple
	vec3(0.5f,-0.5f,-0.5f),color,
	vec3(0.5f, 0.5f,-0.5f), color,

	vec3(0.5f,-0.5f,-0.5f), color,
	vec3(0.5f, 0.5f, 0.5f), color,
	vec3(0.5f,-0.5f, 0.5f), color,

	vec3(0.5f, 0.5f, 0.5f),color, // top - yellow
	vec3(0.5f, 0.5f,-0.5f), color,
	vec3(-0.5f, 0.5f,-0.5f),color,

	vec3(0.5f, 0.5f, 0.5f), color,
	vec3(-0.5f, 0.5f,-0.5f), color,
	vec3(-0.5f, 0.5f, 0.5f), color
	};
	temp = sizeof(vertexArray);
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(vertexArray),
		&vertexArray,
		GL_STATIC_DRAW);

	glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(vec3),
		(void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glBindVertexArray(0);
}

void Grid::Draw()
{
	glBindVertexArray(gridVAO);

	for (float i = -50; i < 51; i++) {
		
		mat4 rotationMatrix = world * changes * translate(mat4(1.0f), vec3(i, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.01f, 0.01f, 100.0f));
		glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
		
	for (float i = -50; i < 51; i++) {
		mat4 rotationMatrix = world * changes * translate(mat4(1.0f), vec3(0.0f, 0.0f, i)) * scale(mat4(1.0f), vec3(100.0f, 0.01f, 0.01f));
		glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

void Grid::UpdateWorld(glm::mat4 stuff)
{
	world = stuff * world;
}

void Grid::Rotate(float angle, glm::vec3 orientation)
{

	changes = changes * rotate(mat4(1.0f), angle, orientation);
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &changes[0][0]);
}

void Grid::ResetWorld() {
	world = mat4(1.0f);
}