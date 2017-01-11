/**
An ArbitraryProperty stores a property of any one of the supported types.

Only one type is active at any given time.

@author Nathan */

#ifndef ARBITRARY_PROPERTY_H
#define ARBITRARY_PROPERTY_H

#include <string>
#include <glm\glm.hpp>

class ArbitraryProperty
{
	public:
		enum SupportedTypes
		{
			NONE,
			INT,
			LONG,
			FLOAT,
			DOUBLE,
			BOOL,
			VEC2,
			VEC3,
			VEC4,
			MAT3,
			MAT4,
			STRING
		};

	private:
		union
		{
			int m_iIntField;
			long m_iLongField;
			float m_fFloatField;
			double m_fDoubleField;
			bool m_bBoolField;
			glm::vec2* m_vec2Field;
			glm::vec3* m_vec3Field;
			glm::vec4* m_vec4Field;
			glm::mat3* m_mat3Field;
			glm::mat4* m_mat4Field;
			std::string* m_stringField;
		};

		bool m_bIdSet;
		unsigned int m_uiId;
		std::string m_sPropertyName;
		SupportedTypes m_activeType;

		ArbitraryProperty();

	protected:

	public:
		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param i An integer value */
		ArbitraryProperty(std::string sPropertyName, int i);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param l A long value */
		ArbitraryProperty(std::string sPropertyName, long l);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param f A float value */
		ArbitraryProperty(std::string sPropertyName, float f);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param d A double value */
		ArbitraryProperty(std::string sPropertyName, double d);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param b A boolean value */
		ArbitraryProperty(std::string sPropertyName, bool b);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param v2 A vec2 value */
		ArbitraryProperty(std::string sPropertyName, glm::vec2* v2);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param v3 A vec3 value */
		ArbitraryProperty(std::string sPropertyName, glm::vec3* v3);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param v4 A vec4 value */
		ArbitraryProperty(std::string sPropertyName, glm::vec4* v4);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param m3 A mat3 value */
		ArbitraryProperty(std::string sPropertyName, glm::mat3* m3);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param m4 A mat4 value */
		ArbitraryProperty(std::string sPropertyName, glm::mat4* m4);

		/**
		Constructs an ArbitaryProperty with the given name.
		@param sPropertyName The name by which to refer to the property
		@param s A string value */
		ArbitraryProperty(std::string sPropertyName, std::string* s);
		
		~ArbitraryProperty();

		/**
		Retrieves the value of the integer field. The property must be an integer for this function
		to be called safely. If it is not, the behaviour is undefined.
		@return An integer value */
		int getIntField() const;
		long getLongField() const;
		float getFloatField() const;
		double getDoubleField() const;
		bool getBoolField() const;
		glm::vec2 getVec2Field() const;
		glm::vec3 getVec3Field() const;
		glm::vec4 getVec4Field() const;
		glm::mat3 getMat3Field() const;
		glm::mat4 getMat4Field() const;
		std::string getStringField() const;

		/**
		Sets the id of the property. This is a convenience function and will probably be moved
		elsewhere later on. 
		@param uiId The id */
		void setId(unsigned int uiId);

		/**
		Gets the id of the property. This is a convenience function and will probably be moved
		elsewhere later on. 
		@return The id */
		unsigned int getId() const;

		/**
		Gets the name of the property.
		@return The name */
		const std::string& getPropertyName() const;

		/**
		Gets the active type. Only one type may be active at any given time.
		@return The active type */
		SupportedTypes getActiveType() const;
};

#endif