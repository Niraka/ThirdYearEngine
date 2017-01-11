/**
AI module. NOT IMPLEMENTED.

@author Austin */

#ifndef AI_MODULE_H
#define AI_MODULE_H

#include "System/Framework/Module.h"
#include "Scene/Modules/AINode.h"

class AIModule : public Module
{
	private:

	protected:
		void onUpdate();

	public:
		AIModule();
		~AIModule();

		bool start();

		bool stop();

};

#endif