#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "Field.h"
//#include "Ray.h"
//#include "Bullet.h"
//#include "EventMessage.h"
#include "../../../Math/Vector3.h"
#include "State/Base/StateMgr.h"

// �v���[���[
class PlayerBody_Connector : public Actor {
public:
	enum class MOTION {
		WALK1,
		WALK2
	};
public:
	PlayerBody_Connector(IWorld* world, const Vector3& position);
	~PlayerBody_Connector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
private:
	StateMgr stateMgr_;
	
	Vector3 prePosition;						// �ړ��O�̍��W	
	Vector3 curPosition;						// �ړ���̍��W
};