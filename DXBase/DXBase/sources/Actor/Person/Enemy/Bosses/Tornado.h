#ifndef TORNADO_H_
#define TORNADO_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Base/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"

// �����N���X(�����̊�_���ʒu�Ƃ��Ă��܂�)
class Tornado : public Actor {
public:
	Tornado(IWorld* world, const Vector2&  position, const Vector2& bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// �ʒu�����������܂�
	void initPosition();
	// �p�x��ύX���܂�
	void setAngle(int angle);

private:
	// �v���C���[��T���܂�
	void findPlayer() const;

private:
	Vector2 initPosition_;
};

#endif
