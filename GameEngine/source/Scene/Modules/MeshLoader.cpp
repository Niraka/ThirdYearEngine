#include "Scene/Modules/MeshLoader.h"

MeshLoader::MeshLoader()
{
	m_sMeshesDirectory = DirectoryListing::getInstance()->getDirectory("meshes");
}

MeshLoader::~MeshLoader()
{
}

bool MeshLoader::loadMesh(std::string sFile, std::shared_ptr<Mesh> mesh)
{
	m_info.clear();

	// Attempt to open the .obj file
	std::string sFullPath = m_sMeshesDirectory + sFile;
	std::ifstream inStream(sFullPath);
	if (inStream.is_open())
	{
		// Create storage for the parsed values
		std::string sLine;
		std::string sTag;

		std::vector<float> vertices;
		std::vector<float> uvs;
		std::vector<float> normals;
		std::vector<unsigned int> indicesV;
		std::vector<unsigned int> indicesU;
		std::vector<unsigned int> indicesN;
		std::vector<unsigned int> indices;
		unsigned int uiNumFaces = 0;
		unsigned int uiNumFacesThisPart = 0;
		unsigned int uiFacesOffsetThisPart = 0;
		std::vector<MeshGroup> groups;
		unsigned int uiActiveGroupIndex;

		unsigned int uiIndexOffset = 0;
		bool bFirstFace = true;
		bool bHasUVs = true;

		// Storage for the min and max points. These are evaluated as the model is loaded to save time
		glm::vec3 vMinimumPoint;
		glm::vec3 vMaximumPoint;
		std::vector<std::string> splitStringOutput;

		// Switch to the 'default' group
		MeshGroup group;
		group.sGroupName = "default";
		group.uiParts = 0;
		groups.push_back(group);
		uiActiveGroupIndex = 0;

		// Begin parsing each line
		while (getline(inStream, sLine))
		{
			// Discard empty lines, comments and lines with no spaces (these wont contain anything useful)
			int iFirstSpace = sLine.find_first_of(' ');
			if (sLine.empty() || sLine.at(0) == '#' || iFirstSpace == std::string::npos)
			{
				continue;
			}

			// Get the line "tag" to determine the type of data on the line. Chop off the tag
			// and all whitespace before the first non-whitespace character
			sTag = sLine.substr(0, sLine.find_first_of(' '));
			sLine = sLine.substr(sLine.find_first_of(' ') + 1, std::string::npos);		

			if (sTag == "v")
			{
				// Vertices
				// 3 values - XYZ
				splitStringOutput = splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					float x = toFloat(splitStringOutput.at(0));
					float y = toFloat(splitStringOutput.at(1));
					float z = toFloat(splitStringOutput.at(2));

					// Evaluate the new vertex to see if it would expand the minimum or maximum points
					if (x < vMinimumPoint.x)
					{
						vMinimumPoint.x = x;
					}
					else if (x > vMaximumPoint.x)
					{
						vMaximumPoint.x = x;
					}
					if (y < vMinimumPoint.y)
					{
						vMinimumPoint.y = y;
					}
					else if (y > vMaximumPoint.y)
					{
						vMaximumPoint.y = y;
					}
					if (z < vMinimumPoint.z)
					{
						vMinimumPoint.z = z;
					}
					else if (z > vMaximumPoint.z)
					{
						vMaximumPoint.z = z;
					}

					// Deposit the vertex
					vertices.push_back(x);
					vertices.push_back(y);
					vertices.push_back(z);
				}
			}
			else if (sTag == "vn")
			{
				// Normals
				// 3 values - XYZ
				splitStringOutput = splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					normals.push_back(toFloat(splitStringOutput.at(0)));
					normals.push_back(toFloat(splitStringOutput.at(1)));
					normals.push_back(toFloat(splitStringOutput.at(2)));
				}
			}
			else if (sTag == "vt")
			{
				// Texture coordinates
				// 2 values - UV
				splitStringOutput = splitString(sLine, ' ');
				if (splitStringOutput.size() >= 2)
				{
					float u = toFloat(splitStringOutput.at(0));
					float v = toFloat(splitStringOutput.at(1));

					// Normalise any values outside the 0-1 range
					u = m_mathsUtils.clamp(0.f, 1.f, u);
					v = m_mathsUtils.clamp(0.f, 1.f, v);

					uvs.push_back(u);
					uvs.push_back(v);
				}
			}
			else if (sTag == "mtllib")
			{
				mesh->m_sDefaultMatLib = sLine;
			}
			else if (sTag == "usemtl")
			{
				// Material library is loaded externally
				groups.at(uiActiveGroupIndex).sMaterialName = sLine;
			}
			else if (sTag == "g")
			{
				// If the group is already active, continue
				if (groups.at(uiActiveGroupIndex).sGroupName == sLine)
				{
					continue;
				}

				// Store the number of faces that were members of the last group's part. Discard
				// if it was 0
				if (uiNumFacesThisPart > 0)
				{
					groups.at(uiActiveGroupIndex).uiIndicesOffset.push_back(uiFacesOffsetThisPart * 3);
					groups.at(uiActiveGroupIndex).uiIndicesThisPart.push_back(uiNumFacesThisPart * 3);
					groups.at(uiActiveGroupIndex).uiParts = groups.at(uiActiveGroupIndex).uiParts + 1;
				}

				// If the group already exists, switch to it and reset part counters
				// If the group did not exist, create it and reset part counters
				bool bFound = false;
				for (int i = 0; i < groups.size(); ++i)
				{
					if (groups.at(i).sGroupName == sLine)
					{
						uiActiveGroupIndex = i;
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					MeshGroup group;
					group.sGroupName = sLine;
					group.uiParts = 0;
					groups.push_back(group);
					uiActiveGroupIndex = groups.size() - 1;
				}

				uiNumFacesThisPart = 0;
				uiFacesOffsetThisPart = uiNumFaces;
			}
			else if (sTag == "f")
			{
				splitStringOutput = splitString(sLine, ' ');

				// Check there are 3 parameters. If there are more the mesh has not been triangulated
				// and therefore is not supported (or the line may be corrupt)
				if (splitStringOutput.size() == 3)
				{
					for (std::string& s : splitStringOutput)
					{
						// Check the line contained 2 slashes
						int iSlashIndex1 = s.find_first_of('/');
						int iSlashIndex2 = s.find_first_of('/', iSlashIndex1 + 1);
						if (iSlashIndex1 != std::string::npos && iSlashIndex2 != std::string::npos)
						{
							// If its the first face, check if there is UV data
							if (bFirstFace)
							{
								bFirstFace = false;
								if (iSlashIndex2 - iSlashIndex1 > 1)
								{
									m_info.push_back(std::string("Mesh using UVs: true"));
									bHasUVs = true;
								}
								else
								{
									m_info.push_back(std::string("Mesh using UVs: false"));
									bHasUVs = false;
								}
							}

							if (bHasUVs)
							{
								unsigned int indexV = 0;
								unsigned int indexU = 0;
								unsigned int indexN = 0;

								indexV = toInt(s.substr(0, iSlashIndex1)) - 1;
								indexU = toInt(s.substr(iSlashIndex1 + 1, iSlashIndex2 - iSlashIndex1 - 1)) - 1;
								indexN = toInt(s.substr(iSlashIndex2 + 1, std::string::npos)) - 1;

								indexV += uiIndexOffset;
								indexU += uiIndexOffset;
								indexN += uiIndexOffset;

								indicesV.push_back(indexV);
								indicesU.push_back(indexU);
								indicesN.push_back(indexN);
							}
							else
							{
								unsigned int indexV = 0;
								unsigned int indexN = 0;

								indexV = toInt(s.substr(0, iSlashIndex1)) - 1;
								indexN = toInt(s.substr(iSlashIndex2 + 1, std::string::npos)) - 1;

								indexV += uiIndexOffset;
								indexN += uiIndexOffset;

								indicesV.push_back(indexV);
								indicesN.push_back(indexN);
							}
						}
					}
						
					uiNumFaces++;
					uiNumFacesThisPart++;
				}
			}		
			else
			{
				continue;
			}
		}

		// Store the last groups part
		if (uiNumFacesThisPart > 0)
		{
			groups.at(uiActiveGroupIndex).uiIndicesOffset.push_back(uiFacesOffsetThisPart * 3);
			groups.at(uiActiveGroupIndex).uiIndicesThisPart.push_back(uiNumFacesThisPart * 3);
			groups.at(uiActiveGroupIndex).uiParts = groups.at(uiActiveGroupIndex).uiParts + 1;
		}
		
		// Purge empty groups
		for (unsigned int i = 0; i < groups.size(); ++i)
		{
			if (groups.at(i).uiParts == 0)
			{
				groups.erase(groups.begin() + i);
				--i;
			}
		}

		m_info.push_back(std::string("Number of groups: " + std::to_string(groups.size())));
		m_info.push_back(std::string("Parsed vertices: " + std::to_string(vertices.size())));
		m_info.push_back(std::string("Parsed uvs: " + std::to_string(uvs.size())));
		m_info.push_back(std::string("Parsed normals: " + std::to_string(normals.size())));
		
		// See note (1) for explanation of the purpose of this code
		// Rebuild indices
		if (bHasUVs)
		{		
			indices = resolveIndicesUvs(vertices, uvs, normals, indicesV, indicesU, indicesN);
		}
		else
		{
			indices = resolveIndicesNoUvs(vertices, normals, indicesV, indicesN);
		}

		m_info.push_back(std::string("Converted vertices: " + std::to_string(vertices.size())));
		m_info.push_back(std::string("Converted uvs: " + std::to_string(uvs.size())));
		m_info.push_back(std::string("Converted normals: " + std::to_string(normals.size())));
		
		// Generate the centre point
		glm::vec3 vCentrePoint;
		vCentrePoint.x = (vMinimumPoint.x + vMaximumPoint.x) / 2;
		vCentrePoint.y = (vMinimumPoint.y + vMaximumPoint.y) / 2;
		vCentrePoint.z = (vMinimumPoint.z + vMaximumPoint.z) / 2;

		// Store the mesh min, max and centre points
		mesh->m_min = vMinimumPoint;
		mesh->m_max = vMaximumPoint;
		mesh->m_centre = vCentrePoint;

		// Store the groups
		mesh->m_groups = groups;

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// Post the data to the GPU

		// Generate a vertex array object to store the buffers and state
		glGenVertexArrays(1, &mesh->m_uiVertexArrayId);
		glBindVertexArray(mesh->m_uiVertexArrayId);

		// Vertices
		if (!vertices.empty())
		{
			glGenBuffers(1, &mesh->m_uiVertexBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->m_uiVertexBufferId);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)nullptr + (0)));
			glEnableVertexAttribArray(0);
		}

		// UV data
		if (!uvs.empty())
		{
			glGenBuffers(1, &mesh->m_uiUvBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->m_uiUvBufferId);
			glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)nullptr + (0)));
			glEnableVertexAttribArray(2);
		}

		// Normals
		if (!normals.empty())
		{
			glGenBuffers(1, &mesh->m_uiNormalBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->m_uiNormalBufferId);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals.at(0), GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)nullptr + (0)));
			glEnableVertexAttribArray(1);
		}

		// Indices
		if (!indices.empty())
		{
			glGenBuffers(1, &mesh->m_uiIndicesBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_uiIndicesBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.at(0), GL_STATIC_DRAW);
		}

		// Unbind the vertex array (Remember 0 is a reserved value for unbinding!)
		glBindVertexArray(0);

		// Finish and close
		inStream.close();
		m_info.push_back(std::string("Successfully loaded Mesh file: " + sFullPath));
		return true;
	}
	else
	{
		m_info.push_back(std::string("Could not open Mesh file: " + sFullPath));
		return false;
	}
}

