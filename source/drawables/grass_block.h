#ifndef _GRASS_BLOCK_H
#define _GRASS_BLOCK_H

#include "drawable.h"

class GrassBlock : public Drawable
{
public:
	GrassBlock();
	~GrassBlock();

	virtual void initialise() override;
	virtual void draw() override;
	virtual void update() override;
};

#endif // _GRASS_BLOCK_H
