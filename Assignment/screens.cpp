#include "gamestate.h"
#include "gameobject.h"
#include "screens.h"
#include <sgg/graphics.h>
#include "util.h"


void Screens::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	//draw Screen's background
	graphics::drawRect(w * 0.5f, h * 0.5, w * 1.5f, h * 1.0f, m_brush_background);
	graphics::drawText(m_state->getCanvasWidth() * 0.25f, m_state->getCanvasHeight() * 0.5, 1.0f, message, text_brush);

}


void Screens::update(float dt)
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		m_state->setLevelCounter(1);					//depending on the type of screen sends to 1st lvl/

	GameObject::update(dt);

}


Screens::Screens(const std::string name, const std::string assetpath, const std::string message)
{

	//sendToLevel = l;

	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath(assetpath);
	SETCOLOR(text_brush.fill_color, 1.0f, 0.5f, 0.0f);
	text_brush.fill_opacity = 1.0f;
	this->message = message;
	//graphics::drawText(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5, 3.0f, message, text_brush);

}


Screens::~Screens()
{
	//delete &m_brush_background;
	m_state->incrLevelCounter();

}