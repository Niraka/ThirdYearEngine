#include "System/Utility/ArbitraryProperty.h"

ArbitraryProperty::ArbitraryProperty()
{
	m_bIdSet = false;
	m_uiId = 0;
	m_activeType = SupportedTypes::NONE;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, int i)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_iIntField = i;
	m_activeType = SupportedTypes::INT;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, long l)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_iLongField = l;
	m_activeType = SupportedTypes::LONG;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, float f)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_fFloatField = f;
	m_activeType = SupportedTypes::FLOAT;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, double d)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_fDoubleField = d;
	m_activeType = SupportedTypes::DOUBLE;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, bool b)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_iIntField = b;
	m_activeType = SupportedTypes::BOOL;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, glm::vec2* v2)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_vec2Field = v2;
	m_activeType = SupportedTypes::VEC2;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, glm::vec3* v3)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_vec3Field = v3;
	m_activeType = SupportedTypes::VEC3;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, glm::vec4* v4)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_vec4Field = v4;
	m_activeType = SupportedTypes::VEC4;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, glm::mat3* m3)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_mat3Field = m3;
	m_activeType = SupportedTypes::MAT3;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, glm::mat4* m4)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_mat4Field = m4;
	m_activeType = SupportedTypes::MAT4;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::ArbitraryProperty(std::string sPropertyName, std::string* s)
{
	m_bIdSet = false;
	m_uiId = 0;
	m_stringField = s;
	m_activeType = SupportedTypes::STRING;
	m_sPropertyName = sPropertyName;
}

ArbitraryProperty::~ArbitraryProperty()
{
}

int ArbitraryProperty::getIntField() const
{
	return m_iIntField;
}

long ArbitraryProperty::getLongField() const
{
	return m_iLongField;
}

float ArbitraryProperty::getFloatField() const
{
	return m_fFloatField;
}

double ArbitraryProperty::getDoubleField() const
{
	return m_fDoubleField;
}

bool ArbitraryProperty::getBoolField() const
{
	return m_bBoolField;
}

glm::vec2 ArbitraryProperty::getVec2Field() const
{
	if (m_vec2Field)
	{
		return *m_vec2Field;
	}
	else
	{
		return glm::vec2();
	}
}

glm::vec3 ArbitraryProperty::getVec3Field() const
{
	if (m_vec3Field)
	{
		return *m_vec3Field;
	}
	else
	{
		return glm::vec3();
	}
}

glm::vec4 ArbitraryProperty::getVec4Field() const
{
	if (m_vec4Field)
	{
		return *m_vec4Field;
	}
	else
	{
		return glm::vec4();
	}
}

glm::mat3 ArbitraryProperty::getMat3Field() const
{
	if (m_mat3Field)
	{
		return *m_mat3Field;
	}
	else
	{
		return glm::mat3();
	}
}

glm::mat4 ArbitraryProperty::getMat4Field() const
{
	if (m_mat4Field)
	{
		return *m_mat4Field;
	}
	else
	{
		return glm::mat4();
	}
}

std::string ArbitraryProperty::getStringField() const
{
	if (m_stringField)
	{
		return *m_stringField;
	}
	else
	{
		return std::string();
	}
}

void ArbitraryProperty::setId(unsigned int uiId)
{
	if (!m_bIdSet)
	{
		m_bIdSet = !m_bIdSet;
		m_uiId = uiId;
	}
}

unsigned int ArbitraryProperty::getId() const
{
	return m_uiId;
}

const std::string& ArbitraryProperty::getPropertyName() const
{
	return m_sPropertyName;
}

ArbitraryProperty::SupportedTypes ArbitraryProperty::getActiveType() const
{
	return m_activeType;
}