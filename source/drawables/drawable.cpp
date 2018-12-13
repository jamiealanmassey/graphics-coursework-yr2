#include "drawable.h"

Drawable::Drawable()
{
	m_rotation = 0.0f;
	m_rotationAxis = Vector3(0.0f, 1.0f, 0.0f);
	m_translation = Vector3(0.0f, 0.0f, 0.0f);
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_colour = Colour(1.0f, 1.0f, 1.0f);
}

Drawable::~Drawable()
{
	m_uvs.clear();
	m_vertices.clear();
	m_textures.clear();
}

void Drawable::setRotation(GLfloat angle, Vector3 axis)
{
	m_rotation = angle;
	m_rotationAxis = axis;
}

void Drawable::setTranslation(Vector3 translation)
{
	m_translation = translation;
}

void Drawable::setScale(Vector3 scale)
{
	m_scale = scale;
}

void Drawable::setScale(GLfloat scalar)
{
	m_scale = Vector3(scalar, scalar, scalar);
}

void Drawable::setColour(Colour colour)
{
	m_colour = colour;
}

void Drawable::setUVS(std::vector<Vector2> uvs)
{
	m_uvs = uvs;
}

Vector3 Drawable::getTranslation() const
{
	return m_translation;
}

Vector3 Drawable::getScale() const
{
	return m_scale;
}

void Drawable::transform()
{
	// Scale, Rotate and Transform object then set colour to white
	glTranslatef(m_translation.getX(), m_translation.getY(), m_translation.getZ());
	glRotatef(m_rotation, m_rotationAxis.getX(), m_rotationAxis.getY(), m_rotationAxis.getZ());
	glScalef(m_scale.getX(), m_scale.getY(), m_scale.getZ());
	m_colour.assign();
}
