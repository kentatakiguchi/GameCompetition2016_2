#pragma once


enum class ModelID {
	PLAYER,
	ENEMY,
	STAGE,
	STAGE_COLL,
	SKYDOME
};

enum class TextureID {

	//背景画像
	BACKSTAGE1_1_TEX,
	BACKSTAGE1_2_TEX,
	BACKSTAGE1_3_TEX,
	BACKSTAGE1_4_TEX,
	BACKSTAGE1_5_TEX,
	BACKSTAGE1_6_1_TEX,
	BACKSTAGE1_6_2_TEX,
	BACKSTAGE1_7_TEX,
	BACKSTAGE1_8_TEX,

	MGR_BACKSTAGE1_1_TEX,
	MGR_BACKSTAGE1_2_TEX,
	MGR_BACKSTAGE1_3_TEX,
	MGR_BACKSTAGE1_4_TEX,
	MGR_BACKSTAGE1_5_TEX,
	MGR_BACKSTAGE1_6_1_TEX,
	MGR_BACKSTAGE1_6_2_TEX,
	MGR_BACKSTAGE1_7_TEX,
	MGR_BACKSTAGE1_8_TEX,

	BACKSTAGE2_1_TEX,
	BACKSTAGE2_2_TEX,
	BACKSTAGE2_3_TEX,
	BACKSTAGE2_4_TEX,
	BACKSTAGE2_5_TEX,
	BACKSTAGE2_6_TEX,
	BACKSTAGE2_7_TEX,
	BACKSTAGE2_8_TEX,
	BACKSTAGE2_9_TEX,
	BACKSTAGE2_10_TEX,
	BACKSTAGE2_TOP1_TEX,
	BACKSTAGE2_TOP2_TEX,
	BACKSTAGE2_TOP3_TEX,

	BACKSTAGE3_1_TEX,
	BACKSTAGE3_2_TEX,

	BACKSTAGE4_1_TEX,
	BACKSTAGE4_2_TEX,



	BACKGRAUND1_TEX,
	BACKGRAUND2_TEX,
	BACKGRAUND3_TEX,
	BACKGRAUND4_TEX,
	BACKGRAUND12_TEX,
	BACKGRAUND22_TEX,
	BACKGRAUND32_TEX,
	BACKGRAUND42_TEX,
	BACKGRAUND_BOT_TEX,
	BACKGRAUND_TOP_TEX,
	BACKGRAUND_TATE11_TEX,
	BACKGRAUND_TATE21_TEX,
	BACKGRAUND_TATE31_TEX,
	BACKGRAUND_TATE41_TEX,
	BACKGRAUND_TATEYOKO_TEX,
	PUYO_TEST_TEX,

	BOSS_GAUGE_IN_TEX,
	BOSS_GAUGE_OUT_TEX,
	BOSS_WING_TEX,
	ENEMY_NEEDLE_TEX,

	CHIP1_TEX,
	CHIP2_TEX,
	CHIP3_TEX,
	CHIP4_TEX,
	PAUSE_BACK_TEX,
	BLACK_BACK_TEX,
	SEGMENT_TRI_TEX,
	SEGMENT_TRI2_TEX,
	SELECT_TARGET_TEX,
	TEXT_ALPHA_TEX,
	CHANGE_SCENE_TEX,
	TITLE_BACK_TEX,
	TITLE_BACK2_TEX,
	TITLE_BACK3_TEX,
	TITLE_BACK4_TEX,
	TITLE_BACK_ALPHA_TEX,
	TEAM_LOGO_TEX,
	FLOOR_STAGE1_TEX,
	FLOOR_STAGE2_TEX,
	FLOOR_STAGE3_TEX,
	FLOOR_STAGE4_TEX,
	FLOOR_WOOD_TEX,
	FLOOR_STONE_TEX,
	FLOOR_SUB_TEX,
	MOVIEBACK_TEX,
	TEXT_CREDIT_TEX,
	TEXT_TITLE_TEX,
	TEXT_GAMEEND_TEX,
	TEXT_GAMESTART_TEX,
	TEXT_MARU_TEX,
	TEXT_MENUBACK_TEX,
	TEXT_NEXTSTAGE_TEX,
	TEXT_TUTORIAL_TEX,
	TEXT_GAMEOVER_TEX,
	TEXT_RETRY_TEX,
	CREDIT_TEX,
	PAUSE_CIRCLE_TEX,
	PAUSE_START_TEX,

