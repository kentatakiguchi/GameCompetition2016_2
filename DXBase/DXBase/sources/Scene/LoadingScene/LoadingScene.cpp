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
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_2_TEX, "./resources/sprite/BackGraund/Stage1-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_3_TEX, "./resources/sprite/BackGraund/Stage1-3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_4_TEX, "./resources/sprite/BackGraund/Stage1-4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_5_TEX, "./resources/sprite/BackGraund/Stage1-5.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_6_1_TEX, "./resources/sprite/BackGraund/Stage1-6-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_6_2_TEX, "./resources/sprite/BackGraund/Stage1-6-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_7_TEX, "./resources/sprite/BackGraund/Stage1-7.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE1_8_TEX, "./resources/sprite/BackGraund/Stage1-8.png");



	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_1_TEX, "./resources/sprite/BackGraund/Stage2-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_2_TEX, "./resources/sprite/BackGraund/Stage2-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_3_TEX, "./resources/sprite/BackGraund/Stage2-3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_4_TEX, "./resources/sprite/BackGraund/Stage2-4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_5_TEX, "./resources/sprite/BackGraund/Stage2-5.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_6_TEX, "./resources/sprite/BackGraund/Stage2-6.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_7_TEX, "./resources/sprite/BackGraund/Stage2-7.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_8_TEX, "./resources/sprite/BackGraund/Stage2-8.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_9_TEX, "./resources/sprite/BackGraund/Stage2-9.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_9_TEX, "./resources/sprite/BackGraund/Stage2-9.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_TOP_TEX, "./resources/sprite/BackGraund/Stage2-Top.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE3_1_TEX, "./resources/sprite/BackGraund/Stage3-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE3_2_TEX, "./resources/sprite/BackGraund/Stage3-2.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE4_1_TEX, "./resources/sprite/BackGraund/Stage4-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE4_2_TEX, "./resources/sprite/BackGraund/Stage4-2.png");
	
	ResourceLoader::GetInstance().loadTexture(TextureID::PUYO_TEST_TEX, "./resources/sprite/en1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PAUSE_BACK_TEX, "./resources/sprite/pauseBack.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_NEEDLE_TEX, "./resources/sprite/Needle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_WEAPON_TEX, "./resources/sprite/EnemyWeapon.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_TEX, "./resources/sprite/Boss01.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_GAUGE_TEX, "./resources/sprite/BossGauge.png");

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
	ResourceLoader::GetInstance().loadTexture(TextureID::TEAM_LOGO_TEX, "./resources/sprite/Logo.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE1_TEX, "./resources/sprite/Block/floor1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE2_TEX, "./resources/sprite/Block/floor2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE3_TEX, "./resources/sprite/Block/floor3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE4_TEX, "./resources/sprite/Block/floor4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_SUB_TEX, "./resources/sprite/Block/floorsub.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_WOOD_TEX, "./resources/sprite/Block/wood.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STONE_TEX, "./resources/sprite/Block/stone.png");


	//プレイヤー関連のロード
	load_player_res();
	load_enemy_res();
	load_boss_res();
	load_bgm_res();
	load_se_res();
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
	return Scene::Logo;
}

void LoadingScene::load_player_res(){
	//butty
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_IDLE,		"./resources/sprite/actor/player/butty/b_idle.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_MOVE,		"./resources/sprite/actor/player/butty/b_move.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_HOLD,		"./resources/sprite/actor/player/butty/b_hold.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_SWIM,		"./resources/sprite/actor/player/butty/b_swim.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_SWIM_TURN,"./resources/sprite/actor/player/butty/b_swimturn.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_DEATH,	"./resources/sprite/actor/player/butty/b_death.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_DAMAGE,	"./resources/sprite/actor/player/butty/b_damage.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_DIV_IDLE, "./resources/sprite/actor/player/butty/b_division_idle.png",256, 8, 2, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_DIV_MOVE, "./resources/sprite/actor/player/butty/b_division_move.png",256, 8, 2, 5);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_BUTTY_TURN,		"./resources/sprite/actor/player/butty/b_turn.png",			256, 8, 2, 5);
	//retty
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_IDLE,		"./resources/sprite/actor/player/retty/r_idle.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_MOVE,		"./resources/sprite/actor/player/retty/r_move.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_HOLD,		"./resources/sprite/actor/player/retty/r_hold.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_SWIM,		"./resources/sprite/actor/player/retty/r_swim.png",			256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_SWIM_TURN,"./resources/sprite/actor/player/retty/r_swimturn.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_DEATH,	"./resources/sprite/actor/player/retty/r_death.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_DAMAGE,	"./resources/sprite/actor/player/retty/r_damage.png",		256, 8, 2, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_DIV_IDLE, "./resources/sprite/actor/player/retty/r_division_idle.png",256, 8, 2, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_DIV_MOVE, "./resources/sprite/actor/player/retty/r_division_move.png",256, 8, 2, 5);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_RETTY_TURN,		"./resources/sprite/actor/player/retty/r_turn.png",			256, 8, 2, 5);

	//エフェクト
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_EFFECT_SEP_MOVE,"./resources/sprite/actor/effect/Separation_move.png",		256, 8, 6, 0);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_EFFECT_SEP_EXP, "./resources/sprite/actor/effect/Separation.png",			256, 7, 9, 6);
}

