#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();
	// 更新
	void update(float deltaTime);
	// 箱の動き方(壁なし)
	Vector3 boxMove();
	// 壁に沿った動き方（まだ）
	Vector3 wallMove();
	// 崖を避ける動き方
	Vector3 cliffMove();
	// 糸を使った動き方
	Vector3 threadMove();
	// プレイヤーとの距離を返します
	float getPlayerLength();
	// プレイヤーとの方向を単位ベクトルで取得します
	Vector2 getPlayerDirection();
	// プレイヤーとの方向を正規化されたベクトルで取得します
	Vector3 getPlayerNormalizeDirection();
	//　敵自身とプレイヤーの位置を入れます
	void setEMPosition(const Vector3& enemyPosition, const Vector3& playerPosition);

private:
	float timer_;				// 経過時間
	float deltaTimer_;			// 時間
	float boxMoveCount;			// 四角形移動カウント

	Vector3 enemyPosition_;		// 敵の位置
	Vector3 playerPosition_;	// プレイヤーの位置

	// 四角形移動用コンテナ
	typedef std::vector<float> BoxMoveConteiner;
	BoxMoveConteiner boxMoveConteiner_;
};

#endif