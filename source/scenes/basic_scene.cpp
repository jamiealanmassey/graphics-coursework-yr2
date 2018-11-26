#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene(Application* application)
{
	application->setCameraLocation(-5.0f, 8.0f, -10.0f);
	application->setCameraTarget(8.0f, 0.0f, 8.0f);

	m_grassBlock = std::make_unique<GrassBlock>();
	m_grassBlock->initialise(application);

	m_texture0 = std::make_unique<Texture>();
	m_texture0.get()->loadTexture("../textures/floor.png");
}

void BasicScene::renderScene(Application* application)
{
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			m_grassBlock.get()->setTranslation(Vector3(x, 0.0f, z));
			m_grassBlock.get()->draw(application);
		}
	}

	for (int x = 0; x < 4; x++)
	{
		for (int z = 0; z < 4; z++)
		{
			m_grassBlock.get()->setTranslation(Vector3(x + 11.0f, 1.0f, z + 11.0f));
			m_grassBlock.get()->draw(application);
		}
	}

	/*m_texture0.get()->bind();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -0.5, 0.5); // v[3]
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, 0.5); // v[2]
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, 0.5); // v[1]
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, -0.5, 0.5); // v[0]
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, -0.5, -0.5); // v[7]
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, -0.5); // v[6]
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5, 0.5, 0.5); // v[2]
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5, -0.5, 0.5); // v[3]
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5, -0.5, 0.5); // v[0]
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5, 0.5, 0.5); // v[1]
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, -0.5); // v[5]
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, -0.5, -0.5); // v[4]
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5, 0.5, 0.5); // v[2]
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5, 0.5, -0.5); // v[6]
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5, 0.5, -0.5); // v[5]
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5, 0.5, 0.5); // v[1]
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
	m_texture0.get()->unbind();*/
}

void BasicScene::updateScene(Application * application)
{
}
