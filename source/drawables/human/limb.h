#ifndef _LIMB_H
#define _LIMB_H

#include "../drawable.h"

/**
 * \brief Describes a limb (arm or leg) to be used by the Human
 * \version 1.0
 * \author Jamie Massey
 * \date 13.12.2018
 */
class Limb : public Drawable
{
public:
	/**
	 * Limb Constructor 
	 *
	 * \param width Width of the limb
	 * \param height Height of the limb
	 * \param depth Depth of the limb
	 **/
	Limb(GLfloat width, GLfloat height, GLfloat depth);

	/** Limb Destructor **/
	~Limb();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

private:
	GLfloat m_limbWidth;  ///< Dimension of the limb along the X-Axis
	GLfloat m_limbHeight; ///< Dimension of the limb along the Y-Axis
	GLfloat m_limbDepth;  ///< Dimension of the limb along the Z-Axis
};

#endif // _LIMB_H
