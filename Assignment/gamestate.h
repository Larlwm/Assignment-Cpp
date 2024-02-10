#pragma once

#include <string>

class GameState
{
private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	const float m_canvas_width = 20.0f;
	const float m_canvas_height = 10.0f;

	class Level* m_current_level = 0;
	class Player* m_player = 0;
	int m_level_counter = 0;

	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;

	bool m_debugging = false;

public:
	~GameState();
	void changeLevel(const std::string& levelName);
	void changeScreens(const std::string& screenName, const std::string assetpath, const std::string message);
	static GameState* getInstance();

	bool init();
	void draw();
	void update(float dt);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }
	//int setLevelCounter(int &n) { m_level_counter = n; }
	void setLevelCounter(const int& n) { m_level_counter = n; }
	void incrLevelCounter() { m_level_counter++; }
};