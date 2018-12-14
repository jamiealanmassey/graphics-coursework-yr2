#include "Block.h"

Block::Block(std::array<std::shared_ptr<Texture>, 3> m_textures) :
	Drawable()
{
	m_textureSide = m_textures[0];
	m_textureTop = m_textures[1];
	m_textureBottom = m_textures[2];
}

Block::~Block()
{
}

void Block::initialise()
{
	// Pre-store vertices that are going to be required to draw
	m_vertices.push_back(Vertex( 0.5f,  0.5f,  0.5f)); // m_vertices[0]
	m_vertices.push_back(Vertex(-0.5f,  0.5f,  0.5f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f)); // m_vertices[2]
	m_vertices.push_back(Vertex( 0.5f, -0.5f,  0.5f)); // m_vertices[3]
	m_vertices.push_back(Vertex( 0.5f,  0.5f, -0.5f)); // m_vertices[4]
	m_vertices.push_back(Vertex(-0.5f,  0.5f, -0.5f)); // m_vertices[5]
	m_vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f)); // m_vertices[6]
	m_vertices.push_back(Vertex( 0.5f, -0.5f, -0.5f)); // m_vertices[7]
}

void Block::draw()
{
	glPushMatrix();
	this->transform();

	// Draw Front Face using the "side texture"
	m_textureSide->bind();
	//new Normal(m_vertices)

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[0].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[1].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[2].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[3].assign();
	glEnd();

	// Draw the left face using the "side texture"
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[1].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[5].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[6].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[2].assign();
	glEnd();

	// Draw the right face using the "side texture"
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[4].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[0].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[3].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[7].assign();
	glEnd();

	// Draw the back face using the "side texture"
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[5].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[4].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[7].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[6].assign();
	glEnd();

	// Draw the top face using the "top texture"
	m_textureSide->unbind();
	m_textureTop->bind();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[0].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[4].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[5].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[1].assign();
	glEnd();

	// Draw the top face using the "bottom texture"
	m_textureTop->unbind();
	m_textureBottom->bind();
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	m_vertices[3].assign();
	glTexCoord2f(1.0f, 0.0f);
	m_vertices[2].assign();
	glTexCoord2f(1.0f, 1.0f);
	m_vertices[6].assign();
	glTexCoord2f(0.0f, 1.0f);
	m_vertices[7].assign();
	glEnd();

	// Unbind remaining texture
	m_textureBottom->unbind();
	glPopMatrix();
}

void Block::update()
{
}
