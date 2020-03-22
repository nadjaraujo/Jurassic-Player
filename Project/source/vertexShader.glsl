#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out vec2 pass_textureCoords;
uniform mat4 transform;

//Declaraçoes da perspectiva
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//gl_Position = vec4(position, 1.0);
	gl_Position = projection *view *  transform * vec4(position, 1.0);
	
	pass_textureCoords = textureCoords;
}