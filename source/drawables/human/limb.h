#ifndef _LIMB_H
#define _LIMB_H

#include "../drawable.h"

class Limb : public Drawable
{
public:
	Limb(GLfloat width, GLfloat height, GLfloat depth);
	~Limb();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;

private:
	GLfloat m_limbWidth;
	GLfloat m_limbHeight;
	GLfloat m_limbDepth;
};

#endif // _LIMB_H
