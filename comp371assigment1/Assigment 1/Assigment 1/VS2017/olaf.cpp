#include"olaf.h"


using namespace glm;
using namespace std;

Olaf::Olaf(int shaderProgram)
	: changes(translate(mat4(1.0f), vec3(2.5f, 1.0f, 2.5f)) * glm::scale(mat4(1.0), vec3(2.5f, 2.5f, 2.5f))), 
	//i don't like this, but it won't let me not have it
	head(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	mask(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	scarf(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	scarf2(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	chest(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	eyeL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	eyeR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	nose(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	armR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	armL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	footL(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	footR(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	button1(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	button3(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	button2(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	hat(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	hat2(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(changes, vec3(0.0f, 3.0f, 0.0f)), shaderProgram)),
	shoe1(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.3f, -0.6f, 0.0f)), shaderProgram)),
	shoe2(Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.3f, -0.6f, 0.0f)), shaderProgram))

{
	chest = Cube2(vec3(1.0f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.0f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.75f, 0.75f, 0.75f)), shaderProgram);
	mask = Cube2(vec3(0.0f, 1.0f, 0.5f), glm::translate(mat4(1.0f), vec3(0.0f, 1.35f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.55f, 0.1f, 0.55f)), shaderProgram);
	scarf = Cube2(vec3(0.5f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.0f, 1.105f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.9f, 0.1f, 0.9f)), shaderProgram);
	scarf2 = Cube2(vec3(0.5f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.45f, 0.84f, 0.35f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.65f, 0.1f)), shaderProgram);
	head = Cube2(vec3(1.0f, 1.0f, 1.0f), glm::translate(mat4(1.0f), vec3(0.0f, 1.3f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.5f, 0.5f, 0.5f)), shaderProgram);
	footL= Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(-0.3f, -0.6f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.25f, 0.25f)), shaderProgram);
	footR = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.3f, -0.6f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.25f, 0.25f)), shaderProgram);
	shoe1 = Cube2(vec3(1.0f, 0.0f, 0.0f), translate(mat4(1.0f), vec3(0.3f, -0.655f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.3f, 0.15f, 0.3f)), shaderProgram);
	shoe2 = Cube2(vec3(1.0f, 0.0f, 0.0f), translate(mat4(1.0f), vec3(-0.3f, -0.655f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.3f, 0.15f, 0.3f)), shaderProgram);
	eyeR = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(0.1f, 1.35f, 0.27f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	eyeL = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(-0.1f, 1.35f, 0.27f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	hat = Cube2(vec3(0.1f, 0.1f, 0.1f), glm::translate(mat4(1.0f), vec3(0.0f, 1.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.25f, 0.50f, 0.25f)), shaderProgram);
	hat2 = Cube2(vec3(0.1f, 0.1f, 0.1f), glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.0f)) * glm::scale(mat4(1.0), vec3(0.75f, 0.15f, 0.75f)), shaderProgram);
	nose = Cube2(vec3(1.8f, .7f, 0.0f), translate(mat4(1.0f), vec3(0.0f, 1.23f, 0.35f)) * glm::scale(mat4(1.0), vec3(0.05f, 0.05f, 0.25f)), shaderProgram);
	armR = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(-0.6f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(1.0f, 0.25f, 0.25f)), shaderProgram);
	armL = Cube2(vec3(1.0f, 1.0f, 1.0f), translate(mat4(1.0f), vec3(0.6f, 0.8f, 0.0f)) * glm::scale(mat4(1.0), vec3(1.0f, 0.25f, 0.25f)), shaderProgram);
	button1 = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(0.0f, 0.35f, 0.55f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	button2 = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(0.0f, 0.70f, 0.425f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);
	button3 = Cube2(vec3(0.1f, 0.1f, 0.1f), translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.425f)) * glm::scale(mat4(1.0), vec3(0.1f, 0.1f, 0.1f)), shaderProgram);

	changes = mat4(1.0);
	world = mat4(1.0);

	Olaf::Update(translate(mat4(1.0f), vec3(0.0f, 0.745f, 0.0f)));
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

	glVertexAttribPointer(0, // attribute 0 matches aPos in Vertex Shader
		3,                   // size
		GL_FLOAT,            // type
		GL_FALSE,            // normalized?
		2 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0             // array buffer offset
	);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1,	 // attribute 1 matches aColor in Vertex Shader
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
	scarf.Draw();
	scarf2.Draw();
	mask.Draw();
	head.Draw();
	footL.Draw();
	footR.Draw();
	eyeR.Draw();
	eyeL.Draw();
	hat.Draw();
	hat2.Draw();
	nose.Draw();
	shoe1.Draw();
	shoe2.Draw();
	armR.Draw();
	armL.Draw();
	button1.Draw();
	button2.Draw();
	button3.Draw();
}

void Olaf::Update(glm::mat4 newStuff)
{
	changes = newStuff * changes;
	chest.UpdateParent(newStuff);
	scarf.UpdateParent(newStuff);
	scarf2.UpdateParent(newStuff);
	head.UpdateParent(newStuff);
	mask.UpdateParent(newStuff);
	shoe1.UpdateParent(newStuff);
	shoe2.UpdateParent(newStuff);
	footL.UpdateParent(newStuff);
	footR.UpdateParent(newStuff);
	eyeR.UpdateParent(newStuff);
	eyeL.UpdateParent(newStuff);
	hat.UpdateParent(newStuff);
	hat2.UpdateParent(newStuff);
	nose.UpdateParent(newStuff);
	armR.UpdateParent(newStuff);
	armL.UpdateParent(newStuff);
	button1.UpdateParent(newStuff);
	button2.UpdateParent(newStuff);
	button3.UpdateParent(newStuff);
}