	NUMBER_ZERO_TEX,
	NUMBER_ONE_TEX,
	NUMBER_TWO_TEX,
	NUMBER_THREE_TEX,
	NUMBER_FOUR_TEX,
	NUMBER_FIVE_TEX,
	NUMBER_SIX_TEX,
	NUMBER_SEVEN_TEX,
	NUMBER_EIGHT_TEX,
	NUMBER_NINE_TEX,

	TUTOREAL1_1_TXT_TEX,
	TUTOREAL1_2_TXT_TEX,
	TUTOREAL2_1_TXT_TEX,
	TUTOREAL2_2_TXT_TEX,
	TUTOREAL3_1_TXT_TEX,
	TUTOREAL3_2_TXT_TEX,
	TUTOREAL4_1_TXT_TEX,
	TUTOREAL4_2_TXT_TEX,
	TUTOREAL4_3_TXT_TEX,
	TUTOREAL_TIME_1_TEX,
	TUTOREAL_TIME_2_TEX,
	TUTOREAL_TIME_3_TEX,
	TUTOREAL_COUNT_1_TEX,
	TUTOREAL_COUNT_2_TEX,
	TUTOREAL_CLER_TEX,
	DOOR_STAY_TEX,
	DOOR_OPEN_TEX,
	TUTOREAL_BACK_TEX,
	STAGE_01_TEX,
	STAGE_02_TEX,
	STAGE_03_TEX,
	STAGE_04_TEX,

	HAPPA1_1_TEX,
	HAPPA1_2_TEX,
	HAPPA3_1_TEX,
	HAPPA3_2_TEX,

	ITEM_TEX,
	ITEM_MINUS_TEX,
	VASE_TEX,
	GOAL_TEX,
	HURRY_TEX,
	BUTTON_R1_PUSH_TEX,
	BUTTON_L1_PUSH_TEX,
	BUTTON_R1_UP_TEX,
	BUTTON_L1_UP_TEX,
	BOARD_NULL_TEX,
	BOARD_STAGE2_TEX,
	BOARD_STAGE3_TEX,
	BOARD_STAGE4_TEX,
	GAMEOVER_TEX,

	TEXT_COMBO2_TEX,
	TEXT_COMBO3_TEX,
	TEXT_COMBO4_TEX,
	TEXT_COMBO5_TEX,
	TEXT_CHARGETIME_TEX,
	TEXT_GETSTAR_TEX,
	TEXT_MAXCOMBO_TEX,
	TEXT_MINUS_MULT_TEX,
	TEXT_MULTIPLY_TEX,
	TEXT_NoENEMY_DEATH_TEX,
	TEXT_MINUS_STAR_COUNT_TEX,
	TEXT_STAR_COUNT_TEX,
	TEXT_DAMAGE_COUNT_TEX,
	TEXT_STICK_COUNT_TEX,
	TEXT_TOTAL_TEX,
	TEXT_WALK_BLOCK_COUNT_TEX,
	RESULT_BACL_TEX,
	KIRIKABU_TEX,
	HUKIDASI_TEX,
	NUMBERS_TEX
};

