/**
Physics module. 

@author Wade */

#ifndef PHYSICS_MODULE_H
#define PHYSICS_MODULE_H

#include "System/Framework/Module.h"
#include "Scene/Modules/PhysicsNode.h"
#include "System/Utility/MathsUtils.h"
#include <memory>
#include <array>
#include "System/Modules/TimingModule.h"
#include "System/Services/LoggerService.h"
#include "System\Utility\VectorSim.h"


enum HitRegionTypes;

class PhysicsModule: 
	public Module,
	public TimerListener
{
	private:
		std::map <std::string, std::shared_ptr<PhysicsNode>> m_PhysNodeHodler;		//!< Map to hold all the physics nodes in
		bool m_active;																//!< Are physics currently running?
		std::array<std::array<std::array<VectorSim<std::shared_ptr<PhysicsNode>>, 5>, 5>, 5> m_cubeGrid;		//!< A system that holds pointers to all physics nodes, keeping track of their grid co-ordinates in a virtual cube grid structure, when testing for collisions, checks should only be performed between nodes in the same or adjacent cube grid sections
		int m_mapMax;										//!< The maximum position of the map
		std::shared_ptr<TimingModule> m_timingModule;		//!< Pointer to the timing module
		float m_updateRate;									//!< The number of seconds between physics updates
		glm::vec3 m_maxPosition;							//!< The largest XYZ position any node can travel to
		glm::vec3 m_minPosition;							//!< The smallest XYZ position any node can trvael to
		

	protected:

	public:
		/**
		Construct a PhysicsModule
		*/
		PhysicsModule();

		/**
		Destruct a PhysicsModule
		*/
		~PhysicsModule();

		MathsUtils m_mathsUtils;			//!< A Maths utility object for all physics objects to use
		std::shared_ptr<LoggerNode> m_loggerNode;			//!< Node to report infor logs to

		/**
		Update the module */
		void onUpdate();

		/**
		Update all stored PhysicsNodes
		*/
		void updatePhysics();

		/** 
		Adds a physics node to the map of stored nodes
		@param idname The unique name of the new node
		@param mesh The mesh the new node is bound to
		@param hitReg The hit region type to use for the new node
		@param p The central position of the new node
		@param v The velocity of the new node
		@param maxS The maximum speed of the new node
		@param a The acceleration of the new node
		@param r The starting rotation of the node
		@param rv The starting rotational velocity of the node
		@param mov The starting moveable state of the node, defaults to true
		@param coll The starting collideable state of the node, defaults to true
		@return A shared pointer to the created node, or a nullptr if creation failed */
		std::shared_ptr<PhysicsNode> createNode(std::string idname, glm::vec3 exts, HitRegionTypes hitReg, glm::vec3 p, glm::vec3 v, float maxS, glm::vec3 a, glm::vec3 r, glm::vec3 rv, bool mov = true, bool coll = true);

		/*Set The current state of physics activity*/
		void setActive(bool act);

		/*Get the current state of physics activity*/
		bool getActive();

		/**
		Generate the cube grid for collision testing*/
		void generateCubeGrid();

		/**
		Get a pointer to the vector at a given position
		@param x The x grid co-ordinate
		@param y The y grid co-ordinate
		@param z The z grid co-ordinate
		@return A pointer to the vector of node pointers at the given position
		*/
		VectorSim<std::shared_ptr<PhysicsNode>>* getGridSqaure(int x, int y, int z);

		/**
		Get pointers to all the nodes relevant to the physNode (the nodes in adjacent or same cube grid squares)
		@param PhysNode The node to check against
		@return A vector of shared pointers to all the relevant nodes
		*/
		VectorSim<std::shared_ptr<PhysicsNode>> getReleventNodes(PhysicsNode* physNode);

		/**
		Called by the TimingModule when a Timer expires.
		@param sTimer The name of the expired timer */
		void onTimerExpired(std::string sTimer);

		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a
		static pointer cast.
		@param moduleName The name of the module
		@param module A shared pointer to the new module */
		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		void moduleDependencyBecameUnavailable(Modules moduleName);

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);

		/*
		@return The maximum XYZ position a node may go to*/
		glm::vec3 getMaxPos();

		/*
		@return The minimum XYZ position a node may go to*/
		glm::vec3 getMinPos();


};

#endif