#ifndef _GAME_DEVICE_H_
#define _GAME_DEVICE_H_

#include "DxLib.h"
#include "../Scene/Base/SceneMgr.h"

class GameDevice{
public:
	GameDevice();
	~GameDevice();
	void start();
	void update();
	void draw();
	void end();
private:
	// ÉRÉsÅ[ã÷é~
	GameDevice(const GameDevice& other) = delete;
	GameDevice& operator = (const GameDevice& other) = delete;
private:
	SceneMgr sceneMgr_;
};

#endif