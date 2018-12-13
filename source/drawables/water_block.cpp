#include "water_block.h"
#include "../delta_time.h"

WaterBlock::WaterBlock()
{
}

WaterBlock::~WaterBlock()
{
}

void WaterBlock::initialise()
{
	// Instantiate all the textures we are going to need as unique_pointer's
	m_textures.emplace_back(std::make_unique<Texture>());

	// Load any required textures into memory
	m_textures[0].get()->loadTexture("../textures/blocks/water.png");

	m_vertices.push_back(Vertex( 0.5f, 0.45f,  0.5f)); // m_vertices[0]
	m_vertices.push_back(Vertex( 0.5f, 0.45f, -0.5f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, 0.45f, -0.5f)); // m_vertices[2]
	m_vertices.push_back(Vertex(-0.5f, 0.45f,  0.5f)); // m_vertices[3]

	// Setups UVs
	m_uvs[0] = Vector2(0.0f, 0.0f);
	m_uvs[1] = Vector2(0.5f, 0.0f);
	m_uvs[2] = Vector2(0.5f, 0.5f);
	m_uvs[3] = Vector2(0.0f, 0.5f);
	
	// Setup offset
	m_offset = Vector2(0.0f, 0.0f);
}

void WaterBlock::draw()
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();

	// Draw water face
	m_textures[0].get()->bind();
	glBegin(GL_POLYGON);
		glTexCoord2f(m_uvs[0].getX() + m_offset.getX(), m_uvs[0].getY() + m_offset.getY());
		m_vertices[0].assign();
		glTexCoord2f(m_uvs[1].getX() + m_offset.getX(), m_uvs[1].getY() + m_offset.getY());
		m_vertices[1].assign();
		glTexCoord2f(m_uvs[2].getX() + m_offset.getX(), m_uvs[2].getY() + m_offset.getY());
		m_vertices[2].assign();
		glTexCoord2f(m_uvs[3].getX() + m_offset.getX(), m_uvs[3].getY() + m_offset.getY());
		m_vertices[3].assign();
	glEnd();

	// Unbind remaining texture
	m_textures[0].get()->unbind();
	glPopMatrix();
}

void WaterBlock::update()
{
	m_offset += Vector2(0.1f, 0.15f) * DELTA_TIME_SECONDS;
	if (m_offset.getX() > 0.5f)
		m_offset = Vector2(0.0f, m_offset.getY());

	if (m_offset.getY() > 0.5f)
		m_offset = Vector2(m_offset.getX(), 0.0f);
}
