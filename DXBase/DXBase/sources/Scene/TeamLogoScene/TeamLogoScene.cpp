#include "TeamLogoScene.h"


TeamLogoScene::TeamLogoScene(SceneDataKeeper* keeper)
{
	isEnd_ = false;
	keeper_ = keeper;
	name_ = "TeamLogo";

}

TeamLogoScene::~TeamLogoScene() {}

void TeamLogoScene::start() {
	isEnd_ = false;

	timeCount = 3;

	// •`‰ææ‰æ–Ê‚ğ— ‰æ–Ê‚ÉƒZƒbƒg
	SetDrawScreen(DX_SCREEN_BACK);

}

void TeamLogoScene::update() {
	Time::GetInstance().update();

	timeCount -= Time::GetInstance().deltaTime();

	if (timeCount < 0) {
		isEnd_ = true;
	}
}


void TeamLogoScene::draw() const {

	DrawGraph(SCREEN_SIZE.x/2, SCREEN_SIZE.y/2, ResourceLoader::GetInstance().getTextureID(TextureID::TEAM_LOGO_TEX), TRUE);

}

void TeamLogoScene::end() {}

bool TeamLogoScene::isEnd() const {
	return isEnd_;
}

Scene TeamLogoScene::next() const {
	return Scene::MainMenu;
}