void LoadingScene::load_enemy_res(){
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_WALK_TEX, "./resources/sprite/actor/enemy/Enemy01_Walk.png", 256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_DISCORVER_TEX, "./resources/sprite/actor/enemy/Enemy01_discorver.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_ATTACK_TEX, "./resources/sprite/actor/enemy/Enemy01_Attack.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_ATTACKTURN_TEX, "./resources/sprite/actor/enemy/Enemy01_Attackturn.png", 256, 4, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_DAMAGE_TEX, "./resources/sprite/actor/enemy/Enemy01_damege.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_FLYINGENEMY_WALK_TEX, "./resources/sprite/actor/enemy/Enemy02_walk.png", 256, 8, 3, 3);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_FLYINGENEMY_ATTACK_TEX, "./resources/sprite/actor/enemy/Enemy02_attack.png", 256, 8, 2, 5);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_FLYINGENEMY_DAMAGE_TEX, "./resources/sprite/actor/enemy/Enemy02_damege.png", 256, 8, 3, 3);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_NEEDLEENEMY_TEX, "./resources/sprite/actor/enemy/Enemy03.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_WALLMOVEENEMY_TEX, "./resources/sprite/actor/enemy/Enemy04_Left.png", 256, 8, 4, 1);
}

void LoadingScene::load_boss_res(){
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_WAIT_TEX, "./resources/sprite/actor/boss/Boss_wait.png", 256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_WAIT_TURN_TEX, "./resources/sprite/actor/boss/Boss_wait_turn.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_JUMP_UP_TEX, "./resources/sprite/actor/boss/Boss_jumpUP.png", 256, 8, 3, 3);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_JUMP_DOWN_TEX, "./resources/sprite/actor/boss/Boss_jumpDOWN.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_WALLATTACK_DASH_TEX, "./resources/sprite/actor/boss/Boss_dash.png", 256, 8, 2, 5);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_WALLATTACK_DASHJUMP_TEX, "./resources/sprite/actor/boss/Boss_dashjump.png", 256, 8, 2, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_WALLATTACK_DASHJUMP_STOP_TEX, "./resources/sprite/actor/boss/Boss_dashjump_stop.png", 256, 8, 3, 3);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_BREATH_TEX, "./resources/sprite/actor/boss/Boss_3_move.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_BREATH_TURN_TEX, "./resources/sprite/actor/boss/Boss_3_turn.png", 256, 8, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_BREATH_DYSFUNCTION_TEX, "./resources/sprite/actor/boss/Boss_3_dysfunction.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_BREATH_LESS_TEX, "./resources/sprite/actor/boss/Boss_3_breath_less.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_PIYO_TEX, "./resources/sprite/actor/boss/Boss_piyo.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_DAMAGE_TEX, "./resources/sprite/actor/boss/Boss_damege.png", 256, 7, 2, 2);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_DAMAGE_BOKO_TEX, "./resources/sprite/actor/boss/Boss_damage_boko.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_DEATH_TEX, "./resources/sprite/actor/boss/Boss_deth.png", 256, 8, 4);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_ATTACK_TEX, "./resources/sprite/actor/boss/effect/boss_attack.png", Vector2(544, 416), 5, 6);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_BOKO_TEX, "./resources/sprite/actor/boss/effect/boss_boko.png", 512, 5, 6);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_DASH_TEX, "./resources/sprite/actor/boss/effect/dash.png", 256, 9, 7);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_PIYO_TEX, "./resources/sprite/actor/boss/effect/piyori.png", 256, 8, 7);

}

void LoadingScene::load_bgm_res(){
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_MENU, "./resources/sounds/bgm/game_menuBGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_123, "./resources/sounds/bgm/stage1,2,3_BGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_4, "./resources/sounds/bgm/stage4_BGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_5, "./resources/sounds/bgm/stage5_BGM.mp3");

}

void LoadingScene::load_se_res(){
	ResourceLoader::GetInstance().loadSound(SoundID::SE_BUNRI, "./resources/sounds/bunri.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_NOBI, "./resources/sounds/nobi.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_NOBI_FULL, "./resources/sounds/nobi_full.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_PUYON, "./resources/sounds/puyon.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_SHOT, "./resources/sounds/shot.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_SYOUTOTU, "./resources/sounds/syoutotu.mp3");

	ResourceLoader::GetInstance().loadSound(SoundID::SE_HAKKEN, "./resources/sounds/enemy_hakkenn.mp3");
}
