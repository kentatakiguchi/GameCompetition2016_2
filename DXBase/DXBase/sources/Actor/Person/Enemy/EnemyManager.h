#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

//#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include <vector>
#include <map>

class FloorSearchPoint;

class EnemyManager{
public:
	EnemyManager(const Vector2 position, const Vector2& direction = Vector2(-1.0f, -1.0f));
	~EnemyManager();
	// 更新
	void update(float deltaTime);
	// 箱の動き方(壁なし)
	Vector2 boxMove();
	// 壁に沿った動き方（まだ）
	Vector2 wallMove();
	// 崖を避ける動き方
	Vector2 cliffMove(bool isFloor);
	// 糸を使った動き方
	Vector2 threadMove();
	// 指定したオブジェクトとの距離を返します
	float getLength(const Vector2& otherPosition);
	// プレイヤーとの距離を返します
	float getPlayerLength();
	// 敵からプレイヤーに伸ばしたベクトルを返します
	Vector2 getPlayerVector();
	// 指定したオブジェクトとの方向を単位ベクトルで取得します
	Vector2 getDirection(const Vector2& otherPosition);
	// プレイヤーとの方向を単位ベクトルで取得します
	Vector2 getPlayerDirection();
	// 指定したオブジェクトとの方向を、正規化されたベクトルで取得します
	Vector2 getNormalizeDirection(const Vector2& otherPosition);
	// プレイヤーとの方向を正規化されたベクトルで取得します
	Vector2 getPlayerNormalizeDirection();
	//　敵自身とプレイヤーの位置を入れます
	void setEMPosition(const Vector2& enemyPosition, const Vector2& playerPosition, const Vector2 direction);
	// 糸の支点の位置取得
	Vector2 getThreadPoint();
	// 捜索オブジェクトの設定
	void addFSP(FloorSearchPoint* fsp);
	// 壁に沿った動き方
	Vector2 getWallDirection();
	// 方向を決めるか
	void setIsDirection(bool isDirection);
	// 壁オブジェクトを回して、合計値を返します
	int eachWSPObj();
	// 指定した要素数の壁捜索オブジェクトを取得します
	FloorSearchPoint* getWSPObj(const int number);
	// mapに追加処理を行います
	void initWSPMap();
	// 壁移動の方向を決定するかを返します
	bool isDirecion();

private:
	int distance_;				// 方向
	int wspResult_;				// 壁移動に使う値の合計値
	int wCollideCount_;			// 壁に当たっているオブジェクトの数
	int wCollidePastCount_;		// 壁に当たっているオブジェクトの過去の数
	float timer_;				// 経過時間
	float deltaTimer_;			// 時間
	float boxMoveCount;			// 四角形移動カウント
	bool isDirection_;			// 方向を代入するか
	Vector2 enemyPosition_;		// 敵の位置
	Vector2 playerPosition_;	// プレイヤーの位置
	Vector2 threadPosition_;	// 糸の位置
	Vector2 enemyDirection_;
	Vector2 playerVector_;
	Vector2 wsDirection_;		// 壁移動時の方向

	// 四角形移動用コンテナ
	typedef std::vector<float> WallMoveConteiner;
	WallMoveConteiner wallMoveConteiner_;
	// 
	typedef std::vector<FloorSearchPoint*> WSPContainer;
	WSPContainer wspContainer_;
	// 素数コンテナ
	typedef std::vector<int> PrimeContainer;
	PrimeContainer primeContainer_;
	// map
	typedef std::map<int, Vector2> WSPDirectionMap;
	WSPDirectionMap wspDirectionMap_;

// 糸移動用
public:
	int threadLength_;
	float rotate_;
	float rotateSpeed_;
	float threadGravity_;
};

#endif