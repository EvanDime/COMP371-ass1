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

	Vertex vertexArray[] = {  // position,                            color
		{vec3(-0.5f,-0.5f,-0.5f),vec3(-0.5f,-0.5f,-0.5f), color}, //left - red
		{	vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), color},
		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), color},

		{	vec3(-0.5f,-0.5f,-0.5f),  vec3(-0.5f,-0.5f,-0.5f), color},
		{	vec3(-0.5f, 0.5f, 0.5f),  vec3(-0.5f, 0.5f, 0.5f), color},
		{	vec3(-0.5f, 0.5f,-0.5f),  vec3(-0.5f, 0.5f,-0.5f), color},

		{	vec3(0.5f, 0.5f,-0.5f),  vec3(0.5f, 0.5f,-0.5f), color}, // far - blue
		{	vec3(-0.5f,-0.5f,-0.5f),  vec3(-0.5f,-0.5f,-0.5f), color},
		{	vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f), color},

		{	vec3(0.5f, 0.5f,-0.5f),  vec3(0.5f, 0.5f,-0.5f), color},
		{	vec3(0.5f,-0.5f,-0.5f),  vec3(0.5f,-0.5f,-0.5f), color},
		{	vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), color},

		{	vec3(0.5f,-0.5f, 0.5f),  vec3(0.5f,-0.5f, 0.5f), color}, // bottom - turquoise
		{	vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), color},
		{	vec3(0.5f,-0.5f,-0.5f),vec3(0.5f,-0.5f,-0.5f), color},

		{	vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), color},
		{	vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), color},
		{	vec3(-0.5f,-0.5f,-0.5f),vec3(-0.5f,-0.5f,-0.5f), color},

		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), color}, // near - green
		{	vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), color},
		{	vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), color},

		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), color},
		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), color},
		{	vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), color},

		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), color}, // right - purple
		{	vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f), color},
		{	vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f), color},

		{	vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f), color},
		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), color},
		{	vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), color},

		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), color}, // top - yellow
		{	vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f), color},
		{	vec3(-0.5f, 0.5f,-0.5f),vec3(-0.5f, 0.5f,-0.5f), color},

		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), color},
		{	vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f), color},
		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), color}
	};

	glGenVertexArrays(1, &gridVAO);
	glBindVertexArray(gridVAO);
	GLuint mVBO;

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	// 1st attribute buffer : vertex Positions
	glVertexAttribPointer(0,              // attribute. No particular reason for 0, but must match the layout in the shader.
		3,              // size
		GL_FLOAT,       // type
		GL_FALSE,       // normalized?
		sizeof(Vertex), // stride
		(void*)0        // array buffer offset
	);
	glEnableVertexAttribArray(0);

	// 3rd attribute buffer : vertex color
	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(2 * sizeof(vec3))   // Normal is Offseted by vec3 (see class Vertex)
	);
	glEnableVertexAttribArray(1);


	//2nd attribute buffer : vertex normal
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(vec3)// Color is Offseted by 2 vec3 (see class Vertex)
	);
	glEnableVertexAttribArray(2);

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