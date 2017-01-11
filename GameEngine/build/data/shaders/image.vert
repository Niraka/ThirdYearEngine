#version 430

layout (location = 0) in vec3 vVertexPosition;     // Position data
layout (location = 1) in vec2 vTextureCoordinate;  // UV data

uniform mat4 mPVM;

void main()
{
	gl_Position = mPVM * vec4(vVertexPosition, 1.0);
}