std::vector<unsigned int> MeshLoader::resolveIndicesNoUvs(std::vector<float>& vertices,
	std::vector<float>& normals,
	std::vector<unsigned int>& indicesV,
	std::vector<unsigned int>& indicesN)
{
	// Note that while this function is used to resolve indices, the actual operation involves
	// moving the vertex and normal data to match the correct indice vector.

	// Determine which vector is the largest. This vector will be used to select the indexes.
	unsigned int uiMax = vertices.size();
	VectorIndexes vi = VectorIndexes::VERTICES;
	if (normals.size() > uiMax)
	{
		uiMax = normals.size();
		vi = VectorIndexes::NORMALS;
	}

	// Create a new set of vectors to hold the corrected data
	std::vector<float> verticesFixed;
	std::vector<float> normalsFixed;

	// Copy the largest vector straight in to the fixed version
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		verticesFixed = vertices;
		normalsFixed.resize(uiMax, 0);
		break;
	case VectorIndexes::NORMALS:
		verticesFixed.resize(uiMax, 0);
		normalsFixed = normals;
		break;
	}

	// Begin the process of copying the data in to the correct arrays
	unsigned int uiNumIndices = 0;
	unsigned int uiIndiceIndex = 0;
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		uiNumIndices = indicesV.size();
		for (; uiIndiceIndex < uiNumIndices; ++uiIndiceIndex)
		{
			normalsFixed[(indicesV[uiIndiceIndex] * 3)] = normals[(indicesN[uiIndiceIndex] * 3) + 0];
			normalsFixed[(indicesV[uiIndiceIndex] * 3) + 1] = normals[(indicesN[uiIndiceIndex] * 3) + 1];
			normalsFixed[(indicesV[uiIndiceIndex] * 3) + 2] = normals[(indicesN[uiIndiceIndex] * 3) + 2];
		}
		break;
	case VectorIndexes::NORMALS:
		uiNumIndices = indicesN.size();
		for (; uiIndiceIndex < uiNumIndices; ++uiIndiceIndex)
		{
			verticesFixed[(indicesN[uiIndiceIndex] * 3)] = vertices[(indicesV[uiIndiceIndex] * 3) + 0];
			verticesFixed[(indicesN[uiIndiceIndex] * 3) + 1] = vertices[(indicesV[uiIndiceIndex] * 3) + 1];
			verticesFixed[(indicesN[uiIndiceIndex] * 3) + 2] = vertices[(indicesV[uiIndiceIndex] * 3) + 2];
		}
		break;
	}

	// Switch to the corrected data
	vertices = verticesFixed;
	normals = normalsFixed;

	// Return the correct indice array
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		return indicesV;
	case VectorIndexes::NORMALS:
		return indicesN;
	default:
		return indicesV;
	}
}

