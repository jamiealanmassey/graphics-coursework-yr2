#ifndef _EMPTY_BLOCK_H
#define _EMPTY_BLOCK_H

#include "drawable.h"

class EmptyBlock : public Drawable {
public:
	EmptyBlock() {};
	~EmptyBlock() {};

	void initialise() {};
	void draw() {};
	void update() {};
};

#endif // _EMPTY_BLOCK_H
