#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(IWorld* world, const Vector3&  position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// 位置の設定
	void setPosition(Vector3 position);
	// 方向の設定
	void setDirection(int direction);
	// 敵の大きさを入れます
	void setEnemyScale(const Vector2 scale);
	// 床と当たったかを返します
	bool isFloor();

private:
	int direction_;			// 方向
	int turnCount_;			// 振り向き回数
	bool isFloor_;
	Vector2 enemyScale_;	// 敵の大きさ
	Vector2 vec2Position_;
};

#endif