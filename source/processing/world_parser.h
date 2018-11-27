#ifndef _WORLD_PARSER_H
#define _WORLD_PARSER_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "../vector3.h"

typedef std::vector<int>		  WorldSegment;
typedef std::vector<WorldSegment> WorldPlane;
typedef std::vector<WorldPlane>   WorldChunk;

class WorldParser
{
public:
	WorldParser(std::string directory, std::string file);
	~WorldParser();

	void parse();

	const WorldChunk getWorldChunk() const;

	const int getChunkSizeX() const;
	const int getChunkSizeY() const;
	const int getChunkSizeZ() const;

	const Vector3& getDimensions();

private:
	void parsePlane(std::string planeFile);
	std::vector<std::string> split(const std::string& string);

private:
	int         m_chunkSizeX;
	int		    m_chunkSizeY;
	int		    m_chunkSizeZ;
	std::string m_directory;
	std::string m_file;
	WorldChunk  m_worldChunk;
};

#endif // _WORLD_PARSER_H
