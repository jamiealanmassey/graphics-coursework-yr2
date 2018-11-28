#ifndef _EMPTY_BLOCK_H
#define _EMPTY_BLOCK_H

#include "drawable.h"

class EmptyBlock : public Drawable {
public:
	EmptyBlock() {};
	~EmptyBlock() {};

	void initialise(Application* application) {};
	void draw(Application* application) {};
	void update(Application* application) {};
};

#endif // _EMPTY_BLOCK_H
