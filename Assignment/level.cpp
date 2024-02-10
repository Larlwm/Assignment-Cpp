#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include "enemy.h"
#include <cmath>


void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::checkCollisions()
{
	
	/*for (auto& box : m_blocks)
	{
		if (m_state->getPlayer()->intersect(box))
			printf("*");
	}*/
	

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
		else if (offset = m_state->getPlayer()->intersectUp(block))
		{
			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy < -1.0f)
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}

	}

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}

	}

}

void Level::checkEnCollisions()
{
	
	for (auto& enemy : m_enemies)
	{
		for (auto& block : m_blocks)
		{
			float offset = 0.0f;
			if (offset = enemy.intersectDown(block))
			{
				enemy.m_pos_y += offset;
				enemy.m_vy = 0.0f;

				break;
			}
		}
	}

	for (auto& enemy : m_enemies)
	{
		for (auto& block : m_blocks)
		{
			float offset = 0.0f;
			if (offset = enemy.intersectSideways(block))
			{
				enemy.m_pos_x += offset;

				enemy.toggleDirection();
				break;
			}

		}
	}

	for (auto& enemy : m_enemies)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(enemy))
		{
			printf("0");
			m_state->getPlayer()->m_pos_x += offset;

			break;
		}

	}

	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end(); )				//Enemy death collision
	{
		if (m_state->getPlayer()->intersectDown(*enemy))
		{
			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("Metal2.wav"), 1.0f);
			enemy = m_enemies.erase(enemy);
			break;

		}
		else
			enemy++;
	}

} 

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->Player::update(dt);

	for (auto& enemy : m_enemies)						//elegxos Enemy isActive sthn update
	{
		if (enemy.isActive())
			enemy.update(dt);
	}

	checkCollisions();
	checkEnCollisions();

	GameObject::update(dt);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

	//draw background
	graphics::drawRect(offset_x, offset_y, 6.0f * w, 4.0f * w, m_brush_background);

	for (auto& enemy : m_enemies)						//elegxos Enemy isActive sthn draw
	{
		if (enemy.isActive())
			enemy.draw();
	}

	// draw player
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();



	// draw blocks

	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}
}

void Level::init()
{
	// Stage 1
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();


	// initialize some collidable blocks here.
	// normally, you should build a Block class 
	// and automate the process more.
	m_blocks.push_back(Box(5, 6, 1, 1));
	m_blocks.push_back(Box(4, 6, 1, 1));
	m_blocks.push_back(Box(3, 6, 1, 1));
	m_blocks.push_back(Box(2, 5, 1, 1));
	m_blocks.push_back(Box(6, 6, 1, 1));
	m_blocks.push_back(Box(7, 6, 1, 1));
	m_blocks.push_back(Box(7, 5, 1, 1));
	m_blocks.push_back(Box(3, 2, 1, 1));
	m_blocks.push_back(Box(4, 3, 1, 1));
	m_blocks.push_back(Box(10, 6, 1, 1));
	m_blocks.push_back(Box(12, 7, 1, 1));
	m_blocks.push_back(Box(4, 15, 1, 1));
	m_blocks.push_back(Box(8, 20, 1, 1));

	m_block_names.push_back("block8.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block7.png");
	m_block_names.push_back("block6.png");
	m_block_names.push_back("block10.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block2.png");
	m_block_names.push_back("block8.png");
	m_block_names.push_back("block3.png");
	m_block_names.push_back("block8.png");
	m_block_names.push_back("block3.png");
	m_block_names.push_back("block1.png");
	m_block_names.push_back("block7.png");

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

	m_enemies.push_back(Enemy("Enemy0", 4.0f, 5.0f));
	m_enemies.push_back(Enemy("Enemy0", 6.0f, 5.0f));
	m_enemies.push_back(Enemy("Enemy0", 5.0f, 5.0f));

}

bool Level::checkCheckpoint()
{
	if (fabs(m_state->getPlayer()->m_pos_x - checkpointPosX) <= checkpointRadius && fabs(m_state->getPlayer()->m_pos_y - checkpointPosY) <= checkpointRadius) {
		return true;
	}
	return false;
}

Level::Level(const std::string& name) : GameObject(name)
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");


}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;

	m_state->incrLevelCounter();
}