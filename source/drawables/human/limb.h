#ifndef _LIMB_H
#define _LIMB_H

#include "../drawable.h"

class Limb : public Drawable
{
public:
	Limb(GLfloat width, GLfloat height, GLfloat depth);
	~Limb();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;

private:
	GLfloat m_limbWidth;
	GLfloat m_limbHeight;
	GLfloat m_limbDepth;
};

#endif // _LIMB_H
