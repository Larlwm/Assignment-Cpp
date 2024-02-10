#include "enemy.h"
#include "util.h"
#include <cmath>

Enemy::Enemy(std::string name, float x, float y)
{
	GameObject::m_name = name;
	Enemy::m_pos_x = x;
	Enemy::m_pos_y = y;
}

void Enemy::update(float dt)
{
	float delta_time = dt / 1000.0f;

	moveEnemy(dt);

	GameObject::update(dt);
}

void Enemy::draw()
{
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;

	//int sprite = (int)fmod(100.0f - m_pos_x * 9.0f, m_enemysprites.size());

	m_brush_enemy.texture = m_state->getFullAssetPath("TOAD.png");
	//SETCOLOR(m_brush_enemy.fill_color, 0.1f, 1.0f, 0.1f);
		m_brush_enemy.fill_opacity = 1.0f;
		m_brush_enemy.outline_opacity = 0.0f;
	graphics::drawRect;
	graphics::drawRect(x, y, 1.0f, 1.0f, m_brush_enemy);

	if (m_state->m_debugging)
		debugDraw();
}

void Enemy::init()
{

	m_brush_enemy.fill_opacity = 1.0f;
	m_brush_enemy.outline_opacity = 0.0f;
	//m_brush_enemy.texture = m_state->getFull
	// 
	// Path("enemy-idle.png");

	//m_enemysprites.push_back(m_state->getFullAssetPath("enemy-left0.png"));

}

void Enemy::debugDraw()
{

	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(x, y, m_width, m_height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(x - 0.4f, y - 0.6f, 0.15f, s, debug_brush);

}

void Enemy::moveEnemy(float dt)
{
	float delta_time = dt / 1000.0f;
	m_pos_x -= m_horizmove * delta_time;

	m_vy += m_gravity * delta_time;

	m_pos_y += m_vy * delta_time;
}

void Enemy::toggleDirection()
{
	float temp = -m_horizmove;
	m_horizmove = temp;

}