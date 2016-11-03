#pragma once
#include "Math/Math.h"


//MapChipの大きさを変更する
const static float CHIPSIZE = 32;

//追加する定数は自分の名前の下に書いてください。
//競合が起こる可能性が高いので扱いには注意

/*** 矢嶋 ***/




/*** 片岡 ***/




/*** 宮内 ***/




/*** 永野 ***/

/* ウインドウ系統 */

// スクリーンのアスペクト比
const static Vector2	SCREEN_ASPECT = Vector2(4, 3);
// スクリーンのサイズ倍率
const static float		SCREEN_RATE = 200;
// スクリーンのサイズ
const static Vector2	SCREEN_SIZE = SCREEN_ASPECT * SCREEN_RATE;
// ウインドウの表示倍率(おそらくデバック時のみ)
const static float		WINDOW_RATE = 1.0f;
// ウインドウモードにするかしないか(TRUE : FALSE)
const static int		WINDOW_MODE = TRUE;

/* プレイヤーパラメータ系統 */

// プレイヤーの移動速度
const static float		PLAYER_SPEED = 3.0f;
// プレイヤーの本体の半径
const static float		PLAYER_RADIUS = 16.0f;
// プレイヤーの通常の長さ
const static float		MAX_NORMAL_LENGTH = 50.0f;
// プレイヤーが伸びた場合の最大値
const static float		MAX_STRETCH_LENGTH = 100.0f;
// プレイヤーの発射速度
const static float		PLAYER_LAUNCH_POWER = 80.0f;





