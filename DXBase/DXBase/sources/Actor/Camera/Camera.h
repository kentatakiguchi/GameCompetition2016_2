#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Base/Actor.h"
#include "../../Math/Vector3.h"
#include "../../Math/Quaternion.h"
#include "../../Input/InputMgr.h"

class Camera : public Actor {
public:
	// コンストラクタ
	explicit Camera(IWorld* world);
private:
	// 更新
	virtual void onUpdate(float deltaTime) override;
	// 描画
	virtual void onDraw() const override;

private:
	const float CAMERA_ANGLE_SPEED = 3.0f;
	//const float MAX_PITCH = 
	Vector3 target_;
	Vector3 eye_;
	float angle_;
};


#endif