std::vector<unsigned int> MeshLoader::resolveIndicesUvs(std::vector<float>& vertices,
	std::vector<float>& uvs,
	std::vector<float>& normals,
	std::vector<unsigned int>& indicesV,
	std::vector<unsigned int>& indicesU,
	std::vector<unsigned int>& indicesN)
{
	// Note that while this function is used to resolve indices, the actual operation involves
	// moving the vertex, uv and normal data to match the correct indice vector.

	// Determine which vector is the largest. This vector will be used to select the indexes.
	unsigned int uiMax = vertices.size();
	VectorIndexes vi = VectorIndexes::VERTICES;
	if (uvs.size() > uiMax)
	{
		uiMax = uvs.size();
		vi = VectorIndexes::UVS;
	}
	if (normals.size() > uiMax)
	{
		uiMax = normals.size();
		vi = VectorIndexes::NORMALS;
	}

	// Create a new set of vectors to hold the corrected data
	std::vector<float> verticesFixed;
	std::vector<float> uvsFixed;
	std::vector<float> normalsFixed;

	// Copy the largest vector straight in to the fixed version
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		verticesFixed = vertices;
		uvsFixed.resize((uiMax / 3) * 2, 0);
		normalsFixed.resize(uiMax, 0);
		break;
	case VectorIndexes::UVS:
		verticesFixed.resize((uiMax / 2) * 3, 0);
		uvsFixed = uvs;
		normalsFixed.resize((uiMax / 2) * 3, 0);
		break;
	case VectorIndexes::NORMALS:
		verticesFixed.resize(uiMax, 0);
		uvsFixed.resize((uiMax / 3) * 2, 0);
		normalsFixed = normals;
		break;
	}

	// Begin the process of copying the data in to the correct arrays
	unsigned int uiNumIndices = 0;
	unsigned int uiIndiceIndex = 0;
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		uiNumIndices = indicesV.size();
		for (; uiIndiceIndex < uiNumIndices; ++uiIndiceIndex)
		{
			uvsFixed[(indicesV[uiIndiceIndex] * 2)] = uvs[(indicesU[uiIndiceIndex] * 2) + 0];
			uvsFixed[(indicesV[uiIndiceIndex] * 2) + 1] = uvs[(indicesU[uiIndiceIndex] * 2) + 1];
			normalsFixed[(indicesV[uiIndiceIndex] * 3)] = normals[(indicesN[uiIndiceIndex] * 3) + 0];
			normalsFixed[(indicesV[uiIndiceIndex] * 3) + 1] = normals[(indicesN[uiIndiceIndex] * 3) + 1];
			normalsFixed[(indicesV[uiIndiceIndex] * 3) + 2] = normals[(indicesN[uiIndiceIndex] * 3) + 2];
		}
		break;
	case VectorIndexes::UVS:
		uiNumIndices = indicesU.size();
		for (; uiIndiceIndex < uiNumIndices; ++uiIndiceIndex)
		{
			verticesFixed[(indicesU[uiIndiceIndex] * 3)] = vertices[(indicesV[uiIndiceIndex] * 3) + 0];
			verticesFixed[(indicesU[uiIndiceIndex] * 3) + 1] = vertices[(indicesV[uiIndiceIndex] * 3) + 1];
			verticesFixed[(indicesU[uiIndiceIndex] * 3) + 2] = vertices[(indicesV[uiIndiceIndex] * 3) + 2];
			normalsFixed[(indicesU[uiIndiceIndex] * 3)] = normals[(indicesN[uiIndiceIndex] * 3) + 0];
			normalsFixed[(indicesU[uiIndiceIndex] * 3) + 1] = normals[(indicesN[uiIndiceIndex] * 3) + 1];
			normalsFixed[(indicesU[uiIndiceIndex] * 3) + 2] = normals[(indicesN[uiIndiceIndex] * 3) + 2];
		}
		break;
	case VectorIndexes::NORMALS:
		uiNumIndices = indicesN.size();
		for (; uiIndiceIndex < uiNumIndices; ++uiIndiceIndex)
		{
			verticesFixed[(indicesN[uiIndiceIndex] * 3)] = vertices[(indicesV[uiIndiceIndex] * 3) + 0];
			verticesFixed[(indicesN[uiIndiceIndex] * 3) + 1] = vertices[(indicesV[uiIndiceIndex] * 3) + 1];
			verticesFixed[(indicesN[uiIndiceIndex] * 3) + 2] = vertices[(indicesV[uiIndiceIndex] * 3) + 2];
			uvsFixed[(indicesN[uiIndiceIndex] * 2)] = uvs[(indicesU[uiIndiceIndex] * 2) + 0];
			uvsFixed[(indicesN[uiIndiceIndex] * 2) + 1] = uvs[(indicesU[uiIndiceIndex] * 2) + 1];
		}
		break;
	}

	// Switch to the corrected data
	vertices = verticesFixed;
	uvs = uvsFixed;
	normals = normalsFixed;

	// Return the correct indice array
	switch (vi)
	{
	case VectorIndexes::VERTICES:
		return indicesV;
	case VectorIndexes::UVS:
		return indicesU;
	case VectorIndexes::NORMALS:
		return indicesN;
	default:
		return indicesV;
	}
}


int MeshLoader::toInt(std::string& sString)
{
	try
	{
		return std::stoi(sString);
	}
	catch (...)
	{
		return 1;
	}
}

float MeshLoader::toFloat(std::string& sString)
{
	try
	{
		return std::stof(sString);
	}
	catch (...)
	{
		return 1.f;
	}
}

std::vector<std::string> MeshLoader::splitString(std::string& sString, char cSplitChar)
{
	std::vector<std::string> output;
	std::stringstream ss(sString);
	std::string temp;
	while (std::getline(ss, temp, cSplitChar))
	{
		if (temp != "")
		{
			output.push_back(temp);
		}
	}
	return output;
}

std::vector<std::string> MeshLoader::getInfo() const
{
	return m_info;
}