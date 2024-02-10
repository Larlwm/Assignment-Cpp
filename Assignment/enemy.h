#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

class Enemy : public Box, public GameObject
{
	std::vector<std::string> m_enemysprites;

	graphics::Brush m_brush_enemy;

public:
	float m_vy = .0f;

private:
	float m_gravity = 10.0f;
	float m_horizmove = 2.0f;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void toggleDirection();
	Enemy(std::string name, float x, float y);

protected:
	void debugDraw();
	void moveEnemy(float dt);

};