enum class AnimationID {
	LOADING,
	//？アニメーション
	HATENA,
	TEXT_STAGECLEAR_ANM_TEX,
	SCENE_CHANGE_SLIME_ANM,
	LORDING_SLIME_ANM,
	ITEM_ANM,
	ITEM_MINUS_ANM,
	//ドアアニメーション
	DOOR_OPEN,
	DOOR_CLOSE,
	//プレイヤーアニメーション（青）
	PLAYER_BUTTY_IDLE,
	PLAYER_BUTTY_MOVE,
	PLAYER_BUTTY_HOLD,
	PLAYER_BUTTY_SWIM,
	PLAYER_BUTTY_SWIM_TURN,
	PLAYER_BUTTY_DEATH,
	PLAYER_BUTTY_DAMAGE,
	PLAYER_BUTTY_DIV_IDLE,
	PLAYER_BUTTY_DIV_MOVE,
	PLAYER_BUTTY_TURN,
	//プレイヤーアニメーション（赤）
	PLAYER_RETTY_IDLE,
	PLAYER_RETTY_MOVE,
	PLAYER_RETTY_HOLD,
	PLAYER_RETTY_SWIM,
	PLAYER_RETTY_SWIM_TURN,
	PLAYER_RETTY_DEATH,
	PLAYER_RETTY_DAMAGE,
	PLAYER_RETTY_DIV_IDLE,
	PLAYER_RETTY_DIV_MOVE,
	PLAYER_RETTY_TURN,
	//エフェクト
	PLAYER_EFFECT_SEP_MOVE,
	PLAYER_EFFECT_SEP_EXP,
	PLAYER_EFFECT_SHOUGEKI,

	// エネミーアニメーション
	ENEMY_EGGENEMY_WALK_TEX,
	ENEMY_EGGENEMY_WALKTURN_TEX,
	ENEMY_EGGENEMY_DISCORVER_TEX,
	ENEMY_EGGENEMY_ATTACK_TEX,
	ENEMY_EGGENEMY_ATTACKTURN_TEX,
	ENEMY_EGGENEMY_DAMAGE_TEX,
	ENEMY_FLYINGENEMY_WALK_TEX,
	ENEMY_FLYINGENEMY_ATTACK_TEX,
	ENEMY_FLYINGENEMY_DAMAGE_TEX,
	ENEMY_NEEDLEENEMY_TEX,
	ENEMY_WALLMOVEENEMY_TEX,
	// エネミーエフェクト
	ENEMY_EFFECT_COLLIDE_TEX,
	ENEMY_EFFECT_DEAD_TEX,

	// ボスアニメーション
	BOSS_WAIT_TEX,
	BOSS_WAIT_TURN_TEX,
	BOSS_JUMP_UP_TEX,
	BOSS_JUMP_DOWN_TEX,
	BOSS_WALLATTACK_DASH_TEX,
	BOSS_WALLATTACK_DASHJUMP_TEX,
	BOSS_WALLATTACK_DASHJUMP_STOP_TEX,
	BOSS_BREATH_TEX,
	BOSS_BREATH_TURN_TEX,
	BOSS_BREATH_DYSFUNCTION_TEX,
	BOSS_BREATH_LESS_TEX,
	BOSS_PIYO_TEX,
	BOSS_DAMAGE_TEX,
	BOSS_DAMAGE_BOKO_TEX,
	BOSS_DEATH_TEX,
	// ボスエフェクト
	BOSS_EFFECT_ATTACK_TEX,
	BOSS_EFFECT_BOKO_TEX,
	BOSS_EFFECT_DASH_TEX,
	BOSS_EFFECT_PIYO_TEX,
	// ボス攻撃エフェクト
	BOSS_EFFECT_ATTACK_SUIKOMI_30_TEX,
	BOSS_EFFECT_ENTRY_SIGN_TEX,

};

enum class SoundID {
	BGM_MENU,
	BGM_STAGE_123,
	BGM_STAGE_4,
	BGM_STAGE_5,
	SE_BUNRI,
	SE_NOBI,
	SE_NOBI_FULL,
	SE_PUYON,
	SE_SHOT,
	SE_SYOUTOTU,
	SE_ENEMY_HAKKEN,
	SE_ENEMY_HITSTOP,
	SE_ENEMY_DEAD,
	SE_BOSS_CHAKUCHI,
	SE_BOSS_DAMAGE,
	SE_BOSS_JUMP,
	SE_BOSS_WALLATTACK,
	SE_BOSS_DEAD,
	SE_BOSS_WIND,
	SE_BOSS_POKO,
	BGM_GAMEOVER,
	BGM_STAGECLEAR,
	SE_GETCOIN,
};
enum MOVIE_ID {
	TUTPREAL_01_MOVIE,
	TUTPREAL_02_MOVIE,
	TUTPREAL_03_MOVIE,
};
enum TXT_FILE_ID {
	STAGE01_TXT,
	STAGE02_TXT,
	STAGE03_TXT
};