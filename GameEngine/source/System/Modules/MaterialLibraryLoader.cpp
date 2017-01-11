#include "System/Modules/MaterialLibraryLoader.h"

MaterialLibraryLoader::MaterialLibraryLoader()
{
	m_sMaterialsDirectory = DirectoryListing::getInstance()->getDirectory("materials");
	m_sTexturesDirectory = DirectoryListing::getInstance()->getDirectory("textures");
}

MaterialLibraryLoader::~MaterialLibraryLoader()
{
}

bool MaterialLibraryLoader::loadMaterialLibrary(std::string sFile, std::shared_ptr<MaterialLibrary> lib)
{
	m_info.clear();

	// Attempt to open the .mtl file
	std::string sFullPath = m_sMaterialsDirectory + sFile;
	std::ifstream inStream(sFullPath);
	if (inStream.is_open())
	{
		// Create storage for the parsed values
		bool bFirstMaterial = true;
		std::string sLine;
		std::string sTag;
		std::string sCurrentMaterialName;
		Material currentMaterial;
		std::vector<std::string> splitStringOutput;

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

			// Parse the data depending on the tag
			// Creates a new material
			if (sTag == "newmtl")
			{
				if (bFirstMaterial == true)
				{
					bFirstMaterial = false;
				}
				else
				{
					lib->addMaterial(sCurrentMaterialName, currentMaterial);
				}
				currentMaterial = Material();
				sCurrentMaterialName = sLine;
			}
			// The ambient reflectivity
			else if (sTag == "Ka")
			{
				splitStringOutput = m_stringUtils.splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					currentMaterial.vReflectivityA.r = m_stringUtils.toFloat(splitStringOutput.at(0));
					currentMaterial.vReflectivityA.g = m_stringUtils.toFloat(splitStringOutput.at(1));
					currentMaterial.vReflectivityA.b = m_stringUtils.toFloat(splitStringOutput.at(2));
				}
			}
			// The diffuse reflectivity
			else if (sTag == "Kd")
			{
				splitStringOutput = m_stringUtils.splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					currentMaterial.vReflectivityD.r = m_stringUtils.toFloat(splitStringOutput.at(0));
					currentMaterial.vReflectivityD.g = m_stringUtils.toFloat(splitStringOutput.at(1));
					currentMaterial.vReflectivityD.b = m_stringUtils.toFloat(splitStringOutput.at(2));
				}

			}
			// The specular reflectivity
			else if (sTag == "Ks")
			{
				splitStringOutput = m_stringUtils.splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					currentMaterial.vReflectivityS.r = m_stringUtils.toFloat(splitStringOutput.at(0));
					currentMaterial.vReflectivityS.g = m_stringUtils.toFloat(splitStringOutput.at(1));
					currentMaterial.vReflectivityS.b = m_stringUtils.toFloat(splitStringOutput.at(2));
				}
			}
			// The ambient texture map
			else if (sTag == "map_Ka")
			{
				Bitmap bmp;
				if (Bitmap::bitmapFromFile(bmp, m_sTexturesDirectory + sLine))
				{
					bmp.flipVertically();
					std::shared_ptr<Texture> texture = std::make_shared<Texture>(bmp);
					currentMaterial.ambientMap = texture;
				}
			}
			// The diffuse texture map
			else if (sTag == "map_Kd")
			{
				Bitmap bmp;
				if (Bitmap::bitmapFromFile(bmp, m_sTexturesDirectory + sLine))
				{
					bmp.flipVertically();
					std::shared_ptr<Texture> texture = std::make_shared<Texture>(bmp);
					currentMaterial.diffuseMap = texture;
				}
			}
			// The specular texture map
			else if (sTag == "map_Ks")
			{
				Bitmap bmp;
				if (Bitmap::bitmapFromFile(bmp, m_sTexturesDirectory + sLine))
				{
					bmp.flipVertically();
					std::shared_ptr<Texture> texture = std::make_shared<Texture>(bmp);
					currentMaterial.specularMap = texture;
				}
			}
			// The transmission filter. This value is parsed but its operations are unsupported
			else if (sTag == "Tf")
			{
				splitStringOutput = m_stringUtils.splitString(sLine, ' ');
				if (splitStringOutput.size() == 3)
				{
					currentMaterial.transmissionFilter.r = m_stringUtils.toFloat(splitStringOutput.at(0));
					currentMaterial.transmissionFilter.g = m_stringUtils.toFloat(splitStringOutput.at(1));
					currentMaterial.transmissionFilter.b = m_stringUtils.toFloat(splitStringOutput.at(2));
				}
			}
			// This value is used for mathematical calculations on some surfaces that goes beyond the requirements
			// of this engine. The value is parsed but its operations are unsupported
			else if (sTag == "Ni")
			{
				currentMaterial.fNi = m_stringUtils.toFloat(sLine);
			}
			// Specular modifier
			else if (sTag == "Ns")
			{
				currentMaterial.fShininess = m_stringUtils.toFloat(sLine);
			}
			// The illumination model. See the wavefront obj wiki for more information on the available models. This
			// value is parsed but its operations are unsupported
			else if (sTag == "illum")
			{
				int iModel = m_stringUtils.toInt(sLine);
				switch (iModel)
				{
				case IlluminationModels::COLOUR_ON_AMBIENT_OFF:
					currentMaterial.illuminationModel = IlluminationModels::COLOUR_ON_AMBIENT_OFF;
					break;
				case IlluminationModels::COLOUR_ON_AMBIENT_ON:
					currentMaterial.illuminationModel = IlluminationModels::COLOUR_ON_AMBIENT_ON;
					break;
				case IlluminationModels::HIGHLIGHTS_ON:
					currentMaterial.illuminationModel = IlluminationModels::HIGHLIGHTS_ON;
					break;
				case IlluminationModels::REFLECTION_ON_RAYTRACE_ON:
					currentMaterial.illuminationModel = IlluminationModels::REFLECTION_ON_RAYTRACE_ON;
					break;
				case IlluminationModels::GLASS_ON_RAYTRACE_ON:
					currentMaterial.illuminationModel = IlluminationModels::GLASS_ON_RAYTRACE_ON;
					break;
				case IlluminationModels::FRESNEL_ON_RAYTRACE_ON:
					currentMaterial.illuminationModel = IlluminationModels::FRESNEL_ON_RAYTRACE_ON;
					break;
				case IlluminationModels::REFRACTION_ON_FRESNEL_OFF_RAYTRACE_ON:
					currentMaterial.illuminationModel = IlluminationModels::REFRACTION_ON_FRESNEL_OFF_RAYTRACE_ON;
					break;
				case IlluminationModels::REFRACTION_ON_FRESNEL_ON_RAYTRACE_ON:
					currentMaterial.illuminationModel = IlluminationModels::REFRACTION_ON_FRESNEL_ON_RAYTRACE_ON;
					break;
				case IlluminationModels::REFLECTION_ON_RAYTRACE_OFF:
					currentMaterial.illuminationModel = IlluminationModels::REFLECTION_ON_RAYTRACE_OFF;
					break;
				case IlluminationModels::GLASS_ON_RAYTRACE_OFF:
					currentMaterial.illuminationModel = IlluminationModels::GLASS_ON_RAYTRACE_OFF;
					break;
				case IlluminationModels::CASTS_SHADOWS_ON_INVISIBLE_SURFACES:
					currentMaterial.illuminationModel = IlluminationModels::CASTS_SHADOWS_ON_INVISIBLE_SURFACES;
					break;
				}
			}
		}

		// Store the last material (if there was one)
		if (bFirstMaterial != true)
		{
			lib->addMaterial(sCurrentMaterialName, currentMaterial);
		}	

		// Clean up any resources
		inStream.close();
		m_info.push_back(std::string("Loaded " + std::to_string(lib->getNumMaterials()) + " materials from " + sFullPath));
		return true;
	}
	else
	{
		m_info.push_back(std::string("Could not open material file: " + sFullPath));
		return false;
	}
}

std::vector<std::string> MaterialLibraryLoader::getInfo() const
{
	return m_info;
}