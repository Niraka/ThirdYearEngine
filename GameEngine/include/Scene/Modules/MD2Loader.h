#ifndef MD2LOADER_H
#define MD2LOADER_H

/*
With credit to David Henry
@class MD2Loader
* A class that can load md2 files
*/

class MD2Module;

class MD2Loader
{
	private:
		MD2Module* m_MD2Module;		//!< Pointer to the MD2 module to sent loaded models to

	protected:

	public:
		/**
		Default constructor*/
		MD2Loader();
		/**
		Destrucutor*/
		~MD2Loader();

		/**
		Construct an MD2 loader with given parameters
		@param MDMod The MD2Module to sent loaded models to*/
		MD2Loader(MD2Module* MDMod);

		/**
		Load MD2 data from a file
		@param filename	The filename of the file to load
		@param mdl A pointer to the model data object to load the model data into*/
		bool load(const char *filename, struct md2_model_t *mdl);

};

#endif