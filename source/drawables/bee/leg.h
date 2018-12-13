#ifndef _LEG_H
#define _LEG_H

#include "../drawable.h"

class Leg : public Drawable
{
public:
	Leg();
	~Leg();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;

	void setFlipped(GLboolean isFlipped);

private:
	bool m_flipped; ///< Denotes if the leg should be mirrored for a different side of the body
};

#endif // _LEG_H
