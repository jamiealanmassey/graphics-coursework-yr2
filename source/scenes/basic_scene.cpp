#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene(Application* application)
{
	m_texture0 = std::make_unique<Texture>();
	m_texture0.get()->loadTexture("../textures/floor.png");
}

void BasicScene::renderScene(Application* application)
{
	/*glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0, 0.5f);
	glEnd();*/

	m_texture0.get()->bind();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, -0.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, 0.5, 0.5);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, -0.5, 0.5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	m_texture0.get()->unbind();
}
