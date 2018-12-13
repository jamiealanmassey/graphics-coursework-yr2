#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <memory>

#include "../maths/colour.h"
#include "../maths/vector2.h"
#include "../maths/vector3.h"
#include "../texture.h"
#include "../application.h"

/**
 * \brief Abstract class describing drawable objects
 * \version 1.0
 * \author Jamie Massey
 * \date 25.11.2018
 */
class Drawable
{
public:
	/** Drawable Constructor **/
	Drawable();

	/** Drawable Destructor flushing m_uvs, m_vertices and m_textures **/
	~Drawable();

	/** Purely virtual function to be called when drawable is created **/
	virtual void initialise() = 0;

	/** Purely virtual function to be called when drawable is drawn **/
	virtual void draw() = 0;

	/** Purely virtual function to be called when drawable is updated **/
	virtual void update() = 0;

	/** Sets the current rotation of the drawable in relation to a defined axis
	 *
	 * \param angle Angle in degrees to rotate
	 * \param axis Axis to rotate about
	 */
	void setRotation(GLfloat angle, Vector3 axis);

	/**
	 * Sets the current translation of this whole object
	 *
	 * \param translation Desired Vector3 to translate by
	 */
	void setTranslation(Vector3 translation);

	/**
	 * Sets the current scale of this whole object
	 *
	 * \param scale Desired Vector3 to scale by
	 */
	void setScale(Vector3 scale);

	/**
	 * Sets the current colour of this whole object
	 *
	 * \param colour Desired Colour to be assigned before drawing
	 */
	void setColour(Colour colour);

	/** 
	 * Allows a definition of a UV set that can be used at draw time for mapping
	 * a texture to each face. This works best when there is a parent drawable that
	 * has a texture that it binds and you wish to draw from.
	 *
	 * \param uvs Collection of UVs that can be used in draw()
	 */
	void setUVS(std::vector<Vector2> uvs);

	/** \returns Current translation Vector **/
	Vector3 getTranslation() const;

	/** \returns Current scale Vector **/
	Vector3 getScale() const;

protected:
	/**
	 * Helper function that applies all relevant transformations to the whole drawable
	 * and any children of the drawable. This should usually be called between a glMatrixPush()
	 * and glMatrixPop() inside of this drawables Drawable.draw(Application)
	 */
	void transform();

protected:
	GLfloat m_rotation;		///< Desired rotation for the whole object
	Vector3 m_rotationAxis; ///< Desired axis to rotate about
	Vector3 m_translation;  ///< Translation to be applied to the whole drawable
	Vector3 m_scale;	    ///< Scale to be applied to the whole drawable
	Colour  m_colour;		///< Colour to be applied to the whole drawable

protected:
	std::vector<Vector2>				  m_uvs;	  ///< Collection of UVs to access in texturing
	std::vector<Vertex>					  m_vertices; ///< Collection of vertices to be used in drawing
	std::vector<std::unique_ptr<Texture>> m_textures; ///< Collection of Textures to be accessed in texturing
};

#endif // _ENTITY_H
