#include "world_parser.h"

WorldParser::WorldParser(std::string directory, std::string file)
{
	m_chunkSizeX = 0;
	m_chunkSizeY = 0;
	m_chunkSizeZ = 0;
	m_directory = directory;
	m_file = file;
}

WorldParser::~WorldParser()
{
	m_worldChunk.clear();
}

void WorldParser::parse()
{
	std::string line;
	std::ifstream worldFile(m_directory + m_file);
	if (worldFile.is_open())
	{
		while (std::getline(worldFile, line))
		{
			m_worldChunk.push_back(WorldPlane());
			parsePlane(line);
		}

		m_chunkSizeY = m_worldChunk.size();
		m_chunkSizeX = m_worldChunk.back().size();
		m_chunkSizeZ = m_worldChunk.back().back().size();
		worldFile.close();
	}
}

const WorldChunk WorldParser::getWorldChunk() const
{
	return m_worldChunk;
}

const int WorldParser::getChunkSizeX() const
{
	return m_chunkSizeX;
}

const int WorldParser::getChunkSizeY() const
{
	return m_chunkSizeY;
}

const int WorldParser::getChunkSizeZ() const
{
	return m_chunkSizeZ;
}

const Vector3 & WorldParser::getDimensions()
{
	return Vector3(m_chunkSizeX, m_chunkSizeY, m_chunkSizeZ);
}

void WorldParser::parsePlane(std::string planeFile)
{
	std::string line;
	std::ifstream file(m_directory + planeFile);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			m_worldChunk.back().push_back(WorldSegment());
			auto blocks = split(line);
			for (auto& block : blocks)
			{
				auto& plane = m_worldChunk.back();
				auto& segment = plane.back();
				segment.push_back(std::stoi(block));
			}
		}

		file.close();
	}
}

std::vector<std::string> WorldParser::split(const std::string & string)
{
	std::string token;
	std::vector<std::string> results;
	std::stringstream stream(string);
	while (std::getline(stream, token, ','))
		results.push_back(token);

	return results;
}
