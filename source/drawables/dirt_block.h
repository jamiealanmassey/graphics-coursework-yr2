#ifndef _DIRT_BLOCK_H
#define _DIRT_BLOCK_H

#include "drawable.h"

class DirtBlock : public Drawable
{
public:
	DirtBlock();
	~DirtBlock();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;
};

#endif // _DIRT_BLOCK_H
