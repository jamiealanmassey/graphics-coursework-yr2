#include "water_block.h"

WaterBlock::WaterBlock()
{
}

WaterBlock::~WaterBlock()
{
}

void WaterBlock::initialise(Application * application)
{
	// Instantiate all the textures we are going to need as unique_pointer's
	m_textures.emplace_back(std::make_unique<Texture>());

	// Load any required textures into memory
	m_textures[0].get()->loadTexture("../textures/blocks/water.jpg");

	m_vertices.push_back(Vertex( 0.5f, 0.5f,  0.5f)); // m_vertices[0]
	m_vertices.push_back(Vertex( 0.5f, 0.5f, -0.5f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, 0.5f, -0.5f)); // m_vertices[2]
	m_vertices.push_back(Vertex(-0.5f, 0.5f,  0.5f)); // m_vertices[3]
}

void WaterBlock::draw(Application * application)
{
}

void WaterBlock::update(Application * application)
{
}
