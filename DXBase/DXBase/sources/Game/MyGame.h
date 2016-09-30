#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "Game.h"
#include "GameDevice.h"

class MyGame : public Game{
public:
	MyGame();
	~MyGame();
	void start();
	void update();
	void draw();
	void end();
private:
	GameDevice gameDevice_;
};

#endif