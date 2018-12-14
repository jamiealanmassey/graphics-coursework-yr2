#ifndef _SCENE_PARSER_H
#define _SCENE_PARSER_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "../drawables/drawable.h"
#include "../drawables/block.h"
#include "../drawables/water_block.h"
#include "../drawables/empty_block.h"

#define BLOCK_EMPTY		 0
#define BLOCK_DIRT		 1
#define BLOCK_GRASS		 2
#define BLOCK_WATER		 3
#define BLOCK_TREE_TRUNK 4
#define BLOCK_TREE_LEAF  5

typedef std::vector<std::shared_ptr<Drawable>> WorldSegment;
typedef std::vector<WorldSegment>			   WorldPlane;
typedef std::vector<WorldPlane>				   WorldChunk;

/**
 * \brief Parser that can evaluate chunks and create a world
 * \details Reads in plaintext files as chunks to create planes in the world
 * \version 1.0
 * \author Jamie Massey
 * \date 28.11.2018
 */
class SceneParser
{
public:
	/**
	 * SceneParser Constructor
	 *
	 * \param directory Directory to load all files from (root and child chunks)
	 * \param file Root chunk file to navigate actual planes
	 **/
	SceneParser(std::string directory, std::string file);

	/** SceneParser Destructor **/
	~SceneParser();

	/** Parses the given chunk file and all its related files **/
	void parse();

	/** \returns High level world chunk that stores nested data representation **/
	const WorldChunk getWorldChunk() const;

	/** \returns All drawable blocks that have been parsed **/
	const std::vector<std::shared_ptr<Drawable>> getDrawables() const;

	/** \returns Dimension of world along Z-Axis (num blocks on X) **/
	const int getChunkSizeX() const;
	
	/** \returns Dimension of world along Y-Axis (num blocks on Y) **/
	const int getChunkSizeY() const;

	/** \returns Dimension of world along Z-Axis (num blocks on Z) **/
	const int getChunkSizeZ() const;

	/** \return x, y and z of world dimensions **/
	const Vector3& getDimensions();

private:
	/**
	 * Parses a plane (i.e. x, z of y) by creating blocks and incrementing axis 
	 * counters with help from split(std::string)
	 *
	 * \param planeFile file denoting the entire plane accessed from root chunk file
	 **/
	void parsePlane(std::string planeFile);

	/**
	 * Splits line using comma separation just like CSV file parsing, where
	 * each element represents a block in space along a row
	 *
	 * \param line line to be parsed by the scene parser
	 * \return Parsed elements that have been separated
	 **/
	std::vector<std::string> split(const std::string& line);

private:
	int									   m_chunkSizeX; ///< Number of blocks on the X-Axis
	int									   m_chunkSizeY; ///< Number of blocks on the Y-Axis
	int									   m_chunkSizeZ; ///< Number of blocks on the Z-Axis
	WorldChunk							   m_worldChunk; ///< Collection containing world blocks as a nested structure
	std::string							   m_directory;  ///< Directory specifying where to load chunks from
	std::string							   m_file;		 ///< File to load chunks from
	std::vector<std::shared_ptr<Drawable>> m_drawables;  ///< Drawable collection of objects
	std::vector<std::shared_ptr<Texture>>  m_textures;   ///< Stored textures to be accessed by blocks
};

#endif // _SCENE_PARSER_H
