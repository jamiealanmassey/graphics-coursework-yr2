#ifndef _EMPTY_BLOCK_H
#define _EMPTY_BLOCK_H

#include "drawable.h"

/**
 * \brief Special definition class that defines empty space
 * \details Stores and renders nothing, this class is important for air
 * \version 1.0
 * \author Jamie Massey
 * \date 28.11.2018
 */
class EmptyBlock : public Drawable {
public:
	/** EmptyBlock Constructor **/
	EmptyBlock() {};

	/** EmptyBlock Destructor **/
	~EmptyBlock() {};


	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override {}

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override {}

	/** Overrided update from Drawable::update() **/
	virtual void update() override {}
};

#endif // _EMPTY_BLOCK_H
