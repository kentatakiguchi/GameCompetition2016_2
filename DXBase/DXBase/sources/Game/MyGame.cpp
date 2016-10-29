#include "MyGame.h"
#include "../Define.h"

MyGame::MyGame() : Game(SCREEN_SIZE.x, SCREEN_SIZE.y, WINDOW_RATE, WINDOW_MODE){
}

MyGame::~MyGame(){
}

void MyGame::start(){
	gameDevice_.start();
}

void MyGame::update(){
	gameDevice_.update();
}

void MyGame::draw(){
	gameDevice_.draw();
}

void MyGame::end(){
	gameDevice_.end();
}