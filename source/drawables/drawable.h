#ifndef _ENTITY_H
#define _ENTITY_H

#include <vector>
#include <memory>

#include "../colour.h"
#include "../vector3.h"
#include "../texture.h"
#include "../application.h"

class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void initialise(Application* application) = 0;
	virtual void draw(Application* application) = 0;
	virtual void update(Application* application) = 0;

	void setRotation(GLfloat angle, Vector3 axis);
	void setTranslation(Vector3 translation);
	void setScale(Vector3 scale);

protected:
	void transform();

private:
	GLfloat m_rotation;
	Vector3 m_rotationAxis;
	Vector3 m_translation;
	Vector3 m_scale;
	Colour  m_colour;

protected:
	std::vector<Vertex>					  m_vertices;
	std::vector<std::unique_ptr<Texture>> m_textures;
};

#endif // _ENTITY_H