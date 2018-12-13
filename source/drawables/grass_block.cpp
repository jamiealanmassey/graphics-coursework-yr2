#include "grass_block.h"

GrassBlock::GrassBlock() :
	Drawable()
{
}

GrassBlock::~GrassBlock()
{
	m_vertices.clear();
	m_textures.clear();
}

void GrassBlock::initialise()
{
	// Instantiate all the textures we are going to need as unique_pointer's
	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures.emplace_back(std::make_unique<Texture>());

	// Load any required textures into memory
	m_textures[0].get()->loadTexture("../textures/blocks/grass_side.jpg");
	m_textures[1].get()->loadTexture("../textures/blocks/grass_top.jpg");
	m_textures[2].get()->loadTexture("../textures/blocks/dirt.jpg");

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

void GrassBlock::draw()
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();

	// Draw Front Face using the "side texture"
	m_textures[0].get()->bind();
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
	m_textures[0].get()->unbind();
	m_textures[1].get()->bind();
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
	m_textures[1].get()->unbind();
	m_textures[2].get()->bind();
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
	m_textures[2].get()->unbind();
	glPopMatrix();
}

void GrassBlock::update()
{
}
