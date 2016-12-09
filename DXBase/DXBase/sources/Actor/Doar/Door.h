#pragma once
#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"
// �v���[���[
class Door : public Actor {
public:
	Door(IWorld* world, const Vector2& position);
	~Door();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
public:
	//�h�A�̊J��ݒ� true:�J�� false:����
	void DoorOpen(bool openFlag);
private:
	bool mDoorFlag;


};