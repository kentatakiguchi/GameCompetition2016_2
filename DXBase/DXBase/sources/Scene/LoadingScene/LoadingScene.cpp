#include "LoadingScene.h"
#include "../../ResourceLoader/ResourceLoader.h"

#include "../../Define.h"

LoadingScene::LoadingScene(SceneDataKeeper* keeper):
isEnd_(false){
}

LoadingScene::~LoadingScene(){
	ResourceLoader::GetInstance().clearResources();
}

void LoadingScene::start(){
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");

	isEnd_ = false;

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND1_TEX, "./resources/sprite/BackGraund1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND2_TEX, "./resources/sprite/BackGraund2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND3_TEX, "./resources/sprite/BackGraund3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND4_TEX, "./resources/sprite/BackGraund4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND12_TEX, "./resources/sprite/BackGraund12.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND22_TEX, "./resources/sprite/BackGraund22.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND32_TEX, "./resources/sprite/BackGraund32.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND42_TEX, "./resources/sprite/BackGraund42.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE11_TEX, "./resources/sprite/BackGraundTate11.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE21_TEX, "./resources/sprite/BackGraundTate21.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE31_TEX, "./resources/sprite/BackGraundTate31.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE41_TEX, "./resources/sprite/BackGraundTate41.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATEYOKO_TEX, "./resources/sprite/BackGraundTateYoko.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_BOT_TEX, "./resources/sprite/BackGraundBot.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TOP_TEX, "./resources/sprite/BackGraundTop.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_SAMPLE_TEX, "./resources/sprite/EnemySample.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_NEEDLE_TEX, "./resources/sprite/Needle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_WEAPON_TEX, "./resources/sprite/EnemyWeapon.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_TEX, "./resources/sprite/Boss01.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_GAUGE_TEX, "./resources/sprite/BossGauge.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PUYO_TEST_TEX, "./resources/sprite/en1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PAUSE_BACK_TEX, "./resources/sprite/pauseBack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_IDLE, "./resources/sprite/actor/player/b_wait.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_PUYOMI, "./resources/sprite/actor/player/ball.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP1_TEX, "./resources/sprite/chip1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP2_TEX, "./resources/sprite/chip2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP3_TEX, "./resources/sprite/chip3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP4_TEX, "./resources/sprite/chip4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SEGMENT_TRI_TEX, "./resources/sprite/segchip.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SELECT_TARGET_TEX, "./resources/sprite/SelTarget.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_ALPHA_TEX, "./resources/sprite/TextAlphaMask.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHANGE_SCENE_TEX, "./resources/sprite/ChangeS.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BLACK_BACK_TEX, "./resources/sprite/blackBack.png");

}

void LoadingScene::update(){
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");

	isEnd_ = true;
}

void LoadingScene::draw() const{
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");
}

void LoadingScene::end(){
}

bool LoadingScene::isEnd() const{
	return isEnd_;
}

Scene LoadingScene::next() const{
	return Scene::Title;
}
