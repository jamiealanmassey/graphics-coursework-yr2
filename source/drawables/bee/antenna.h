#ifndef _ANTENNA_H
#define _ANTENNA_H

#include "../drawable.h"

class Antenna : public Drawable
{
public:
	Antenna();
	~Antenna();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;
};

#endif // _ANTENNA_H
