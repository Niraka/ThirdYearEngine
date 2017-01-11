/**
The GUI Module is responsible for the management of the GUI components. 

@author Nathan + Wade */

#ifndef GUI_MODULE_H
#define GUI_MODULE_H

#include <memory>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "System/Modules/WindowModule.h"
#include "System/Framework/Module.h"
#include "System/Modules/TimingModule.h"
#include "System/Modules/Renderable.h"
#include "System/Modules/ResourceModule.h"
#include "System/Services/LoggerService.h"
#include "System/Modules/WindowEventsManager.h"
#include "System/Utility/DirectoryListing.h"

#include "Scene/Modules/UIButton.h"
#include "Scene/Modules/UIImage.h"
#include "Scene/Modules/UIText.h"
#include "Scene/Modules/UILoader.h"
//
//#include <freetype\config\ftheader.h>
//#include <ft2build.h>
//#include FT_FREETYPE_H

class GUIModule :
	public Module,
	public Renderable,
	public InputListener,
	public WindowListener,
	public SceneManagerListener
{
	private:
		std::shared_ptr<TimingModule> m_timingModule;
		std::map<std::string, std::vector<std::shared_ptr<UIComponent>>> m_components;		//map of different GUIs
		std::shared_ptr<ResourceModule> m_resourceModule;
		std::shared_ptr<LoggerNode> m_loggerNode;
		std::shared_ptr<WindowModule> m_windowModule;
		int m_mouseX;
		int m_mouseY;
		std::string m_activeGUI;			//The GUI to currently render
		

	protected:
		/**
		Updates the GUIModule. */
		void onUpdate();

		/**
		Perform an action based on a button clicked
		@param buttonName The name of the button that was clicked
		*/
		void performButtonAction(std::string buttonName);
	public:
		/**
		Constructs a default GUIModule. */
		GUIModule();

		/**
		Destructs a GUIModule. */
		~GUIModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Adds a set of UIComponents to the GUIModule.
		@param idname A name for the new set
		@param component The component set to add */
		void addComponentSet(std::string idname, std::vector<std::shared_ptr<UIComponent>> component);
		
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
		Called by the TimingModule when a Timer expires. 
		@param sTimer The name of the expired timer */
		void onTimerExpired(std::string sTimer);

		/**
		Update the GUI Components based on the new mouse position
		@param fXPos The new X position of the cursor
		@param fYPos The new Y position of the cursor */
		void onCursorMoved(double fXPos, double fYPos);

		/**
		Perform click based actions to the GUIModule based on which button was pressed
		@param iButton The code of the pressed mouse button
		@param iMods The modifiers to apply to this mouse action*/
		void onMousePressed(int iButton, int iMods);

		/**
		Renders to the window. Use the shader manager to activate the correct shader.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations */
		void render(ShaderManager& shaderManager, const RenderData& data);

		/**
		Called when a depended service becomes available
		@param serviceName The service type that became available
		@param service A shared pointer to the service that became available*/
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		Called when a depended service becomes unavailable
		@param serviceName The service type that became unavailable */
		void serviceDependencyBecameUnavailable(Services serviceName);

		//FT_Library m_libray;		//The text libraray
		//FT_Face m_face;				//The font face
		//FT_GlyphSlot g;				//shortcut function

		/**
		Called when the active scene is changed
		@param sNewScene The name of the enw scene
		@param sOldScene The name of the old scene*/
		void onSceneChanged(std::string sNewScene, std::string sOldScene);

		/**
		Set the active UI to be displayed
		@param newUI The name of the UI to switch to */
		void setActiveUI(std::string newUI);

		/**
		Get the name of the currently active UI
		@return The name of the active UI, as a string */
		std::string getActiveUI();

		/**
		Called when the window is closed, to perform cleanup actions, etc. */
		void onWindowClose();

		/**
		Called when the window is resized
		@param iWidth The new window width
		@param iHeight The new window height */
		void onWindowResized(int iWidth, int iHeight);

		/**
		Called when the frame buffer is resized
		@param iWidth The new frame buffer width
		@param iHeight The new frame buffer height */
		void onFramebufferResized(int iWidth, int iHeight);

};

#endif