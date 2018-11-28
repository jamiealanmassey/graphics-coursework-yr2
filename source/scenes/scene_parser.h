#ifndef _SCENE_PARSER_H
#define _SCENE_PARSER_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "../drawables/drawable.h"
#include "../drawables/grass_block.h"
#include "../drawables/empty_block.h"

#define BLOCK_EMPTY 0
#define BLOCK_GRASS 1

typedef std::vector<std::shared_ptr<Drawable>> WorldSegment;
typedef std::vector<WorldSegment>			   WorldPlane;
typedef std::vector<WorldPlane>				   WorldChunk;

// TODO: Change nested vectors to contain fixed Arrays instead (can base this by preprocessing files and then parsing data)
class SceneParser
{
public:
	SceneParser(std::string directory, std::string file);
	~SceneParser();

	void parse();

	const WorldChunk getWorldChunk() const;
	const std::vector<std::shared_ptr<Drawable>> getDrawables() const;

	const int getChunkSizeX() const;
	const int getChunkSizeY() const;
	const int getChunkSizeZ() const;

	const Vector3& getDimensions();

private:
	void parsePlane(std::string planeFile);
	std::vector<std::string> split(const std::string& string);

private:
	int									   m_chunkSizeX;
	int									   m_chunkSizeY;
	int									   m_chunkSizeZ;
	WorldChunk							   m_worldChunk;
	std::string							   m_directory;
	std::string							   m_file;
	std::vector<std::shared_ptr<Drawable>> m_drawables;
};

#endif // _SCENE_PARSER_H
