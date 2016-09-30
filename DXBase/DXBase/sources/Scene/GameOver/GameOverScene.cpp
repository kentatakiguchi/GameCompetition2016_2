#include "GameOverScene.h"

GameOverScene::GameOverScene() :
	id(0) {
	isEnd_ = false;
}

GameOverScene::~GameOverScene(){

}

void GameOverScene::start() {
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード
	id = LoadGraph("./resources/Player.png");
}

void GameOverScene::update() {
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::SPACE))	isEnd_ = true;
}

void GameOverScene::draw() const {
	DrawFormatString(375, 200, GetColor(255, 255, 255), "リザルト");
	DrawFormatString(300, 500, GetColor(255, 255, 255), "SPACEボタンでタイトルへ");
}

void GameOverScene::end() {

}

bool GameOverScene::isEnd() const {
	return isEnd_;
}

Scene GameOverScene::next() const {
	return Scene::Title;
}
