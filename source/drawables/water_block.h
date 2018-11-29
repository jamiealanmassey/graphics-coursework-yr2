#ifndef _WATER_BLOCK_H
#define _WATER_BLOCK_H

#include "drawable.h"

class WaterBlock : public Drawable
{
public:
	WaterBlock();
	~WaterBlock();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;
};

#endif // _WATER_BLOCK_H
