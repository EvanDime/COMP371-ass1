#include"cube2.h"


using namespace glm;
using namespace std;

Cube2::Cube2(glm::vec3 color, glm::mat4 change, int shaderProgram, GLuint texture, int anim) 
	{
	originalBuild = change;
	changes = change;
	mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	centerSource = mat4(1.0f);
	world = mat4(1.0f);
	animationMatrix = mat4(1.0f);
	animateType = anim;
	animating = false;
	frame = 0;
	if (texture != NULL) {
		textureLocation = glGetUniformLocation(shaderProgram, "textureSampler");
	}
	Vertex vertexArray[] = {  // position,                            color
		{   vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)}, //left - red
		{	vec3(-0.5f,-0.5f, 0.5f),	color,	vec2(0.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),	color,	vec2(1.0f, 1.0f)},

		{	vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),	color,	vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),	color,	vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f,-0.5f),		color,	vec2(1.0f, 1.0f)}, // far - blue
		{	vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),	color,	vec2(0.0f, 1.0f)},

		{	vec3(0.5f, 0.5f,-0.5f),		color,	vec2(1.0f, 1.0f)},
		{	vec3(0.5f,-0.5f,-0.5f),		color,	vec2(1.0f, 0.0f)},
		{	vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},

		{	vec3(0.5f,-0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)}, // bottom - turquoise
		{	vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},
		{	vec3(0.5f,-0.5f,-0.5f),		color,	vec2(1.0f, 0.0f)},

		{	vec3(0.5f,-0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)},
		{	vec3(-0.5f,-0.5f, 0.5f),	color,	vec2(0.0f, 1.0f)},
		{	vec3(-0.5f,-0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},

		{	vec3(-0.5f, 0.5f, 0.5f),	color,	vec2(0.0f, 1.0f)}, // near - green
		{	vec3(-0.5f,-0.5f, 0.5f),	color,	vec2(0.0f, 0.0f)},
		{	vec3(0.5f,-0.5f, 0.5f),		color,	vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),	color,	vec2(0.0f, 1.0f)},
		{	vec3(0.5f,-0.5f, 0.5f),		color,	vec2(1.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)}, // right - purple
		{	vec3(0.5f,-0.5f,-0.5f),		color,	vec2(0.0f, 0.0f)},
		{	vec3(0.5f, 0.5f,-0.5f),		color,	vec2(1.0f, 0.0f)},

		{	vec3(0.5f,-0.5f,-0.5f),		color,	vec2(0.0f, 0.0f)},
		{	vec3(0.5f, 0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)},
		{	vec3(0.5f,-0.5f, 0.5f),		color,	vec2(0.0f, 1.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)}, // top - yellow
		{	vec3(0.5f, 0.5f,-0.5f),		color,	vec2(1.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},

		{	vec3(0.5f, 0.5f, 0.5f),		color,	vec2(1.0f, 1.0f)},
		{	vec3(-0.5f, 0.5f,-0.5f),	color,	vec2(0.0f, 0.0f)},
		{	vec3(-0.5f, 0.5f, 0.5f),	color,	vec2(0.0f, 1.0f)}
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
			(void*)( sizeof(vec3))   // Normal is Offseted by vec3 (see class Vertex)
		);
		glEnableVertexAttribArray(2);



		// 4thd attribute buffer : texture 
		glVertexAttribPointer(3,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(2 * sizeof(vec3))
		);
		glEnableVertexAttribArray(3);

		if (texture != NULL) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

		}

	}

void Cube2::Draw(GLuint texture)
{
	glBindVertexArray(cubeVAO);
	mat4 temp = world * centerSource * animationMatrix * changes;
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &temp[0][0]);
	if (texture != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

	}
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

void Cube2::Animate(float dt, bool reverse) {
	if (animateType == 1)
	{
		if (reverse)
			frame = frame - dt * 400;
		else
			frame = frame + dt * 400;

		if (frame > 360)
		{
			frame = frame - 360;
		}
		if (frame < 0)
		{
			frame = frame + 360;
		}

		float i = sin(radians(frame)) / 5;
		float f;
		if (frame >= 270 || frame <= 90)
			f = abs(sin(radians((frame + 90)))) / 10;
		else
			f = 0;
		animationMatrix = translate(glm::mat4(1.0f), vec3(0.0f, f, i));
	}
	else if (animateType == 2)
	{
		if (reverse)
			frame = frame - dt * 400;
		else
			frame = frame + dt * 400;

		if (frame > 360)
		{
			frame = frame - 360;
		}
		if (frame < 0)
		{
			frame = frame + 360;
		}


		float i = sin(radians(frame + 180)) / 5;
		float f;
		if (frame <= 270 && frame >= 90)
			f = abs(sin(radians((frame + 90)))) / 10;
		else
			f = 0;


		animationMatrix = translate(glm::mat4(1.0f), vec3(0.0f, f, i));
	}
	else if (animateType == 3)
	{
		if (reverse) {
			frame = frame - dt * 400;
		}
		else {
			frame = frame + dt * 400;
		}
		if (frame > 360)
		{
			frame = frame - 360;
		}
		if (frame < 0) {
			frame += 360;
		}

		float i = -1 * sin(radians(frame))*40;

		animationMatrix = rotate(glm::mat4(1.0f), radians(i),vec3(0.0f, 1.0f, 0.0f));
	}
	else if (animateType == 4)
	{
		if (reverse) {
			frame = frame - dt * 400;
		}
		else {
			frame = frame + dt * 400;
		}
		if (frame > 360)
		{
			frame = frame - 360;
		}
		if (frame < 0) {
			frame += 360;
		}

		float i = sin(radians(frame+180)) * 40;

		animationMatrix = rotate(glm::mat4(1.0f), radians(i), vec3(0.0f, 1.0f, 0.0f));
	}
	else if (animateType == 5)
	{
		if (frame < 90)
			frame = 90;

		if (frame <= 270)
		{
			frame = frame + dt * 400;
			float i = sin(radians(frame));			
			if (frame < 270 && frame > 90)
				changes = originalBuild * scale(mat4(1.0f), vec3(1.0f, abs(i), 1.0f));

		}
		else {
			changes = originalBuild;
			frame = 90;
		}
	}
	else {
		animationMatrix = mat4(1.0f);
	}

}

