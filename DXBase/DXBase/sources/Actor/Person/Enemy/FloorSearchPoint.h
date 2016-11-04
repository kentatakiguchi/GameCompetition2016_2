#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include "../../../Define.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(
		IWorld* world, 
		const Vector2& enemyPosition,
		const Vector2& addPosition, 
		const Vector2& bodyScale
		);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// 位置の設定
	void setPosition(const Vector2& position);
	// 方向の設定
	void setDirection(const Vector2& direction);
	// 敵の大きさを入れます
	void setEnemyScale(const Vector2& scale);
	// 床と当たったかを返します
	bool isFloor();
	bool isGround();
	// 床と当たった場所を返します
	Vector2 getFloorPosition();
	// 床との位置をクランプします
	void clampPosition(const Vector2& thisPosition, const Vector2& otherPosition);

private:
	int turnCount_;			// 振り向き回数
	bool isFloor_;
	bool isGround_;
	Vector2 direction_;		// 方向
	Vector2 scale_;			// 敵の大きさ
	Vector2 enemyPosition_;
	Vector2 addPosition_;
	Vector2 floorPosition_;	// 床の位置
};

#endif