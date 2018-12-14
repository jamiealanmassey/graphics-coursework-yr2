#include "water_block.h"
#include "../delta_time.h"

WaterBlock::WaterBlock(std::shared_ptr<Texture> textureWater) :
	Block({ nullptr, nullptr, nullptr })
{
	m_textureWater = textureWater;
}

WaterBlock::~WaterBlock()
{
}

void WaterBlock::initialise()
{
	// Lighting
	m_ambient = new GLfloat[4]{ 0.8f, 0.8f, 0.8f, 1.0f };
	m_diffuse = new GLfloat[4]{ 0.6f, 0.6f, 0.6f, 1.0f };
	m_specular = new GLfloat[4]{ 0.5f, 0.5f, 0.8f, 1.0f };

	// Define vertices for drawing
	m_vertices.push_back(Vertex( 0.5f, 0.45f,  0.5f)); // m_vertices[0]
	m_vertices.push_back(Vertex( 0.5f, 0.45f, -0.5f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, 0.45f, -0.5f)); // m_vertices[2]
	m_vertices.push_back(Vertex(-0.5f, 0.45f,  0.5f)); // m_vertices[3]

	// Setups UVs
	m_uvs.push_back(Vector2(0.0f, 0.0f));
	m_uvs.push_back(Vector2(0.5f, 0.0f));
	m_uvs.push_back(Vector2(0.5f, 0.5f));
	m_uvs.push_back(Vector2(0.0f, 0.5f));
	
	// Setup offset
	m_offset = Vector2(0.0f, 0.0f);
}

void WaterBlock::draw()
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);

	// Draw water face
	m_textureWater->bind();
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
	m_textureWater->unbind();
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
