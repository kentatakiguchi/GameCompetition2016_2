#pragma once

#include <DxLib.h>

#include <vector>
#include "../Math/Math.h"

class Animation2D {
public:
	// コンストラクタ
	Animation2D();
	// コンストラクタ(画像id,横の分割数,縦の分割数)
	Animation2D(int id, int row, int column);
	// 画像を分割し配列に格納
	void registSprite();
	// アニメーションの変更(速度のみ変更も可能)
	void change(int anim_num, float speed = 1.0f);
	// 更新処理
	void update(float deltaTime);
	// 描画
	// 座標,(軸),(拡大率),(回転角度(度数法)),
	void draw(Vector2 position, Vector2 origin = Vector2::Zero, float scale = 1, float degree = 0) const;
	// 座標,軸,拡大率,回転角度(度数法),
	void draw(Vector2 position, Vector2 origin, Vector2 scale, float degree) const;
private:
	Vector2 getSize();
private:
	//分割前の画像id
	int id_;
	//現在のアニメーション
	int anim_num_;
	//行
	int row_;
	//列
	int column_;
	//アニメーションの再生時間
	float timer_;
	//アニメーションの再生速度
	float speed_;
	//分割後のid格納用多次元配列
	std::vector<std::vector<int>> sprites_;
};