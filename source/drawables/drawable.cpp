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

void Drawable::transform()
{
	// Scale, Rotate and Transform object then set colour to white
	glScalef(m_scale.getX(), m_scale.getY(), m_scale.getZ());
	glRotatef(m_rotation, m_rotationAxis.getX(), m_rotationAxis.getY(), m_rotationAxis.getZ());
	glTranslatef(m_translation.getX(), m_translation.getY(), m_translation.getZ());
	m_colour.assign();
}
