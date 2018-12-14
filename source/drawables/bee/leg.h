#ifndef _LEG_H
#define _LEG_H

#include "../drawable.h"

/**
 * \brief Describes a leg to be used by the Bee
 * \version 1.0
 * \author Jamie Massey
 * \date 13.12.2018
 */
class Leg : public Drawable
{
public:
	/** Leg Constructor **/
	Leg();

	/** leg Destructor **/
	~Leg();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

	/** 
	 * If set the leg will be flipped on the Y-Axis, mirroring it for use on
	 * the opposite side of the body.
	 *
	 * \param isFlipped Flag to set m_flipped to for use in transformations
	 **/
	void setFlipped(GLboolean isFlipped);

private:
	bool m_flipped; ///< Denotes if the leg should be mirrored for a different side of the body
};

#endif // _LEG_H
