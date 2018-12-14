#ifndef _BEE_H
#define _BEE_H

#include "../drawable.h"
#include "Leg.h"

/**
 * \brief Describes a complex bee object with animation
 * \version 1.0
 * \author Jamie Massey
 * \date 13.12.2018
 */
class Bee : public Drawable
{
public:
	/** Bee Constructor **/
	Bee();

	/** Bee destructor **/
	~Bee();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

	/** Get the state of the bee being attacked **/
	const GLboolean isAttacked() const;

	/** Set state of the bee being attacked **/
	void setAttacked(GLboolean flag);

private:
	/** Helper function that draws the body of the bee **/
	void drawBody();

	/** Helper function that draws the head of the bee **/
	void drawHead();

	/** Helper function to setup UV drawing of legs **/
	void setupLegUVs();

private:
	GLboolean			 m_attacked;   ///< Flag to denote if bee is being attacked
	GLfloat				 m_bodyWidth;  ///< Width of the bee
	GLfloat				 m_bodyHeight; ///< Height of the bee
	GLfloat				 m_bodyDepth;  ///< Depth of the bee body
	GLfloat				 m_rotation;   ///< Current facing direction of bee in degrees
	GLfloat				 m_pathSpeed;  ///< Speed at which bee follows path
	GLint				 m_pathNext;   ///< Current target node in the bee path
	Vector3*			 m_path;	   ///< Path for the bee to follow
	std::unique_ptr<Leg> m_legs[6];    ///< All legs of the bee
};

#endif // _BEE_H
