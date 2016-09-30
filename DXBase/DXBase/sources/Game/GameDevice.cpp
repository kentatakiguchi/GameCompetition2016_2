#include "GameDevice.h"

#include "../Scene/LoadingScene/LoadingScene.h"
#include "../Scene/Title/TitleScene.h"
#include "../Scene/GamePlay/GamePlayScene.h"
#include "../Scene/GameOver/GameOverScene.h"

GameDevice::GameDevice(){

}
GameDevice::~GameDevice(){

}

void GameDevice::start(){

	sceneMgr_.add(Scene::Loading, std::make_shared<LoadingScene>());
	sceneMgr_.add(Scene::Title, std::make_shared<TitleScene>());
	sceneMgr_.add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sceneMgr_.add(Scene::GameOver, std::make_shared<GameOverScene>());
	sceneMgr_.change(Scene::Loading);
}

void GameDevice::update(){
	sceneMgr_.update();
}

void GameDevice::draw(){
	sceneMgr_.draw();
}

void GameDevice::end(){
	sceneMgr_.end();
}