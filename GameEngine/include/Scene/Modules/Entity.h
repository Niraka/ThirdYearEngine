/**
An Entity defines an object that exists within the world. 

Entities are component hosts, meaning that until they are assigned their components, they are essentially
without functionality. 

@author Nathan */

#ifndef ENTITY_H
#define ENTITY_H

#include "Scene/Modules/Actor.h"
#include "Scene/Modules/PhysicsNode.h"
#include "Scene/Modules/AINode.h"
#include "Scene/Modules/EntityToken.h"
#include "Scene/Modules/EntityMap.h"
#include "Scene/Modules/EntitySpecification.h"
#include "System/Modules/MovementMapping.h"
#include "System/Modules/MouseAction.h"
#include "System/Modules/KeyAction.h"
#include "System/Modules/Camera.h"
#include "System/Modules/SpotLight.h"
#include "System/Modules/PointLight.h"
#include "System/Modules/SoundNode.h"
#include "System/Utility/HasIndex.h"

class Entity :
	public Renderable,
	public HasIndex,
	public KeyAction,
	public MovementMapping
{
	public:
		enum class CameraModes
		{
			FIRST_PERSON,      // Looks in the direction the entity is
			THIRD_PERSON       // Follows the entity from behind
		};

		enum class SpotLightModes
		{
			FIRST_PERSON,      // Illuminates infront of the entity
			THIRD_PERSON       // Illuminates the back of the entity
		};

	private:
		const std::string m_sMoveForward;
		const std::string m_sMoveBackward;
		const std::string m_sMoveLeft;
		const std::string m_sMoveRight;
		const EntitySpecification m_buildSpec;
		EntityToken m_token;
		EntityMap* m_entityMap;
		std::shared_ptr<SoundNode> m_sound;
		std::shared_ptr<Actor> m_actor;
		std::shared_ptr<PhysicsNode> m_physics;
		std::shared_ptr<Camera> m_camera;
		std::shared_ptr<SpotLight> m_spotLight;
		std::shared_ptr<PointLight> m_pointLight;
		std::shared_ptr<AINode> m_aiNode;
		Entity::CameraModes m_cameraMode;
		Entity::SpotLightModes m_spotLightMode;

	protected:

	public:
		/**
		Constructs an Entity. */
		Entity();

		/**
		Constructs an Entity. 
		@param spec A reference to the EntitySpecification this Entity was built with */
		Entity(const EntitySpecification& spec);

		/**
		Destructs an Entity. */
		~Entity();

		/**
		Returns the EntitySpecification this Entity was built with. This value is only valid if the 
		'remember specification' setting is enabled via the EntityModule.
		@return An EntitySpecification */
		const EntitySpecification& getSpec() const;

		/**
		Returns a pointer to an EntityToken. Tokens are used to store basic information about an Entity
		in a way that minimises dependencies amongst classes. 
		@return A pointer to an EntityToken */
		EntityToken* getEntityToken();

		/**
		Sets the state of an EntityFlag. Flags are used to arbitrarily define properties associated an
		entity. By default all flags are set to false.
		@param flag The flag to set
		@param bValue The boolean value to assign to the flag */
		void setFlag(EntityFlags::Flags flag, bool bValue);
		
		/**
		Returns the boolean value associated with a given flag. Flags are used to arbitrarily define 
		properties associated anentity. By default all flags are set to false.
		@param flag The flag to set 
		@return The boolean value associated with the given flag, or false if the flag was invalid */
		bool getFlag(EntityFlags::Flags flag);
		
		/**
		Attaches a PointLight to this Entity, replacing any existing PointLight. Attaching a nullptr
		effectively removes the PointLight.
		@param light The PointLight to attach */
		void attachPointLight(std::shared_ptr<PointLight> light);

		/**
		Attaches a SpotLight to this Entity, replacing any existing SpotLight. Attaching a nullptr
		effectively removes the SpotLight.
		@param light The SpotLight to attach */
		void attachSpotLight(std::shared_ptr<SpotLight> light);

		/**
		Attaches a Camera to this Entity, replacing any existing Camera. Attaching a nullptr effectively
		removes the Camera. 
		@param camera The Camera to attach*/
		void attachCamera(std::shared_ptr<Camera> camera);

		/**
		Attaches an Actor component to this Entity, replacing any existing Actor. Attaching a nullptr
		effectively removes the Actor.
		@param actor The Actor component to attach */
		void attachActor(std::shared_ptr<Actor> actor);

		/**
		Attaches a PhysicsNode component to this Entity, replacing any existing PhysicsNode. Attaching a
		nullptr effectively removes the PhysicsNode. 
		@param node The PhysicsNode component to attach */
		void attachPhysicsNode(std::shared_ptr<PhysicsNode> node);

		/**
		Attaches a SoundNode component to this Entity, replacing any existing SoundNode. Attaching a
		nullptr effectively removes the SoundNode.
		@param node The SoundNode component to attach */
		void attachSoundNode(std::shared_ptr<SoundNode> node);

		/**
		Attaches an AINode component to this Entity, replacing any existing AINode. Attaching a
		nullptr effectively removes the AINode.
		@param node The AINode component to attach */
		void attachAINode(std::shared_ptr<AINode> node);

		/**
		Moves the Entity relative to its current position.
		@param distance The distance to move */
		void move(glm::vec3 distance);

		/**
		Sets the absolute position of the Entity.
		@param pos The position of the Entity */
		void setPosition(glm::vec3 pos);

		/**
		Retrieves the position of the Entity.
		@return The position of the Entity */
		glm::vec3 getPosition() const;

		/**
		Scales the Entity relative to its current scale.
		@param scale The scale to apply */
		void scale(glm::vec3 scale);

		/**
		Sets the absolute scale of the Entity.
		@param scale The scale of the Entity */
		void setScale(glm::vec3 scale);

		/**
		Retrieves the scale of the Entity.
		@return The scale of the Entity */
		glm::vec3 getScale() const;

		/**
		Rotates the Entity relative to its current orientation.
		@param rotation The rotation to apply */
		void rotate(glm::vec3 rotation);

		/**
		Sets the absolute orientation of the Entity.
		@param orientation The orientation of the Entity */
		void setOrientation(glm::vec3 orientation);

		/**
		Retrieves the orientation of the Entity.
		@return The orientation of the Entity */
		glm::vec3 getOrienation() const;

		/**
		Sets the visibility state of the Entity. Defaults to visible (true). 
		@param bVisible True to make the Entity visible, false to make it invisible */
		void setVisible(bool bVisible);

		/**
		Enables or disables looping on the Sound with the given name.
		@param sSoundName The name of the Sound to modify
		@param bLooping True to enable looping, false to disable */
		void setSoundLooping(const std::string& sSoundName, bool bLooping);

		/**
		Sets the minimum distance that the Sound will be heard at full volume. Take careful consideration
		of the size of the game world when using this function. Also consider that things like explosions
		will have a high value (several hundred), wheras footsteps will have a low value (sub-100).
		@param sSoundName The name of the sound to modify
		@param fDistance The minimum distance */
		void setSoundMinimumDistance(const std::string& sSoundName, float fDistance);

		/**
		Sets the Sounds attenuation level. Attenuation defines the falloff rate of the sounds volume. Note
		that this value is also dependant on world size (A large word requires smaller attenuation values).
		Values range between 0 (no falloff) and 100 (almost instant falloff).
		@param sSoundName The name of the sound to modify
		@param fAttenuation The attenuation level */
		void setSoundAttenuation(const std::string& sSoundName, float fAttenuation);

		/**
		Sets the SoundBuffer that the Sound with the given name will use. If Either the Sound or SoundBuffer
		could not be found, this function will fail.
		@param sSoundName The name of the Sound to bind to
		@param sBufferName The name of the SoundBuffer to bind
		@return True if the operation was successful, false otherwise */
		bool setSoundBuffer(const std::string& sSoundName, const std::string& sBufferName);

		/**
		Creates a Sound with the given name. The name must be unique amongst all other Sounds on this entity.
		The default settings of a sound are: 0 attenuation, non-looping, 0 minimum distance.
		@param sSoundName The name by which the Sound will be referred to
		@param sChannelName The name of the channel to bind the Sound to
		@return True if the Sound was created, false otherwise */
		bool createSound(const std::string& sSoundName, const std::string& sChannelName);

		/**
		Deletes a Sound with the given name.
		@param sSoundName The name of the Sound to delete */
		void deleteSound(const std::string& sSoundName);

		/**
		Stops the Sound with the given name. This function is really only useful for interrupting looping
		sounds.
		@param sSoundName The name of the Sound to stop */
		void stopSound(const std::string& sSoundName);

		/**
		Plays the Sound with the given name. If no such Sound existed or the Sound had no SoundBuffer, this
		function does nothing.
		@param sSoundName The name of the Sound to play */
		void playSound(const std::string& sSoundName);

		/**
		Renders to the window. Use the shader manager to activate the correct shader.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations */
		void render(ShaderManager& shaderManager, const RenderData& data);
		
		/**
		This function is called when an action is triggered by a bound key press/release.
		@param sActionName The name of the action that was triggered */
		void onAction(const std::string& sActionName);

		/**
		This function is called by a Scene when the mouse is moved.
		@param fX The mouse x position
		@param fY The mouse y position */
		void onMouseMoved(double fX, double fY);
};

#endif