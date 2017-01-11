#version 430

layout (location = 0) in vec3 vVertexPosition;
layout (location = 1) in vec3 vVertexNormal;
layout (location = 2) in vec2 vUV;

out vec3 vVertPos;                                  // Vertex position in eye coords
out vec3 vNormal;                                   // Transformed normal
out vec2 vUVCoord;                                  // UV coordinate

uniform mat3 mNormalMatrix;                         // Used to apply rotation and scaling to normals
uniform mat4 mPVM;                                  // Transforms a vertex from model space to screen space
uniform mat4 mVM;                                   // Transforms a vertex from model space to eye space
uniform mat4 mM;

void main()
{
	// Forward the UV coordinate to the fragment shader
	vUVCoord = vUV;

	vVertPos = vec3(mM * vec4(vVertexPosition, 1.0));
	vNormal = normalize(mNormalMatrix * vVertexNormal);
	gl_Position = mPVM * vec4(vVertexPosition, 1.0);
}