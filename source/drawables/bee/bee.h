#ifndef _BEE_H
#define _BEE_H

#include "../drawable.h"

class Bee : public Drawable
{
public:
	Bee();
	~Bee();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;

private:
	void drawBody();
	void drawHead();

private:
	GLfloat m_bodyWidth;
	GLfloat m_bodyHeight;
	GLfloat m_bodyDepth;
};

#endif // _BEE_H
