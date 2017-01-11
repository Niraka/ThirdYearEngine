#ifndef MD2MODULE_H
#define MD2MODULE_H

#include "System/Framework/Module.h"
#include <map>
#include <string>
#include <memory>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Scene/Modules/anorms.h"
#include "System/Services/LoggerService.h"
#include "Scene\Modules\MD2Loader.h"
#include <glm\glm.hpp>

class MD2Model;

class MD2Module: public Module
{
	private:
		std::map<std::string, MD2Model*> m_models;		//!< Map of pointers to md2 models
		std::shared_ptr<LoggerNode> m_loggerNode;

	protected:

	public:
		/**
		Default constructor*/
		MD2Module();
		/**
		Destructor*/
		~MD2Module();
		/**
		Render each MD2 model
		*/
		void render();
		/**
		Update the MD2 models stored in the nmodule*/
		void update();
		/**
		Start the module*/
		bool start();
		/**
		Stop the module*/
		bool stop();
		
		/**/
		void onUpdate();

		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		void moduleDependencyBecameUnavailable(Modules moduleName);

		void serviceDependencyBecameUnavailable(Services serviceName);

		void createModel(std::string idName, const char modelFile);
};

#endif