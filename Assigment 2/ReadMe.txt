The main code runs form the file Source.cpp

Camera.cpp is just basic camera setup. I plan to refactor and move all the functionality in here.

cube.cpp is my first build for a cube (not as in depth, used for grid and 3 Axis)
cube2.cpp is a more robust version of a cube with more functionality

fragment.glsl and vertex.glsl are self explanatory

grid.cpp is a simple class that builds the grid.

olaf.cpp contains multiple cube2 objects, each one refering to a part of the snowman. 
////////////////////////
RUNNING THE PROGRAM
A and D rotate Olaf along his Y axis. 

//Bonus
W and S rotate Olaf along his Z axis.

SHIFT + A or D move olaf left or right depending on his direction.
SHIFT + W or S move olaf Front or back depending on his direction.

P shows the world using points.
T shows the world using Triangles.
L shows the world using lines.

U scales olaf up.
J scales olaf down. 

left and right arrows rotate the world observed by the camera along its X axis.
up and down arrow keys rotate the world observed by the camera along its Y axis.

home or shift + backspace resets the world observed by the camera and the camera to their initial state.
(my laptop has no home button so i added a button)

space bar resets olaf's height and direction and teleports him to a random location on the grid. 

hold left click to zoom in and out depending on the direction the camera is facing. 

hold right click to pan the camera left and right, moving along it's x axis.

hold the center mouse button to change the pitch and yaw of the camera. (added yaw for extra control) 

//Extra parts to olaf
Olaf has: 
	Shoes on his feet. 
	Buttons on his chest.

//Github link in case you need it
https://github.com/EvanDime/COMP371-ass1


///Assigment 2 addons
Olaf's head body and chest are now round. 

There is a texture on the ground and on his nose. 
press X to toggle the textured ground and the grid

shift+S and shift+W now also do the walking animation forward and backards. you can tap it or hold it.
while walking, you can use O and K to turn left and right while walking. 

You can use Z and shift+Z to do a full forward and backward walk cycle respectively. 

//BONUS ANIMATIONS
press C to make the Right eye wink.
press shift+C to make the left eye wink.
press B to make the snowman blink. 