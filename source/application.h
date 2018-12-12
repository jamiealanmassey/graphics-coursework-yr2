#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <functional>
#include <map>

#include "maths/vector3.h"
#include "maths/vertex.h"
#include "maths/colour.h"
#include "delta_time.h"

/**
 * \brief Describes the whole Application root
 * \details This singleton class is the core of the project and is where everything is stored
 *          and ran
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 */
class Application
{
public:
	/** C++0x standard to make sure we cannot ever call the constructor **/
	Application(Application const&) = delete;

	/** C++0x standard to make sure we cannot ever compare this object **/
	void operator=(Application const&) = delete;

private:
	/** Application Constructor **/
    Application();

	/** Application Destructor **/
    ~Application();

public:
	/** 
	 * Main entry point to the application and where everything will be initialised. Once done, we will kick
	 * into the core program loop of update, render, flip buffers, repeat.
	 *
	 * \param viewingMode specified mode to view in (windowed or fullscreen)
	 * \param width Width of the viewport we want to achieve
	 * \param height Height of the viewport we want to achieve
	 * \param windowTitle String representation of what to call our window
	 **/
    void run(GLint viewingMode, GLint width, GLint height, std::string windowTitle);

	/** Helper function that binds functions to glfw **/
	void bindFuncs();

	/** \returns True if 'X' key has been pressed **/
    const GLboolean isViewingX() const;

	/** \returns True if 'Y' key has been pressed **/
    const GLboolean isViewingY() const;

	/** \returns True if 'Z' key has been pressed **/
    const GLboolean isViewingZ() const;

	/** \returns True if any axis are currently viewing **/
    const GLboolean isViewingAxis() const;

	/** \returns Current distance that we are viewing from on the axis **/
    const GLfloat getViewingAxisDistance() const;

	/** \returns Maximum distance that we are allowed to view from on the axis **/
    const GLfloat getViewingAxisDistanceMax() const;

	/** \returns Minimum distance that we are allowed to view from on the axis **/
    const GLfloat getViewingAxisDistanceMin() const;

	/**
	 * Sets the minimum width that our window can be at any point.
	 *
	 * \param minWidth Window's minimum width in pixels
	 */
	void setWindowMinWidth(GLint minWidth);

	/**
	 * Sets the minimum height that our window can be at any point.
	 *
	 * \param minWidth Window's minimum height in pixels
	 */
	void setWindowMinHeight(GLint minHeight);
	
	/**
	 * Sets flag that denotes if we are curring viewing an axis
	 *
	 * \param state Desired state as a boolean
	 */
    void setViewingAxis(GLboolean state);

	/**
	 * Sets current viewing axis distance
	 *
	 * \param state Desired distance as a floating point value
	 */
    void setViewingAxisDistance(GLfloat distance);

	/**
	 * Sets the location of the camera to be updated next frame as denoted by
	 * some x, y, z components
	 *
	 * \param x Camera location on the X-Axis
	 * \param y Camera location on the Y-Axis
	 * \param z Camera location on the Z-Axis
	 */
	void setCameraLocation(GLfloat x, GLfloat y, GLfloat z);

	/**
	 * Sets the location of the camera to be updated next frame as denoted by
	 * some Vector3 object
	 *
	 * \param location Desired location represented by a Vector3
	 */
	void setCameraLocation(Vector3 location);

	/**
	 * Sets the target of the camera to be updated next frame as denoted by
	 * some x, y, z components
	 *
	 * \param x Camera target on the X-Axis
	 * \param y Camera target on the Y-Axis
	 * \param z Camera target on the Z-Axis
	 */
	void setCameraTarget(GLfloat x, GLfloat y, GLfloat z);

	/**
	 * Sets the target of the camera to be updated next frame as denoted by
	 * some Vector3 object
	 *
	 * \param location Desired target represented by a Vector3
	 */
	void setCameraTarget(Vector3 target);

	/** \returns A Map of key states where 'key' -> boolean state of the key (pressed or not) **/
	std::map<GLubyte, GLboolean> getKeyStates() const;

	/** \returns Singleton instance of this object **/
	static Application& instance();

protected:
	/** Updates the scene camera (depending on camera target, camera location and if we are viewing the axis or not **/
    void setSceneCamera();

	/** Draws the Axis lines if m_viewingAxis is true **/
    void drawAxisLines();

private:
	/** Helper function to initialise the Application **/
    void initialise();

