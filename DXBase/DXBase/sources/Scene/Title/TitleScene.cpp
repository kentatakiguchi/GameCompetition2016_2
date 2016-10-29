#include "TitleScene.h"

TitleScene::TitleScene() :
	id(0) {
	isEnd_ = false;
}

TitleScene::~TitleScene(){}

void TitleScene::start() {
	isEnd_ = false;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
}

void TitleScene::update() {
	if (InputMgr::GetInstance().IsKeyUp(KeyCode::SPACE))isEnd_ = true;
}

void TitleScene::draw() const {
	DrawFormatString(375, 200, GetColor(255, 255, 255), "タイトル");
	DrawFormatString(300, 500, GetColor(255, 255, 255), "SPACEボタンでゲームスタート");	
}

void TitleScene::end() {}

bool TitleScene::isEnd() const {
	return isEnd_;
}

Scene TitleScene::next() const {
	return Scene::GamePlay;
}
