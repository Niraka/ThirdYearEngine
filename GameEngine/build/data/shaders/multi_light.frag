#version 430

struct AmbientLight
{
	vec3 vColour;
};

struct PointLight
{
	vec3 vColour;
	vec3 vPosition;
};

struct SpotLight
{
	vec3 vColour;
	vec3 vPosition;
	vec3 vTargetPosition;
	float fSpotCutOff;
};

struct Material
{
	vec3 vReflectionA;
	vec3 vReflectionD;
	vec3 vReflectionS;

	float fShininess;
};

// The number of active lights in each category
uniform int iNumAmbientLights;
uniform int iNumPointLights;
uniform int iNumSpotLights;

// The data of each light in each category
uniform AmbientLight ambientLights[3];
uniform PointLight pointLights[10];
uniform SpotLight spotLights[10];

// Texture information
uniform sampler2D ambientTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform samplerCube cubeTexture;

// Active material information
uniform Material activeMaterial;

in vec3 vVertPos;
in vec3 vNormal;
in vec2 vUVCoord;

// The eye position
uniform vec3 vEyePos = vec3(0, 0, -5);
uniform mat4 mM;
uniform mat4 mV;

// View-model matrix
uniform mat4 mVM;

uniform bool bUsingTexture = true;

// Output colour
layout(location = 0) out vec4 vFragColour;

// Declare functions
vec3 calculateSpotLight(SpotLight light, Material mat);
vec3 calculatePointLight(PointLight light, Material mat);
vec3 calculateAmbientLight(AmbientLight light, Material mat);

void main() 
{
	vFragColour = vec4(0, 0, 0, 0);
		
	// Process each light
	vec3 vResultantLight = vec3(0, 0, 0);
	for (int i = 0; i < iNumAmbientLights; ++i)
	{
		vResultantLight += calculateAmbientLight(ambientLights[i], activeMaterial);
	}
	for (int i = 0; i < iNumPointLights; ++i)
	{	
		vResultantLight += calculatePointLight(pointLights[i], activeMaterial);
	}
	for (int i = 0; i < iNumSpotLights; ++i)
	{
		vResultantLight += calculateSpotLight(spotLights[i], activeMaterial);
	}

	// Clamp the resultant light
	vResultantLight = clamp(vResultantLight, 0.0, 1.0);
	vFragColour = vec4(vResultantLight, 1.0);

	// Sample the texture
	if (bUsingTexture)
	{			
		vFragColour *= texture(diffuseTexture, vUVCoord);
	}
}

// Spot lights
vec3 calculateSpotLight(SpotLight light, Material mat)
{
	vec3 vResult = vec3(0, 0, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Diffuse component:

	vec3 vLightDirection = normalize(light.vPosition - vVertPos);                          
	float fNormalDirection = dot(vNormal, vLightDirection);                
	fNormalDirection = clamp(fNormalDirection, 0.0, 1.0);
	
	vec3 vDiffuseComponent = light.vColour * mat.vReflectionD * (max(fNormalDirection, 0.0));
		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Specular component:	

	vec3 vViewDirection = normalize(vVertPos - vEyePos);                         // V
	vec3 vReflectedLight = reflect(vLightDirection, vNormal);                    // R

	float fAngle = max(dot(vReflectedLight, vViewDirection), 0.0);               // R.V
	fAngle = pow(fAngle, mat.fShininess);                                        // (R.V)^n

	vec3 vSpecularComponent = light.vColour * mat.vReflectionS * fAngle;         // Is * Ks * (R.V)^n

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Apply attenuation
	vec3 vTargetDirection = normalize(light.vPosition - light.vTargetPosition);
	fAngle = dot(vLightDirection, vTargetDirection);
	fAngle = clamp(fAngle, 0, 1);

	float fAttenuation = 0.f;
	if (acos(fAngle) <= radians(light.fSpotCutOff))
	{
		fAttenuation = fAngle;
	}		
		
	vDiffuseComponent *= fAttenuation;                                           // Mod diffuse by attenuation
	vSpecularComponent *= fAttenuation;                                          // Mod specular by attenuation
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sum the result
	vResult += vDiffuseComponent;
	vResult += vSpecularComponent;                                               // Sum diffuse and specular components	
	return vResult;
}

// Point lights
vec3 calculatePointLight(PointLight light, Material mat)
{
	vec3 vResult = vec3(0, 0, 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Diffuse component:

	vec3 vLightDirection = normalize(light.vPosition - vVertPos);                          
	float fNormalDirection = dot(vNormal, vLightDirection);                
	fNormalDirection = clamp(fNormalDirection, 0.0, 1.0);
	
	vec3 vDiffuseComponent = light.vColour * mat.vReflectionD * (max(fNormalDirection, 0.0));
		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Specular component:	

	vec3 vViewDirection = normalize(vVertPos - vEyePos);                         // V
	vec3 vReflectedLight = reflect(vLightDirection, vNormal);                    // R

	float fAngle = max(dot(vReflectedLight, vViewDirection), 0.0);               // R.V
	fAngle = pow(fAngle, mat.fShininess);                                        // (R.V)^n

	vec3 vSpecularComponent = light.vColour * mat.vReflectionS * fAngle;         // Is * Ks * (R.V)^n	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sum the result
	vResult += vDiffuseComponent;
	vResult += vSpecularComponent;                                               // Sum diffuse and specular components	
	return vResult;
}

// Ambient lights
vec3 calculateAmbientLight(AmbientLight light, Material mat)
{
	return mat.vReflectionA * light.vColour;
}