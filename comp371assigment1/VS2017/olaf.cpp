#include"olaf.h"


using namespace glm;
using namespace std;

Olaf::Olaf(int shaderProgram)
	: changes(translate(mat4(1.0f), vec3(2.5f, 1.0f, 2.5f)) * glm::scale(mat4(1.0), vec3(2.5f, 2.5f, 2.5f))), 
	//i don't like this
	head(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	chest(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	eyeL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	eyeR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	nose(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	armR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	armL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	footL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	footR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	hat(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram))

{
	chest = Cube2(vec3(1.0f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.0f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.75f, 0.75f, 0.75f)), shaderProgram);
	head = Cube2(vec3(1.0f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.0f, 1.3f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.5f, 0.5f, 0.5f)), shaderProgram);
	footL= Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(-0.3f, -0.6f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.25f, 0.25f)), shaderProgram);
	footR = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.3f, -0.6f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.25f, 0.25f)), shaderProgram);
	eyeR = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(0.1f, 1.35f, 0.27f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	eyeL = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(-0.1f, 1.35f, 0.27f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	hat = Cube2(vec3(0.1f, 0.1f, 0.1f), glm::translate(mat4(1.0f), vec3(0.0f, 1.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.50f, 0.25f)), shaderProgram);
	nose = Cube2(vec3(1.8f, .7f, 0.0f), translate(mat4(1.0f), vec3(0.0f, 1.23f, 0.35f)) * glm::scale(mat4(1.0), vec3(0.05f, 0.05f, 0.25f)), shaderProgram);
	armR = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(-0.6f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(1.0f, 0.25f, 0.25f)), shaderProgram);
	armL = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.6f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(1.0f, 0.25f, 0.25f)), shaderProgram);

	changes = mat4(1.0);
	world = mat4(1.0);

	Olaf::Update(translate(mat4(1.0f), vec3(0.0f, 0.7f, 0.0f)));
	glm::vec3 color = vec3(1.0f,1.0f, 1.0f);
	mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
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
	glGenVertexArrays(1, &olafVAO);
	glBindVertexArray(olafVAO);


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

void Olaf::Draw()
{
	mat4 temp = world * changes;
	glBindVertexArray(olafVAO);
	glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &temp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	chest.Draw();
	head.Draw();
	footL.Draw();
	footR.Draw();
	eyeR.Draw();
	eyeL.Draw();
	hat.Draw();
	nose.Draw();
	armR.Draw();
	armL.Draw();
}

void Olaf::Update(glm::mat4 newStuff)
{
	changes = newStuff * changes;
	chest.UpdateParent(newStuff);
	head.UpdateParent(newStuff);
	footL.UpdateParent(newStuff);
	footR.UpdateParent(newStuff);
	eyeR.UpdateParent(newStuff);
	eyeL.UpdateParent(newStuff);
	hat.UpdateParent(newStuff);
	nose.UpdateParent(newStuff);
	armR.UpdateParent(newStuff);
	armL.UpdateParent(newStuff);
}

void Olaf::Rotate(float angle, vec3 orientation)
{
	chest.RotateParent(angle, orientation);
	head.RotateParent(angle, orientation);
	footL.RotateParent(angle, orientation);
	footR.RotateParent(angle, orientation);
	eyeR.RotateParent(angle, orientation);
	eyeL.RotateParent(angle, orientation);
	hat.RotateParent(angle, orientation);
	nose.RotateParent(angle, orientation);
	armR.RotateParent(angle, orientation);
	armL.RotateParent(angle, orientation);
	changes = rotate(changes, angle, orientation);	
}


void Olaf::Translate(glm::vec3 movement) {
	changes = changes * translate(glm::mat4(1.0f), movement);
	chest.TranslateParent(movement);
	hat.TranslateParent(movement);
	head.TranslateParent(movement);
	armL.TranslateParent(movement);
	armR.TranslateParent(movement);
	eyeR.TranslateParent(movement);
	footR.TranslateParent(movement);
	eyeL.TranslateParent(movement);
	footL.TranslateParent(movement);
	nose.TranslateParent(movement);
}

void Olaf::Scale(glm::vec3 scalee)
{
	changes = glm::scale(changes, scalee);
	chest.ScaleParent(scalee);
	hat.ScaleParent(scalee);
	head.ScaleParent(scalee);
	armL.ScaleParent(scalee);
	armR.ScaleParent(scalee);
	eyeR.ScaleParent(scalee);
	footR.ScaleParent(scalee);
	eyeL.ScaleParent(scalee);
	footL.ScaleParent(scalee);
	nose.ScaleParent(scalee);
}

void Olaf::Nuke() {
	float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)) - 50;
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)) - 50;
	changes = translate(mat4(1.0f), vec3(r1, 0.70f, r2));
	hat.Nuke(changes);
	chest.Nuke(changes);
	head.Nuke(changes);
	armL.Nuke(changes);
	armR.Nuke(changes);
	eyeR.Nuke(changes);
	footR.Nuke(changes);
	eyeL.Nuke(changes);
	footL.Nuke(changes);
	nose.Nuke(changes);

}

void Olaf::ResetWorld()
{
	world = mat4(1.0f);
	hat.ResetWorld();
	chest.ResetWorld();
	head.ResetWorld();
	armL.ResetWorld();
	armR.ResetWorld();
	eyeR.ResetWorld();
	footR.ResetWorld();
	eyeL.ResetWorld();
	footL.ResetWorld();
	nose.ResetWorld();
}

void Olaf::UpdateWorld(glm::mat4 stuffandthings)
{
	world = stuffandthings * world;
	hat.UpdateWorld(stuffandthings);
	chest.UpdateWorld(stuffandthings);
	head.UpdateWorld(stuffandthings);
	armL.UpdateWorld(stuffandthings);
	armR.UpdateWorld(stuffandthings);
	eyeR.UpdateWorld(stuffandthings);
	footR.UpdateWorld(stuffandthings);
	eyeL.UpdateWorld(stuffandthings);
	footL.UpdateWorld(stuffandthings);
	nose.UpdateWorld(stuffandthings);
}
