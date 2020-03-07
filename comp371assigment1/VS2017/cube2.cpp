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

	Vertex vertexArray[] = {  // position,                            color
		{   vec3(-0.5f,-0.5f,-0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(0.0f, 0.0f)}, //left - red
		{	vec3(-0.5f,-0.5f, 0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(0.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(1.0f, 1.0f)},

		{	vec3(-0.5f,-0.5f,-0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),  vec3(-1.0f, 0.0f,0.0f),	color,vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f,-0.5f),   vec3(0.0f, 0.0f,-1.0f),	color,vec2(1.0f, 1.0f)}, // far - blue
		{	vec3(-0.5f,-0.5f,-0.5f),  vec3(0.0f, 0.0f,-1.0f),	color,vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f,-1.0f),	color,vec2(0.0f, 1.0f)},

		{	vec3(0.5f, 0.5f,-0.5f),  vec3(0.0f, 0.0f,-1.0f),	color,vec2(1.0f, 1.0f)},
		{	vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f, 0.0f,-1.0f),	color,vec2(1.0f, 0.0f)},
		{	vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, 0.0f,-1.0f),	color,vec2(0.0f, 0.0f)},

		{	vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, -1.0f, 0.0f),	color,vec2(1.0f, 1.0f)}, // bottom - turquoise
		{	vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, -1.0f, 0.0f),	color,vec2(0.0f, 0.0f)},
		{	vec3(0.5f,-0.5f,-0.5f),  vec3(0.0f, -1.0f, 0.0f),	color,vec2(1.0f, 0.0f)},

		{	vec3(0.5f,-0.5f, 0.5f),  vec3(0.0f, -1.0f, 0.0f),	color,vec2(1.0f, 1.0f)},
		{	vec3(-0.5f,-0.5f, 0.5f), vec3(0.0f, -1.0f, 0.0f),	color,vec2(0.0f, 1.0f)},
		{	vec3(-0.5f,-0.5f,-0.5f), vec3(0.0f, -1.0f, 0.0f),	color,vec2(0.0f, 0.0f)},

		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f),	color,vec2(0.0f, 1.0f)}, // near - green
		{	vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f),	color,vec2(0.0f, 0.0f)},
		{	vec3(0.5f,-0.5f, 0.5f),  vec3(0.5f,-0.5f, 0.5f),	color,vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),  vec3(0.5f, 0.5f, 0.5f),	color,vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f),	color,vec2(0.0f, 1.0f)},
		{	vec3(0.5f,-0.5f, 0.5f),  vec3(0.5f,-0.5f, 0.5f),	color,vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f),		color,vec2(1.0f, 1.0f)}, // right - purple
		{	vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f),		color,vec2(0.0f, 0.0f)},
		{	vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f),		color,vec2(1.0f, 0.0f)},

		{	vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f),		color,vec2(0.0f, 0.0f)},
		{	vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f),		color,vec2(1.0f, 1.0f)},
		{	vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f),		color,vec2(0.0f, 1.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),	vec3(0.5f, 0.5f, 0.5f),		color,vec2(1.0f, 1.0f)}, // top - yellow
		{	vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f),		color,vec2(1.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),vec3(-0.5f, 0.5f,-0.5f),	color,vec2(0.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),	 vec3(0.5f, 0.5f, 0.5f), color, vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f), color,vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),	vec3(-0.5f, 0.5f, 0.5f), color,vec2(0.0f, 1.0f)}
	};
	numOfVertices = sizeof(vertexArray) / sizeof(Vertex);
		glGenVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);
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

void Cube2::Draw()
{
	glBindVertexArray(cubeVAO);
	mat4 temp = world * centerSource * changes;
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &temp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
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

