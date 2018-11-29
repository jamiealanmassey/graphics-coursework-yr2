#ifndef _DIRT_BLOCK_H
#define _DIRT_BLOCK_H

#include "drawable.h"

class DirtBlock : public Drawable
{
public:
	DirtBlock();
	~DirtBlock();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;
};

#endif // _DIRT_BLOCK_H
