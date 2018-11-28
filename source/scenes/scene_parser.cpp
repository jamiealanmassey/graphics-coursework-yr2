#include "scene_parser.h"

SceneParser::SceneParser(std::string directory, std::string file)
{
	m_chunkSizeX = 0;
	m_chunkSizeY = 0;
	m_chunkSizeZ = 0;
	m_directory = directory;
	m_file = file;
}

SceneParser::~SceneParser()
{
	m_drawables.clear();
	m_worldChunk.clear();
}

void SceneParser::parse()
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

const WorldChunk SceneParser::getWorldChunk() const
{
	return m_worldChunk;
}

const std::vector<std::shared_ptr<Drawable>> SceneParser::getDrawables() const
{
	return m_drawables;
}

const int SceneParser::getChunkSizeX() const
{
	return m_chunkSizeX;
}

const int SceneParser::getChunkSizeY() const
{
	return m_chunkSizeY;
}

const int SceneParser::getChunkSizeZ() const
{
	return m_chunkSizeZ;
}

const Vector3& SceneParser::getDimensions()
{
	return Vector3(m_chunkSizeX, m_chunkSizeY, m_chunkSizeZ);
}

void SceneParser::parsePlane(std::string planeFile)
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
				std::shared_ptr<Drawable> drawable;
				auto& plane = m_worldChunk.back();
				auto& segment = plane.back();
				auto type = std::stoi(block);
				
				if (type == BLOCK_GRASS)
					drawable = std::make_shared<GrassBlock>();
				else if (type == BLOCK_EMPTY)
					drawable = std::make_shared<EmptyBlock>();

				m_drawables.emplace_back(drawable);
				segment.emplace_back(drawable);
				drawable->setTranslation(Vector3(segment.size(), m_worldChunk.size(), plane.size()));
			}
		}

		file.close();
	}
}

std::vector<std::string> SceneParser::split(const std::string & string)
{
	std::string token;
	std::vector<std::string> results;
	std::stringstream stream(string);
	while (std::getline(stream, token, ','))
		results.push_back(token);

	return results;
}
