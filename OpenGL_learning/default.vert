#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
//
layout (location = 1) in vec3 aNormal; 
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Curent Position
out vec3 crntPos;
// Normal
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;



uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 projection; // aspecRatio

void main()
{ 
	// Curent Position
	crntPos = vec3( model * translation * -rotation * scale vec4(aPos, 1.0f));
	//Normal
	Normal = aNormal;	
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0) * aTex;

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);	
}