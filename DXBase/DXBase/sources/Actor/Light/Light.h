#ifndef LIGHT_H_
#define LIGHT_H_

#include "../Base/Actor.h"

class Light : public Actor {
public:
	// コンストラクタ
	Light(IWorld* world, const Vector3& position);
private:
	// 描画
	virtual void onDraw() const override;
};

#endif

