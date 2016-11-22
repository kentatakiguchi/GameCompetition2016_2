#pragma once
#include "Math/Math.h"

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


//追加する定数は自分の名前の下に書いてください。
//競合が起こる可能性が高いので扱いには注意

/*** 矢嶋 ***/
const static Vector2	BOSSBODY_POSITION = Vector2(SCREEN_SIZE.x - 96 * 3, SCREEN_SIZE.y + 96 * 10);



/*** 片岡 ***/




/*** 宮内 ***/

const static float CHIPSIZE = 96;

const static float TURNLESS_FLOOR_SIZE = 1;

const static float RIGHTLEFTRANGE = 3;

const static float UPDOWNRANGE = 3;


/*** 永野 ***/



/* プレイヤーパラメータ系統 */
//プレイヤーのデフォルトの開始位置
static const Vector2 START_POS = Vector2(700, 1500);
// プレイヤーの表示位置
const static Vector2	PLAYER_SCREEN_POSITION = Vector2(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.75f);
// プレイヤーの移動速度
const static float		PLAYER_SPEED = 10.0f;
// プレイヤーの本体の半径
const static float		PLAYER_RADIUS = CHIPSIZE * 0.5f;
// プレイヤーの本体の衝突の半径
const static float		PLAYER_COLLIDER_RADIUS = PLAYER_RADIUS * 1.25f;
// プレイヤーの通常の長さ
const static float		PLAYER_MAX_NORMAL_LENGTH = CHIPSIZE * 2;
// プレイヤーが伸びた場合の最大値
const static float		PLAYER_MAX_STRETCH_LENGTH = CHIPSIZE * 4;
// プレイヤーの発射速度
const static float		PLAYER_LAUNCH_POWER = 140.0f;
// プレイヤーのジャンプ速度
const static float		PLAYER_JUMP_POWER = 30.0f;
// プレイヤーの仰け反り速度
const static float		PLAYER_LEANBACK_POWER = 10.0f;
// プレイヤーの無敵時間
const static float		PLAYER_INV_TIME = 3.0f;
// プレイヤーの死亡までの時間
const static float		PLAYER_DEAD_LIMIT = 5.0f;







