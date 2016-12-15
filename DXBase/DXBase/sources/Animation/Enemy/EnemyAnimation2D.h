#ifndef ENMEY_ANIMATION2D_H_
#define ENMEY_ANIMATION2D_H_

#include "../Base/Animation2D.h"

#include <unordered_map>

//enum class EnemyAnimationID {
//	Idel,
//	Search,
//	Chase,
//	Attack,
//	Damage,
//	Dead
//};

class EnemyAnimation2D : public Animation2D {
//public:
//	enum class EnemyAnimationID {
//		Idel,
//		Search,
//		Chase,
//		Attack,
//		Damage,
//		Dead
//	};

public:
	EnemyAnimation2D();
	// 更新(自分のupdate)
	void onUpdate(float deltaTime);
	// アニメーションの追加
	// (アニメーションのID, リソースID, 横の数, 縦の数, 横の数の減らる数)
	void addAnimation(
		int id, int res, int size, int row, int column, int surplus = 0);
	// アニメーションの追加(サイズのX, Y指定)
	void addAnimation(
		int id, int res, Vector2 size, int row, int column, int surplus = 0);
	// アニメーションの変更
	void changeAnimation(int id, float speed = 1.0f);
	// アニメーションのが終わったかを返します
	bool isEndAnimation();
	// アニメーションのテクスチャを反転します
	void turnAnimation(int id, int direction);
	// アニメーションをループさせるかを設定します
	void setIsLoop(bool isLoop);

public:
	int prevFrame_;		// 1f前のフレーム
	bool isLoop_;		// ループするか
	bool isStop_;		// アニメーションを止めるか
};


#endif
