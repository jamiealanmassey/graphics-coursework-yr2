#ifndef _BLOCK_H
#define _BLOCK_H

#include "drawable.h"
#include "../maths/normal.h"

#include <array>

/**
 * \brief Defines a generic block in the world scene
 * \details Can access textures passed from the world parser to draw a block
 * \version 1.0
 * \author Jamie Massey
 * \date 14.12.2018
 */
class Block : public Drawable
{
public:
	/** 
	 * Block Constructor 
	 *
	 * \param texturePath Directory of the texture to load for this Block
	 **/
	Block(std::array<std::shared_ptr<Texture>, 3> m_textures);

	/** Block Destructor **/
	~Block();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

private:
	std::shared_ptr<Texture> m_textureTop;    ///< Path of texture to load at top
	std::shared_ptr<Texture> m_textureSide;   ///< Path of texture to load at top
	std::shared_ptr<Texture> m_textureBottom; ///< Path of texture to load at top
};

#endif // _BLOCK_H
