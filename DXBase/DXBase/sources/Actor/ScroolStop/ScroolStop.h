#pragma once
#ifndef SCROOL_STOP_H_
#define SCROOL_STOP_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"




// �v���[���[
class ScroolStop : public Actor {
public:
	enum StopDirection {
		RIGHT,
		LEFT,
		TOP,
		BOT
	};

public:
	ScroolStop(IWorld* world, const Vector2& position,StopDirection dire);
	~ScroolStop();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;

public:
	Vector2 GetSceneInFlag() {
		return sceneInFlag;
	}
private:
	//��ʓ��ɓ����Ă��邩x��
	Vector2 sceneInFlag;
	//�ǂ̕����Ŏ~�߂邩
	StopDirection mDire;
};

#endif
