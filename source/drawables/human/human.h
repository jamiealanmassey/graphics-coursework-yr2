#ifndef _HUMAN_H
#define _HUMAN_H

#include "../drawable.h"

class Human : public Drawable
{
public:
	Human();
	~Human();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;

private:
	GLfloat m_currentRot;

	//Arm m_arms[2];
	//Leg m_legs[2];
	//Bee m_bee;
};

#endif // _HUMAN_H
