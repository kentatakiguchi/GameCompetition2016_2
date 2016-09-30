#include "GameOverScene.h"

GameOverScene::GameOverScene() :
	id(0) {
	isEnd_ = false;
}

GameOverScene::~GameOverScene(){

}

void GameOverScene::start() {
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	// �O���t�B�b�N�̃��[�h
	id = LoadGraph("./resources/Player.png");
}

void GameOverScene::update() {
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))	isEnd_ = true;
}

void GameOverScene::draw() const {
	DrawFormatString(375, 200, GetColor(255, 255, 255), "���U���g");
	DrawFormatString(300, 500, GetColor(255, 255, 255), "SPACE�{�^���Ń^�C�g����");
}

void GameOverScene::end() {

}

bool GameOverScene::isEnd() const {
	return isEnd_;
}

Scene GameOverScene::next() const {
	return Scene::Title;
}
