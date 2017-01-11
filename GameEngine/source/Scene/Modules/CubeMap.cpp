#include "Scene/Modules/CubeMap.h"

CubeMap::CubeMap(float fSize, std::vector<std::string> filePaths)
{
	//// Create a cube out of 6 faces (Each with 6 points - because they're triangles)
	//m_fSize = fSize;

	//glGenVertexArrays(1, &m_vao);
	//glBindVertexArray(m_vao);
	//glEnableVertexAttribArray(0);

	//// Create a vertex buffer object to store the points data in
	//setPosition(glm::vec3(0.f, 0.f, 0.f));
	//glm::vec3 pos(0.f, 0.f, 0.f);

	//float points[] =
	//{
	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,

	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,

	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,

	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,

	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, m_fSize + pos.z,
	//	-m_fSize + pos.x, m_fSize + pos.y, -m_fSize + pos.z,

	//	-m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, -m_fSize + pos.z,
	//	-m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z,
	//	m_fSize + pos.x, -m_fSize + pos.y, m_fSize + pos.z
	//};

	//gl::GenBuffers(1, &m_vbo);
	//gl::BindBuffer(gl::ARRAY_BUFFER, m_vbo);
	//gl::BufferData(gl::ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, gl::STATIC_DRAW);
	//gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);

	//// Check we have the correct number of file paths
	//if (filePaths.size() >= 6)
	//{
	//	// Generate a cube map texture
	//	gl::ActiveTexture(gl::TEXTURE0);
	//	gl::GenTextures(1, &m_cubeTexture);
	//	gl::BindTexture(gl::TEXTURE_CUBE_MAP, m_cubeTexture);

	//	// Load the textures and attach them to the cube map
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		Bitmap bmp = Bitmap::bitmapFromFile(filePaths.at(i));
	//		gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, gl::RGB, bmp.width(),
	//			bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());
	//	}

	//	// Configure the cube map
	//	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	//	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	//	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);
	//	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	//	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	//}
}