#include "LoadingScene.h"
#include "../../ResourceLoader/ResourceLoader.h"

#include "../../Define.h"
#include "../../ResourceLoader/Movie.h"

LoadingScene::LoadingScene(SceneDataKeeper* keeper):
isEnd_(false){
}

LoadingScene::~LoadingScene(){
	ResourceLoader::GetInstance().clearResources();
}

void LoadingScene::start(){

	//ここにローディング専用のリソースを読み込む
	ResourceLoader::GetInstance().loadTexture(TextureID::PUYO_TEST_TEX, "./resources/sprite/en1.png");
	ResourceLoader::GetInstance().loadAnimation(AnimationID::TEXT_STAGECLEAR_ANM_TEX, "./resources/sprite/Text/stageclear_anim.png", Vector2(640, 320), 6, 7, 2);
	//DerivationGraphと動画読み込みが非同期読み込みに対応していないため
	//プレイヤー関連のロード
	load_player_res();
	load_enemy_res();
	load_boss_res();
	//動画
	//Movie::GetInstance().Load(MOVIE_ID::TEST_MOVE, "./resources/Movie/Test.wmv");
	//Movie::GetInstance().Load(MOVIE_ID::TEST2_MOVIE, "./resources/Movie/Test2.avi");
	//非同期読み込みを開始
	SetUseASyncLoadFlag(TRUE);
	
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
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_10_TEX, "./resources/sprite/BackGraund/Stage2-10.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_TOP1_TEX, "./resources/sprite/BackGraund/Stage2-Top1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE2_TOP2_TEX, "./resources/sprite/BackGraund/Stage2-Top2.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::MOVIEBACK_TEX, "./resources/sprite/MovieBack.png");


	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE3_1_TEX, "./resources/sprite/BackGraund/Stage3-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE3_2_TEX, "./resources/sprite/BackGraund/Stage3-2.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE4_1_TEX, "./resources/sprite/BackGraund/Stage4-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKSTAGE4_2_TEX, "./resources/sprite/BackGraund/Stage4-2.png");
	
	ResourceLoader::GetInstance().loadTexture(TextureID::PAUSE_BACK_TEX, "./resources/sprite/pauseBack.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_NEEDLE_TEX, "./resources/sprite/Needle.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_WEAPON_TEX, "./resources/sprite/EnemyWeapon.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_TEX, "./resources/sprite/Boss01.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL1_1_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText1-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL1_2_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText1-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL2_1_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText2-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL2_2_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText2-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL3_1_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText3-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL3_2_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText3-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL4_1_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText4-1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL4_2_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText4-2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL4_3_TXT_TEX, "./resources/sprite/Tutoreal/TutorealText4-3.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL_TIME_1_TEX, "./resources/sprite/Tutoreal/TutorealTime1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL_TIME_2_TEX, "./resources/sprite/Tutoreal/TutorealTime2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL_TIME_3_TEX, "./resources/sprite/Tutoreal/TutorealTime3.png");

	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL_COUNT_1_TEX, "./resources/sprite/Tutoreal/TutorealCount1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TUTOREAL_COUNT_2_TEX, "./resources/sprite/Tutoreal/TutorealCount2.png");


	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_GAUGE_IN_TEX, "./resources/sprite/BossGaugeIn.png");


	ResourceLoader::GetInstance().loadTexture(TextureID::BOSS_GAUGE_OUT_TEX, "./resources/sprite/BossGaugeOut.png");


	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP1_TEX, "./resources/sprite/chip1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP2_TEX, "./resources/sprite/chip2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP3_TEX, "./resources/sprite/chip3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHIP4_TEX, "./resources/sprite/chip4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SEGMENT_TRI_TEX, "./resources/sprite/segchip.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SEGMENT_TRI2_TEX, "./resources/sprite/segchip2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::SELECT_TARGET_TEX, "./resources/sprite/SelTarget.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_ALPHA_TEX, "./resources/sprite/TextAlphaMask.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::CHANGE_SCENE_TEX, "./resources/sprite/ChangeS.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BLACK_BACK_TEX, "./resources/sprite/blackBack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK_TEX, "./resources/sprite/TitleBack.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK2_TEX, "./resources/sprite/TitleBack2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK3_TEX, "./resources/sprite/TitleBack3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK4_TEX, "./resources/sprite/TitleBack4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TITLE_BACK_ALPHA_TEX, "./resources/sprite/TitleBackAlpha.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEAM_LOGO_TEX, "./resources/sprite/Logo.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE1_TEX, "./resources/sprite/Block/floor1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE2_TEX, "./resources/sprite/Block/floor2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE3_TEX, "./resources/sprite/Block/floor3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STAGE4_TEX, "./resources/sprite/Block/floor4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_SUB_TEX, "./resources/sprite/Block/floorsub.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_WOOD_TEX, "./resources/sprite/Block/wood.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::FLOOR_STONE_TEX, "./resources/sprite/Block/stone.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_TITLE_TEX, "./resources/sprite/Text/title.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_CREDIT_TEX, "./resources/sprite/Text/credit.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_GAMEEND_TEX, "./resources/sprite/Text/gameend.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_GAMESTART_TEX, "./resources/sprite/Text/gamestart.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_MARU_TEX, "./resources/sprite/Text/maru.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_MENUBACK_TEX, "./resources/sprite/Text/menuback.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_NEXTSTAGE_TEX, "./resources/sprite/Text/nextstage.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_TUTORIAL_TEX, "./resources/sprite/Text/tutorial.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_GAMEOVER_TEX, "./resources/sprite/Text/gameover.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::TEXT_RETRY_TEX, "./resources/sprite/Text/retry.png");


	load_bgm_res();
	load_se_res();
	//非同期読み込み終了
	SetUseASyncLoadFlag(FALSE);


	//---Updateテスト用---
	mPosition = Vector2(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);
	isEnd_ = false;
	mAngle = 0;
	//---------
}

