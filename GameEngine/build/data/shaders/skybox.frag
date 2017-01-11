#version 430

uniform samplerCube cubeMap;
in vec3 vReflectionVector;

layout( location = 0 ) out vec4 FragColour;

void main() 
{
	FragColour = texture(cubeMap, vReflectionVector);	
}