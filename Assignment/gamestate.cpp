#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "enemy.h"
#include "screens.h"			//Extra include, xreiazetai
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()						//main destructor i guess
{
	if (m_current_level)
		delete m_current_level;

	if (m_player)
		delete m_player;
		
}

void GameState::changeLevel(const std::string& levelName)			//(Prosthiki) Used to change level 
{
	if (m_current_level)
	{
		delete m_current_level;
		m_current_level = nullptr;
	}

		m_current_level = new Level(levelName);
		m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
}

void GameState::changeScreens(const std::string& name, const std::string assetpath, const std::string message)		//(Prosthiki) Used to change to main/death/victory screen
{
	if (m_current_level)
	{
		delete m_current_level;
		m_current_level = nullptr;
	}

	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	m_current_level = new Screens(name, assetpath, message);
	m_current_level->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

bool GameState::init()							//THIS IS WHERE I PUT THE LEVELS
{
	/*m_current_level = new Level("1.lvl");
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();*/

	/*m_current_level = new Screens("MainMenu", "menu.png", "Press Space to start game");
	m_current_level->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");			//Text font

	return true;
}

void GameState::draw()
{
	if (!m_current_level)
		return;
	else
		m_current_level->draw();


}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;

	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}

	if (!m_current_level)
		return;

	m_current_level->update(dt);

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	
	if (m_player != 0) {
		if (getPlayer()->m_pos_x > 8.0f) 						//EDW O DESTRUCTOR KAI GENIKA EDW OI ALLAGES LEVEL MALLON
			changeLevel("1.lvl");
	}

}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

GameState* GameState::m_unique_instance = nullptr;