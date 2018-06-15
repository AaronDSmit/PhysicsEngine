#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D()
{

}

Application2D::~Application2D()
{

}

bool Application2D::startup()
{
	m_2dRenderer = new aie::Renderer2D();

	return true;
}

void Application2D::shutdown()
{
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime)
{
	// exit the application
	if (aie::Input::getInstance()->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw()
{
	clearScreen();

	m_2dRenderer->begin();

	m_2dRenderer->end();
}