#ifndef _WATER_BLOCK_H
#define _WATER_BLOCK_H

#include "block.h"
#include "../maths/vector2.h"

/**
 * \brief Special extension of Block class
 * \details Overrides Block class to implement animated water using UV texture coordinates
 * \version 1.0
 * \author Jamie Massey
 * \date 29.11.2018
 */
class WaterBlock : public Block
{
public:
	/**
	 * WaterBlock Constructor
	 *
	 * \param textureWater shared pointer to the texture to render
	 */
	WaterBlock(std::shared_ptr<Texture> textureWater);

	/** WaterBlock Destructor **/
	~WaterBlock();

	/** Overrided initialisation from Drawable::initialise() **/
	virtual void initialise() override;

	/** Overrided draw from Drawable::draw() **/
	virtual void draw() override;

	/** Overrided update from Drawable::update() **/
	virtual void update() override;

private:
	const GLfloat* m_ambient;  ///< Ambient lighting for water
	const GLfloat* m_diffuse;  ///< Diffuse lighting for water
	const GLfloat* m_specular; ///< Specular lighting for water

private:
	Vector2					 m_offset;		 ///< Water offset for animation
	std::shared_ptr<Texture> m_textureWater; ///< Water texture to use
};

#endif // _WATER_BLOCK_H
