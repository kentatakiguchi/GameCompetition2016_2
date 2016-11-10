#pragma once
#include "Math/Math.h"


//追加する定数は自分の名前の下に書いてください。
//競合が起こる可能性が高いので扱いには注意

/*** 矢嶋 ***/




/*** 片岡 ***/




/*** 宮内 ***/

const static float CHIPSIZE = 32;

const static float TURNLESS_FLOOR_SIZE = 2;



/*** 永野 ***/

/* ウインドウ系統 */

//// スクリーンのサイズ倍率
//const static float		SCREEN_RATE = 200;
// スクリーンのサイズ
const static Vector2	SCREEN_SIZE = Vector2(1920, 1080);
// スクリーンのアスペクト比
const static float		SCREEN_ASPECT = SCREEN_SIZE.x / SCREEN_SIZE.y;
// ウインドウの表示倍率(おそらくデバック時のみ)
const static float		WINDOW_RATE = 0.5f;
// ウインドウモードにするかしないか(TRUE : FALSE)
const static int		WINDOW_MODE = TRUE;

/* プレイヤーパラメータ系統 */

// プレイヤーの表示位置
const static Vector2	PLAYER_SCREEN_POSITION = Vector2(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.75f);
// プレイヤーの移動速度
const static float		PLAYER_SPEED = 3.0f;
// プレイヤーの本体の半径
const static float		PLAYER_RADIUS = 24.0f;
// プレイヤーの通常の長さ
const static float		PLAYER_MAX_NORMAL_LENGTH = 50.0f;
// プレイヤーが伸びた場合の最大値
const static float		PLAYER_MAX_STRETCH_LENGTH = 100.0f;
// プレイヤーの発射速度
const static float		PLAYER_LAUNCH_POWER = 50.0f;
// プレイヤーのジャンプ速度
const static float		PLAYER_JUMP_POWER = 10.0f;





