#ifndef _HUMAN_H
#define _HUMAN_H

#include "../drawable.h"
#include "limb.h"

class Human : public Drawable
{
public:
	Human();
	~Human();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;

private:
	void drawTorso();
	void drawHead();
	void setupArmUVs();
	void setupLegUVs();

private:
	GLfloat				  m_currentRot;
	std::unique_ptr<Limb> m_arms[2];
	std::unique_ptr<Limb> m_legs[2];
	//Bee m_bee;
};

#endif // _HUMAN_H
