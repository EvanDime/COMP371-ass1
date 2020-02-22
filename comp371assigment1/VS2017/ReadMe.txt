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
W and S rotate Olaf along his Z axis.

SHIFT + A or D move olaf left or right depending on his direction.
SHIFT + W or S move olaf Front or back depending on his direction.

P shows the world using points.
T shows the world using Triangles.
L shows the world using lines.