void Olaf::Rotate(float angle, vec3 orientation)
{
	chest.RotateParent(angle, orientation);
	head.RotateParent(angle, orientation);
	mask.RotateParent(angle, orientation);
	scarf.RotateParent(angle, orientation);
	scarf2.RotateParent(angle, orientation);
	footL.RotateParent(angle, orientation);
	footR.RotateParent(angle, orientation);
	eyeR.RotateParent(angle, orientation);
	eyeL.RotateParent(angle, orientation);
	hat.RotateParent(angle, orientation);
	hat2.RotateParent(angle, orientation);
	shoe1.RotateParent(angle, orientation);
	shoe2.RotateParent(angle, orientation);
	nose.RotateParent(angle, orientation);
	armR.RotateParent(angle, orientation);
	armL.RotateParent(angle, orientation);
	button1.RotateParent(angle, orientation);
	button2.RotateParent(angle, orientation);
	button3.RotateParent(angle, orientation);
	changes = rotate(changes, angle, orientation);	
}


void Olaf::Translate(glm::vec3 movement) {
	changes = changes * translate(glm::mat4(1.0f), movement);
	chest.TranslateParent(movement);
	mask.TranslateParent(movement);
	scarf.TranslateParent(movement);
	scarf2.TranslateParent(movement);
	hat.TranslateParent(movement);
	hat2.TranslateParent(movement);
	head.TranslateParent(movement);
	armL.TranslateParent(movement);
	armR.TranslateParent(movement);
	eyeR.TranslateParent(movement);
	footR.TranslateParent(movement);
	eyeL.TranslateParent(movement);
	footL.TranslateParent(movement);
	nose.TranslateParent(movement);
	shoe1.TranslateParent(movement);
	shoe2.TranslateParent(movement);
	button1.TranslateParent(movement);
	button2.TranslateParent(movement);
	button3.TranslateParent(movement);
}

void Olaf::Scale(glm::vec3 scalee)
{
	changes = glm::scale(changes, scalee);
	chest.ScaleParent(scalee);
	mask.ScaleParent(scalee);
	scarf.ScaleParent(scalee);
	scarf2.ScaleParent(scalee);
	hat.ScaleParent(scalee);
	hat2.ScaleParent(scalee);
	head.ScaleParent(scalee);
	shoe1.ScaleParent(scalee);
	shoe2.ScaleParent(scalee);
	armL.ScaleParent(scalee);
	armR.ScaleParent(scalee);
	eyeR.ScaleParent(scalee);
	footR.ScaleParent(scalee);
	eyeL.ScaleParent(scalee);
	footL.ScaleParent(scalee);
	nose.ScaleParent(scalee);
	button1.ScaleParent(scalee);
	button2.ScaleParent(scalee);
	button3.ScaleParent(scalee);
}

void Olaf::Nuke() {
	float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)) - 50;
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100)) - 50;
	changes = translate(mat4(1.0f), vec3(r1, 0.70f, r2));
	hat.Nuke(changes);
	hat2.Nuke(changes);
	chest.Nuke(changes);
	scarf.Nuke(changes);
	scarf2.Nuke(changes);
	mask.Nuke(changes);
	head.Nuke(changes);
	armL.Nuke(changes);
	armR.Nuke(changes);
	eyeR.Nuke(changes);
	footR.Nuke(changes);
	shoe1.Nuke(changes);
	shoe2.Nuke(changes);
	eyeL.Nuke(changes);
	footL.Nuke(changes);
	nose.Nuke(changes);
	button1.Nuke(changes);
	button2.Nuke(changes);
	button3.Nuke(changes);

}

void Olaf::ResetWorld()
{
	world = mat4(1.0f);
	scarf.ResetWorld();
	scarf2.ResetWorld();
	hat.ResetWorld();
	hat2.ResetWorld();
	mask.ResetWorld();
	chest.ResetWorld();
	head.ResetWorld();
	shoe1.ResetWorld();
	shoe2.ResetWorld();
	armL.ResetWorld();
	armR.ResetWorld();
	eyeR.ResetWorld();
	footR.ResetWorld();
	eyeL.ResetWorld();
	footL.ResetWorld();
	nose.ResetWorld();
	button1.ResetWorld();
	button2.ResetWorld();
	button3.ResetWorld();
}

void Olaf::UpdateWorld(glm::mat4 stuffandthings)
{
	world = stuffandthings * world;
	scarf.UpdateWorld(stuffandthings);
	scarf2.UpdateWorld(stuffandthings);
	hat.UpdateWorld(stuffandthings);
	hat2.UpdateWorld(stuffandthings);
	chest.UpdateWorld(stuffandthings);
	shoe1.UpdateWorld(stuffandthings);
	shoe2.UpdateWorld(stuffandthings);
	head.UpdateWorld(stuffandthings);
	mask.UpdateWorld(stuffandthings);
	armL.UpdateWorld(stuffandthings);
	armR.UpdateWorld(stuffandthings);
	eyeR.UpdateWorld(stuffandthings);
	footR.UpdateWorld(stuffandthings);
	eyeL.UpdateWorld(stuffandthings);
	footL.UpdateWorld(stuffandthings);
	nose.UpdateWorld(stuffandthings);
	button1.UpdateWorld(stuffandthings);
	button2.UpdateWorld(stuffandthings);
	button3.UpdateWorld(stuffandthings);
}
