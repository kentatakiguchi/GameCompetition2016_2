#pragma once

#include <DxLib.h>

#include <unordered_map>
#include <vector>
#include "../../Math/Math.h"
#include "../../Actor/Person/Player/State/Base/ActionType.h"

class Animation2D {
public:
	// コンストラクタ
	Animation2D();
	// アニメーションの変更(速度のみ変更も可能)
	void change_param(int anim_num, float speed = 1.0f);
	// アニメーションの方向転換
	void change_dir_type(int anim_num, ActionType type);
	// アニメーションを元に戻す
	void back_to_pre_motion();
	// アニメーションの方向転換
	bool end_anim();
	// 更新処理
	void update(float deltaTime);
	// 描画
	// 座標,(軸),(拡大率),(回転角度(度数法)),
	void draw(Vector2 position, Vector2 origin = Vector2::Zero, float scale = 1, float degree = 0, Vector3 color = Vector3(255, 255, 255)) const;
	// 座標,軸,拡大率,回転角度(度数法),
	void draw(Vector2 position, Vector2 origin, Vector2 scale, float degree, Vector3 color = Vector3(255, 255, 255)) const;
protected:
	//分割前の画像id
	int id_;
	//現在のアニメーション
	int anim_num_;
	//
	int frame_;

	int pre_anim_;

	int pre_speed_;

	//アニメーションの再生時間
	float timer_;
	//アニメーションの再生速度
	float speed_;
	
	ActionType type_stock_;
	ActionType type_;
	//分割後のid格納用多次元配列
	std::unordered_map<int, std::vector<int>> sprites_;
};