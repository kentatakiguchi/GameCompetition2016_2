#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "Field.h"
//#include "Ray.h"
//#include "Bullet.h"
//#include "EventMessage.h"
#include "../../../Math/Vector3.h"
#include "State/Base/StateMgr.h"

// �v���[���[
class Player : public Actor {
public:
	enum class MOTION {
		WALK1,
		WALK2
	};
public:
	Player(IWorld* world, const Vector3& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void field();
private:
	StateMgr stateMgr_;

	int hp_;

	Vector3 prePosition;						// �ړ��O�̍��W	
	Vector3 curPosition;						// �ړ���̍��W


};

#endif
