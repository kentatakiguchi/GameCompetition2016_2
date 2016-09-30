#include "MyGame.h"

MyGame::MyGame(){
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