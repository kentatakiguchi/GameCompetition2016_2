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

	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND1_TEX, "./resources/sprite/BackGraund1.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND2_TEX, "./resources/sprite/BackGraund2.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND3_TEX, "./resources/sprite/BackGraund3.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND4_TEX, "./resources/sprite/BackGraund4.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND12_TEX, "./resources/sprite/BackGraund12.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND22_TEX, "./resources/sprite/BackGraund22.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND32_TEX, "./resources/sprite/BackGraund32.png");
	//ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND42_TEX, "./resources/sprite/BackGraund42.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE11_TEX, "./resources/sprite/BackGraundTate11.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE21_TEX, "./resources/sprite/BackGraundTate21.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE31_TEX, "./resources/sprite/BackGraundTate31.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATE41_TEX, "./resources/sprite/BackGraundTate41.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TATEYOKO_TEX, "./resources/sprite/BackGraundTateYoko.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_BOT_TEX, "./resources/sprite/BackGraundBot.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TOP_TEX, "./resources/sprite/BackGraundTop.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_1_TEX, "./resources/sprite/BackGraund/Stage1-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_2_1_TEX, "./resources/sprite/BackGraund/Stage1-2-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_2_2_TEX, "./resources/sprite/BackGraund/Stage1-2-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_3_1_TEX, "./resources/sprite/BackGraund/Stage1-3-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_3_2_TEX, "./resources/sprite/BackGraund/Stage1-3-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_4_TEX, "./resources/sprite/BackGraund/Stage1-4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_5_TEX, "./resources/sprite/BackGraund/Stage1-5.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_6_TEX, "./resources/sprite/BackGraund/Stage1-6.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_7_TEX, "./resources/sprite/BackGraund/Stage1-7.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_8_1_TEX, "./resources/sprite/BackGraund/Stage1-8-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_8_2_TEX, "./resources/sprite/BackGraund/Stage1-8-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_9_TEX, "./resources/sprite/BackGraund/Stage1-9.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_EGGENEMY_WALK_TEX, "./resources/sprite/actor/enemy/Enemy01_Walk.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_EGGENEMY_DISCORVER_TEX, "./resources/sprite/actor/enemy/Enemy01_discorver.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_EGGENEMY_ATTACK_TEX, "./resources/sprite/actor/enemy/Enemy01_Attack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_EGGENEMY_ATTACKTURN_TEX, "./resources/sprite/actor/enemy/Enemy01_Attackturn.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_EGGENEMY_DAMAGE_TEX, "./resources/sprite/actor/enemy/Enemy01_damege.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_FLYINGENEMY_WALK_TEX, "./resources/sprite/actor/enemy/Enemy02_walk.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_FLYINGENEMY_ATTACK_TEX, "./resources/sprite/actor/enemy/Enemy02_attack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_FLYINGENEMY_DAMAGE_TEX, "./resources/sprite/actor/enemy/Enemy02_damege.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_NEEDLEENEMY_TEX, "./resources/sprite/actor/enemy/Enemy03.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_WALLMOVEENEMY_TEX, "./resources/sprite/actor/enemy/Enemy04_Left.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_NEEDLE_TEX, "./resources/sprite/Needle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_WEAPON_TEX, "./resources/sprite/EnemyWeapon.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_TEX, "./resources/sprite/Boss01.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_GAUGE_TEX, "./resources/sprite/BossGauge.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PUYO_TEST_TEX, "./resources/sprite/en1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PAUSE_BACK_TEX, "./resources/sprite/pauseBack.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP1_TEX, "./resources/sprite/chip1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP2_TEX, "./resources/sprite/chip2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP3_TEX, "./resources/sprite/chip3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP4_TEX, "./resources/sprite/chip4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SEGMENT_TRI_TEX, "./resources/sprite/segchip.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SELECT_TARGET_TEX, "./resources/sprite/SelTarget.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_ALPHA_TEX, "./resources/sprite/TextAlphaMask.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHANGE_SCENE_TEX, "./resources/sprite/ChangeS.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BLACK_BACK_TEX, "./resources/sprite/blackBack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK_TEX, "./resources/sprite/TitleBack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK2_TEX, "./resources/sprite/TitleBack2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK3_TEX, "./resources/sprite/TitleBack3.png");


	//プレイヤー関連のロード
	load_player_res();
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

void LoadingScene::load_player_res(){
	//butty
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_IDLE, "./resources/sprite/actor/player/butty/b_idle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_MOVE, "./resources/sprite/actor/player/butty/b_move.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_HOLD, "./resources/sprite/actor/player/butty/b_hold.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_SWIM, "./resources/sprite/actor/player/butty/b_swim.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_SWIM_TURN, "./resources/sprite/actor/player/butty/b_swimturn.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_DEATH, "./resources/sprite/actor/player/butty/b_death.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_DAMAGE, "./resources/sprite/actor/player/butty/b_damage.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_DIV_IDLE, "./resources/sprite/actor/player/butty/b_division_idle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_DIV_MOVE, "./resources/sprite/actor/player/butty/b_division_move.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_BUTTY_TURN, "./resources/sprite/actor/player/butty/b_turn.png");

	//retty
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_IDLE,		"./resources/sprite/actor/player/retty/r_idle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_MOVE,		"./resources/sprite/actor/player/retty/r_move.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_HOLD,		"./resources/sprite/actor/player/retty/r_hold.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_SWIM,		"./resources/sprite/actor/player/retty/r_swim.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_SWIM_TURN,"./resources/sprite/actor/player/retty/r_swimturn.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_DEATH,	"./resources/sprite/actor/player/retty/r_death.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_DAMAGE,	"./resources/sprite/actor/player/retty/r_damage.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_DIV_IDLE, "./resources/sprite/actor/player/retty/r_division_idle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_DIV_MOVE, "./resources/sprite/actor/player/retty/r_division_move.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_RETTY_TURN, "./resources/sprite/actor/player/retty/r_turn.png");
	
	//エフェクト
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_EFFECT_SEP_MOVE, "./resources/sprite/actor/effect/Separation_move.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PLAYER_EFFECT_SEP_EXP, "./resources/sprite/actor/effect/Separation.png");
}
