#include"cube2.h"


using namespace glm;
using namespace std;

Cube2::Cube2(glm::vec3 color, glm::mat4 change, int shaderProgram) 
	{
	originalBuild = change;
	changes = change;
	mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	centerSource = mat4(1.0f);
	world = mat4(1.0f);

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

		// Create a vertex array
		glGenVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);


		GLuint vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

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

void Cube2::Draw()
{
	glBindVertexArray(cubeVAO);
	mat4 temp = world * centerSource * changes;
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &temp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube2::Update(glm::mat4 newStuff)
{
	changes = newStuff * changes;
}

void Cube2::UpdateParent(glm::mat4 newStuff)
{
	centerSource = newStuff * centerSource;
}

void Cube2::UpdateWorld(glm::mat4 newStuff)
{
	world = newStuff * world;
}

void Cube2::ResetWorld()
{
	world = mat4(1.0f);
}

void Cube2::RotateParent(float angle, glm::vec3 orientation)
{
	centerSource = centerSource *  rotate(mat4(1.0), angle, orientation) ;
}

void Cube2::Scale(glm::vec3 scalee) {
	changes = changes * scale(mat4(1.0f), scalee);
}

void Cube2::ScaleParent(glm::vec3 scalee) {
	centerSource = centerSource * scale(mat4(1.0f), scalee);
}

void Cube2::Rotate(float angle, glm::vec3 orientation)
{

	changes = changes * rotate(mat4(1.0f), angle, orientation);
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &changes[0][0]);
}

void Cube2::Translate(glm::vec3 movement) {
	changes = changes * translate(glm::mat4(1.0f), movement);
}
void Cube2::TranslateParent(glm::vec3 movement) {
	centerSource = centerSource * translate(glm::mat4(1.0f), movement);
}

void Cube2::Nuke(glm::mat4 updated)
{
	centerSource = updated;
}
