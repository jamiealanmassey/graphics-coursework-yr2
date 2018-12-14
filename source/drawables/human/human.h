#ifndef _HUMAN_H
#define _HUMAN_H

#include "../drawable.h"
#include "../bee/bee.h"
#include "limb.h"

/**
 * Defines the current state of the human (idling or running) as an
 * enumerator expression (0 or 1)
 */
enum eHumanState
{
	IDLE	= 0,
	RUNNING = 1,
};

/**
 * \brief Describes a complex human object with animation
 * \details This class allows the drawing of a human object in addition to Delta scaled animations, additonal limbs and
 *          the bee that is flying around them
 * \version 1.0
 * \author Jamie Massey
 * \date 13.12.2018
 */
class Human : public Drawable
{
public:
	/** Human Constructor **/
	Human();

	/** Human Destructor **/
	~Human();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

	/**
	 * Set the state of the human determining its interaction with the world and its
	 * current animation cycle (and resetting some variables based on m_stateLast)
	 *
	 * \param state New state of the human
	 **/
	void setState(eHumanState state);

private:
	/** Helper function that updates the animation of the Human and child drawables **/
	void updateAnimation();

	/** Helper function to follow a defined path when m_state == eHumanState::RUNNING **/
	void updatePath();

	/** Helper function to draw the torso of the Human called by Human::draw() **/
	void drawTorso();
	
	/** Helper function to draw the head of the Human called by Human::draw() **/
	void drawHead();

	/** Helper function that passes UV vertices for texture mapping child arms called in Human::initialise() **/
	void setupArmUVs();
	
	/** Helper function that passes UV vertices for texture mapping child legs called in Human::initialise() **/
	void setupLegUVs();

private:
	const GLfloat* m_humanAmbient;  ///< Ambient lighting for human
	const GLfloat* m_humanDiffuse;  ///< Diffuse lighting for human
	const GLfloat* m_humanSpecular; ///< Specular lighting for human

private:
	eHumanState			  m_state;		   ///< Finite state machine tracking human's state
	eHumanState			  m_stateLast;	   ///< Finite state machine denoting the state we were last in
	GLfloat				  m_currentRot;    ///< Current rotation of the whole human in local space
	GLfloat				  m_armSwayRot;	   ///< Current rotation of arms to sway back and forth
	GLfloat				  m_armSwayRotMax; ///< Maximum rotation allowed for arm sway
	GLfloat			      m_armSwaySpeed;  ///< Speed at which the arms sway
	GLfloat				  m_runningRot;    ///< Current rotation of the legs for running
	GLfloat				  m_runningRotMax; ///< Maximum rotation allowed for legs to move when running
	GLfloat				  m_runningSpeed;  ///< Speed at which the legs move when running
	GLfloat				  m_pathSpeed;	   ///< Speed at which the human follows the path
	GLint			      m_pathNext;	   ///< Current target for the human
	GLboolean			  m_armSwayDir;	   ///< Current direction of arm sway
	GLboolean			  m_runningDir;    ///< Current direction of legs moving
	GLboolean		      m_offsetDir;	   ///< Current direction of jumping
	GLboolean			  m_stoppedPress;  ///< Flag to track if the human is idling
	Vector3				  m_armPosition;   ///< Position of the arms relative to player
	Vector3               m_offset;		   ///< Current translation offset that is being applied
	Vector3				  m_offsetInitial; ///< Last known m_translation position before jumping
	Vector3               m_offsetLimit;   ///< Offset to aim for when jumping
	Vector3				  m_beeOffset;	   ///< Translation offset to set bee at
	Vector3*			  m_path;	       ///< Path for the human to follow
	Bee				      m_bee;		   ///< Bee that is flying around human
	std::unique_ptr<Limb> m_arms[2];	   ///< Both arms that are attached to this human stored uniquely in memory
	std::unique_ptr<Limb> m_legs[2];	   ///< Both legs that are attacjed to this human stored uniquely in memory
};

#endif // _HUMAN_H
