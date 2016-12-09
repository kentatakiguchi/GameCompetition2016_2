#ifndef TORNADO_H_
#define TORNADO_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Base/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"

// 竜巻クラス(竜巻の基点を位置としています)
class Tornado : public Actor {
public:
	Tornado(IWorld* world, const Vector2&  position, const Vector2& bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// 位置を初期化します
	void initPosition();
	// 角度を変更します
	void setAngle(int angle);

private:
	// プレイヤーを探します
	void findPlayer() const;

private:
	Vector2 initPosition_;
};

#endif