	/** Helper function that will call to glfw to create a new window **/
    void createWindow();

	/** 
	 * Helper function that takes input of the mouse and propagates the message 
	 *
	 * \param button Button that has been pressed as an integer
	 * \param state Type of action that has been made
	 * \param x Position of the mouse on X-Axis
	 * \param y Position of the mouse on Y-Axis
	 **/
	void updateMouse(GLint button, GLint state, GLint x, GLint y);

	/** Helper function that updates aspects of the scene and propagates the message **/
	void updateScene();

	/** Helper function that updates the view matrix of the camera and calls to setSceneCamera() **/
    void updateCamera();

	/** Helper function that clears the screen and propogates rendering **/
	void renderFrame();
	
	/** 
	 * GLFW callback function for when the window is closed 
	 *
	 * \param window Reference to the GLFW window object
	 **/
	static void windowClose(GLFWwindow* window);

	/** 
	 * GLFW callback function for when a key has been pressed 
	 *
	 * \param window Reference to the GLFW window object
	 * \param key Key that has been pressed as an integer value
	 * \param scancode Special code for special keys
	 * \param action Action that has been made (pressed, released, repeated)
	 * \param modes Any modifiers to the key
	 **/
	static void keyboard(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);

	/**
	 * GLFW callback function for when the window has been resized by the user or otherwise
	 *
	 * \param window Reference to the GLFW window object
	 * \param width New width of the window in pixels
	 * \param height New height of the window in pixels
	 **/
	static void reshape(GLFWwindow* window, int width, int height);

public:
    static const GLenum FULLSCREEN = 0; ///< WindowMode for Fullscreen
    static const GLenum WINDOWED = 1;   ///< WindowMode for Windowed

public:
	std::function<void(Application*)>							  fp_initScene;			  ///< Function pointer for initialisation
	std::function<void(Application*)>							  fp_updateScene;	      ///< Function pointer for updating the scene
	std::function<void(Application*)>							  fp_renderScene;		  ///< Function pointer for rendering the scene
	std::function<void(Application*, GLint, GLint, GLint, GLint)> fp_updateSceneKeyboard; ///< Function pointer for keyboard input
	std::function<void(Application*, GLint, GLint, GLint, GLint)> fp_updateSceneMouse;	  ///< Function pointer for mouse input

protected:
	std::map<GLubyte, GLboolean> m_keyStates; ///< Stored Map of all current key states

protected:
	GLfloat m_cameraLocX;	 ///< Current location of the camera on the X-Axis
	GLfloat m_cameraLocY;	 ///< Current location of the camera on the Y-Axis
	GLfloat m_cameraLocZ;	 ///< Current location of the camera on the Z-Axis
	GLfloat m_cameraTargetX; ///< Where the camera is looking on the X-Axis
	GLfloat m_cameraTargetY; ///< Where the camera is looking on the Y-Axis
	GLfloat m_cameraTargetZ; ///< Where the camera is looking on the Z-Axis

private:
	GLboolean   m_running;				  ///< Flag denoting if the program is actually running
	GLboolean   m_viewingX;				  ///< Flag denoting if the X-Axis is being viewed
	GLboolean   m_viewingY;				  ///< Flag denoting if the Y-Axis is being viewed
	GLboolean   m_viewingZ;				  ///< Flag denoting if the Z-Axis is being viewed
	GLboolean   m_viewingAxis;			  ///< Flag denoting if any of m_viewingX, m_viewingY or m_viewingZ are active
    GLfloat     m_viewingAxisDistance;    ///< Distance that any active axis is viewed at
	GLfloat     m_viewingAxisDistanceMin; ///< Distance that axis can be viewed at minimum
	GLfloat     m_viewingAxisDistanceMax; ///< Distance that axis can be viewed at maximum
	GLfloat     m_hwRatio;				  ///< Ratio of the height to width
    GLint       m_viewingMode;			  ///< Current viewing mode
	GLint		m_windowWidth;			  ///< Current width of the window
	GLint		m_windowWidthMin;		  ///< Minimum width of the window
	GLint		m_windowHeight;			  ///< Current height of the window
	GLint		m_windowHeightMin;		  ///< Minimum height of the window
	GLFWwindow* m_window;				  ///< Reference to the window that has been created in createWindow()
    std::string m_windowTitle;			  ///< String representation of the window's title
};

#endif // _APPLICATION_H
