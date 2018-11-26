#ifndef _GRASS_BLOCK_H
#define _GRASS_BLOCK_H

#include "drawable.h"

class GrassBlock : public Drawable
{
public:
	GrassBlock();
	~GrassBlock();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;
};

#endif // _GRASS_BLOCK_H
