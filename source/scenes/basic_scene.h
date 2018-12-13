#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/grass_block.h"
#include "../drawables/human/human.h"
#include "scene_parser.h"

/**
 * \brief Scene containing all elements
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 *
 * Scene Graph:
 *  Scene Origin
 *  |
 *  +-- [T(block.x, block.y, block.z)] Blocks(0 .. *)
 *  |
 *  +-- [S(0.5, 0.5, 0.5) T(m_human.x, m_human.y, m_human.z)] Human
 *  |   |
 *  |   +-- [T(-0.65f, 0.0f, 0.0f)] Left Arm
 *	|   |
 *	|   +-- [T(0.65f, 0.0f, 0.0f)] Right Arm
 *  |   |
 *  |   +-- [T(-0.225f, -1.3f, 0.0f)] Left Leg
 *  |   |
 *  |   +-- [T(0.225f, -1.3f, 0.0f)] Right Leg
 *  |   |
 *  |   +-- [T()] Bee
 *	|		|
 *	|	    +-- [T()] Wing Left
 *	|		|
 *	|	    +-- [T()] Wing Right
 *	|		|
 *	|	    +-- [T()] Leg 1
 *	|		|
 *	|	    +-- [T()] Leg 2
 *	|		|
 *	|	    +-- [T()] Leg 3
 *	|		|
 *	|	    +-- [T()] Leg 4
 *	|		|
 *	|	    +-- [T()] Leg 5
 *	|		|
 *	|	    +-- [T()] Leg 6
 *	|		|
 *	|	    +-- [T()] Antenna Left
 *	|		|
 *	|	    +-- [T()] Antenna Right
 *  |       |
 *  |		+-- [T()] Stinger
 *  |
 *  +-- [T()] Scene Backdrop
 *
 */
class BasicScene
{
public:
	BasicScene();
	~BasicScene();

public:
	void initScene();
	void renderScene();
	void updateScene();

private:
	std::unique_ptr<SceneParser> m_sceneParser;
	std::unique_ptr<Human> m_human;
};

#endif // _BASIC_SCENE_H
