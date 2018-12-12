#ifndef _WATER_BLOCK_H
#define _WATER_BLOCK_H

#include "drawable.h"
#include "../maths/vector2.h"

class WaterBlock : public Drawable
{
public:
	WaterBlock();
	~WaterBlock();

	virtual void initialise(Application* application) override;
	virtual void draw(Application* application) override;
	virtual void update(Application* application) override;

private:
	Vector2 m_uvs[4];
	Vector2 m_offset;
};

#endif // _WATER_BLOCK_H