void LoadingScene::update(){
	mAngle += 10.0f*Time::GetInstance().deltaTime();
	//読み込み処理が終わっていたら
	if (GetASyncLoadNum()==0&&ProcessMessage()==0) {
		isEnd_ = true;
	}
}

void LoadingScene::draw() const{
	DrawRotaGraph(mPosition.x, mPosition.y,0.3f,mAngle, ResourceLoader::GetInstance().getTextureID(TextureID::PUYO_TEST_TEX), TRUE);
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
	ResourceLoader::GetInstance().loadAnimation(AnimationID::PLAYER_EFFECT_SHOUGEKI, "./resources/sprite/actor/effect/large_cell_256_256_syougeki_sun2.png", 256, 5, 5, 0);
}

void LoadingScene::load_enemy_res(){
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_WALK_TEX, "./resources/sprite/actor/enemy/Enemy01_Walk.png", 256, 8, 4, 1);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::ENEMY_EGGENEMY_WALKTURN_TEX, "./resources/sprite/actor/enemy/Enemy01_Walkturn.png", 256, 8, 2);
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
	//ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_ATTACK_TEX, "./resources/sprite/actor/boss/effect/boss_attack.png", Vector2(544, 416), 5, 6);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_ATTACK_TEX, "./resources/sprite/actor/boss/effect/large_cell_256_256_attack_star.png", 256, 5, 6);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_BOKO_TEX, "./resources/sprite/actor/boss/effect/boss_boko.png", 512, 5, 6);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_DASH_TEX, "./resources/sprite/actor/boss/effect/dash.png", 256, 9, 7);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_PIYO_TEX, "./resources/sprite/actor/boss/effect/piyori.png", 256, 8, 7);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_ATTACK_SUIKOMI_TEX, "./resources/sprite/actor/boss/effect/suikomi.png", Vector2(256, 512), 20, 24);
	ResourceLoader::GetInstance().loadAnimation(AnimationID::BOSS_EFFECT_ATTACK_SUIKOMI_30_TEX, "./resources/sprite/actor/boss/effect/suikomi_30.png", Vector2(256, 512), 5, 6);
}

void LoadingScene::load_bgm_res(){
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_MENU, "./resources/sounds/bgm/game_menuBGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_123, "./resources/sounds/bgm/stage1,2,3_BGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_4, "./resources/sounds/bgm/stage4_BGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGE_5, "./resources/sounds/bgm/stage5_BGM.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_STAGECLEAR, "./resources/sounds/menuse/stageClear.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::BGM_GAMEOVER, "./resources/sounds/menuse/gameover.mp3");

}

void LoadingScene::load_se_res(){
	ResourceLoader::GetInstance().loadSound(SoundID::SE_BUNRI, "./resources/sounds/bunri.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_NOBI, "./resources/sounds/nobi.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_NOBI_FULL, "./resources/sounds/nobi_full.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_PUYON, "./resources/sounds/puyon.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_SHOT, "./resources/sounds/shot.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_SYOUTOTU, "./resources/sounds/syoutotu.mp3");

	ResourceLoader::GetInstance().loadSound(SoundID::SE_HAKKEN, "./resources/sounds/enemy_hakkenn.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_BOSS_WIND, "./resources/sounds/boss/boss_wind.mp3");
	ResourceLoader::GetInstance().loadSound(SoundID::SE_BOSS_POKO, "./resources/sounds/boss/boss_poko.mp3");
}
