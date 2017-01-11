#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 vReflectionVector;
uniform mat4 mPVM;

void main()
{
	vReflectionVector = VertexPosition;
	gl_Position = mPVM * vec4(VertexPosition, 1.0);
}