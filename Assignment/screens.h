#pragma once

#include "gameobject.h"
#include "level.h"
#include <string>
#include <sgg/graphics.h>

class Screens : public Level
{
	graphics::Brush m_brush_background;
	graphics::Brush text_brush;
	std::string message;
	//int sendToLevel;

public:
	void update(float dt) override;
	void draw() override;

	Screens(const std::string name, const std::string assetpath, const std::string message);
	//Screens(const std::string name, const std::string assetpath, const std::string message, const int l);		//dk if will be needed
	~Screens() override;

};