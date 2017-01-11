/**
A ScriptVar is a variable component of the scripting module.

ScriptVars have a limited number of supported types and may only represent one of those
types at any given time.

@author Nathan */

#ifndef SCRIPT_VAR_H
#define SCRIPT_VAR_H

#include <string>

class ScriptVar
{
	public:
		enum class SupportedTypes
		{
			STRING,
			INT,
			FLOAT,
			BOOL,
			VOID
		};

	private:
		union
		{
			std::string* m_stringField;
			int m_intField;
			float m_floatField;
			bool m_boolField;
		};

		SupportedTypes m_activeType;

	protected:

	public:
		/**
		Constructs a void-type ScriptVar. */
		ScriptVar();

		/**
		Constructs a string-type ScriptVar.
		@param sVal A string value */
		explicit ScriptVar(std::string& sVal);

		/**
		Constructs an integer-type ScriptVar.
		@param iVal An integer value */
		explicit ScriptVar(int iVal);

		/**
		Constructs a float-type ScriptVar.
		@param fVal A float value */
		explicit ScriptVar(float fVal);

		/**
		Constructs a boolean-type ScriptVar.
		@param bVal A boolean value */
		explicit ScriptVar(bool bVal); 
		
		/**
		Assigns the value of one ScriptVar to this ScriptVar.
		@param other The ScriptVar to copy */
		ScriptVar& operator=(const ScriptVar& other);

		/**
		Constructs a new ScriptVar and copies the contents of another ScriptVar in to it.
		@param other The ScriptVar to copy */
		ScriptVar(const ScriptVar& other);
		~ScriptVar();

		/**
		Gets the type of the ScriptVar. 
		@return The type */
		const SupportedTypes& getType() const;
		
		/**
		Gets the contents of the string field. If the string field is not the active type, calling this
		function results in undefined behaviour.
		@return A string value */
		const std::string& getString() const;

		/**
		Gets the contents of the integer field. If the integer field is not the active type, calling this
		function results in undefined behaviour.
		@return An integer value */
		int getInt() const;

		/**
		Gets the contents of the float field. If the float field is not the active type, calling this
		function results in undefined behaviour.
		@return A float value */
		float getFloat() const;

		/**
		Gets the contents of the boolean field. If the boolean field is not the active type, calling this
		function results in undefined behaviour.
		@return A boolean value */
		bool getBool() const;

		/**
		Sets the value of the string field. The ScriptVar becomes a string type. 
		@param sVal The string value to assign */
		void setString(const std::string& sVal);

		/**
		Sets the value of the integer field. The ScriptVar becomes an integer type.
		@param iVal The integer value to assign */
		void setInt(int iVal);

		/**
		Sets the value of the float field. The ScriptVar becomes a float type.
		@param fVal The float value to assign */
		void setFloat(float fVal);

		/**
		Sets the value of the boolean field. The ScriptVar becomes a boolean type.
		@param bVal The boolean value to assign */
		void setBool(bool bVal);

		/**
		Returns a string representation of the given variable type. 
		@param type The type to convert
		@return A string representation of the given variable type */
		static std::string typeToString(SupportedTypes type);
};

#endif