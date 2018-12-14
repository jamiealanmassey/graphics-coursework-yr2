#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/human/human.h"
#include "scene_parser.h"

/**
 * \brief Scene containing all elements
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 *
 * TODO: Introduction stuff
 *
 * Scene Graph:
 *  Scene Origin
 *  |
 *  +-- [T(block.x, block.y, block.z)] Blocks(0 .. *)
 *  |
 *  +-- [S(0.5, 0.5, 0.5) T(Human.x, Human.y, Human.z)] Human
 *      |
 *      +-- [T(-Human.arm.x, Human.arm.y, Human.arm.z)] Left Arm
 *	    |
 *	    +-- [T(Human.arm.x, Human.arm.y, Human.arm.z)] Right Arm
 *      |
 *      +-- [T(-0.225f, -1.3f, 0.0f)] Left Leg
 *      |
 *      +-- [T(0.225f, -1.3f, 0.0f)] Right Leg
 *      |
 *      +-- [Ry(Bee.m_rotation) S(0.4f, 0.4f, 0.4f) T(Bee.x, Bee.y, Bee.z)] Bee
 *			|
 *		    +-- [Ry(90) S(0.2f, 0.2f, 0.2f) T(0.0f, -1.8f, -1,4f)] Leg 1
 *			|
 *		    +-- [Ry(90) S(0.2f, 0.2f, 0.2f) T(-3.0f, -1.8f, -1,4f)] Leg 2
 *			|
 *		    +-- [Ry(90) S(0.2f, 0.2f, 0.2f) T(3.0f, -1.8f, -1,4f)] Leg 3
 *			|
 *		    +-- [Ry(-90) S(0.2f, 0.2f, 0.2f) T(0.0f, -1.8f, -1,4f)] Leg 4
 *			|
 *		    +-- [Ry(-90) S(0.2f, 0.2f, 0.2f) T(-3.0f, -1.8f, -1,4f)] Leg 5
 *			|
 *		    +-- [Ry(-90) S(0.2f, 0.2f, 0.2f) T(3.0f, -1.8f, -1,4f)] Leg 6
 *
 */
class BasicScene
{
public:
	/** BasicScene Constructor **/
	BasicScene();

	/** BasicScene Destructor **/
	~BasicScene();

public:
	/** High level setup function to be called by Application singleton as function pointer **/
	void initScene();

	/** High level rendering function to be called by Application singleton as function pointer **/
	void renderScene();

	/** High level update function to be called by Application singleton as function pointer **/
	void updateScene();

private:
	std::unique_ptr<SceneParser> m_sceneParser; ///< Parsing object to load and draw world
	std::unique_ptr<Human>		 m_human;		///< Human that interacts with scene
};

#endif // _BASIC_SCENE_H
