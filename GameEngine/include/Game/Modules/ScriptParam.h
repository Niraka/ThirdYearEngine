/**
A ScriptParam is a parameter that may be passed in to Script functions.

Parameters may taken on only one of the supported types at any given time.

@author Nathan */

#ifndef SCRIPT_PARAM_H
#define SCRIPT_PARAM_H

#include "Game/Modules/ScriptVar.h"
#include "Game/Modules/Function.h"

class ScriptParam
{		
	public:
		enum class Type
		{
			FUNCTION,   // Another function
			REFERENCE,  // A reference to a Script variable
			VALUE,      // A local value
			NULL_PARAM  // An "invalid" parameter
		};

	private:
		Type m_type;
		union
		{
			Function* m_function;
			ScriptVar* m_value;
		};

	protected:

	public:
		/**
		Constructs an invalid parameter. */
		ScriptParam();

		/**
		Constructs a function parameter. 
		@param function A pointer to a heap-allocated function */
		ScriptParam(Function* function);

		/**
		Constructs a value or reference parameter. 
		@param var A reference to the ScriptVar to use 
		@param bIsRef True if var should be stored as a reference rather than being copied */
		ScriptParam(ScriptVar& var, bool bIsRef);

		/**
		Copies the ScriptParam. Deep copies are performed on 'value' parameters. 
		@param other A const reference to the parameter to copy */
		ScriptParam(const ScriptParam& other);

		/**
		Assigns the value of the given ScriptParam to this ScriptParam. 
		@param other The ScriptParam to assign to this one */
		ScriptParam& operator=(const ScriptParam& other);

		/**
		Destructs the ScriptParam. */
		~ScriptParam();

		/**
		Returns the type of parameter. 
		@return The type of parameter */
		const Type& getType() const;

		/**
		Returns the type of the value that will be returned by this parameter on calls to getValue. 
		@return The type of the value that will be returned */
		const ScriptVar::SupportedTypes& getReturnType() const;

		/**
		Returns the value this ScriptParam holds. For function parameters the value must first be
		computed. 
		@param pack 
		@return The value */
		ScriptVar& getValue(ScriptInfoPack& pack);
};

#endif