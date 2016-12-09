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
	// アニメーションの追加
	// (アニメーションのID, リソースID, 横の数, 縦の数, 横の数の減らる数)
	/*void addAnimation(
		EnemyAnimationID id, int res, int size, int row, int column, int surplus);*/
	void addAnimation(
		int id, int res, int size, int row, int column, int surplus = 0);
	// アニメーションの変更
	/*void changeAnimation(EnemyAnimationID id, float speed = 1.0f);*/
	void changeAnimation(int id, float speed = 1.0f);

	// アニメーションのが終わったかを返します
	bool isEndAnimation();

	// アニメーションのテクスチャを反転します
	void turnAnimation(int id);
};


#endif
