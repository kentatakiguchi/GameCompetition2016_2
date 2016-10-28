#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerBody.h"

// �v���[���[
class Player : public Actor {
public:
	using PlayerBodyPtr = std::shared_ptr<PlayerBody>;

	enum class MOTION {};
public:
	Player(IWorld* world, const Vector2& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	void changeMotion(float deltaTime);
	void setBody(PlayerBodyPtr main, PlayerBodyPtr sub);
	PlayerBodyPtr getMainBody();
	PlayerBodyPtr getSubBody();

	void createOval(Vector2 main_pos, Vector2 sub_pos, int height)const;
	void createOval(Vector2 center, float width, int height)const;
	

	//void field();	

	Vector2 GetVelo()
	{
		return mVelo;
	}
	Vector2 GetSpringVelo()
	{
		return veloPlus;
	}
private:
	void createWindow();
	StateMgr stateMgr_;

	int hp_;
	
	PlayerBodyPtr main_body_;
	PlayerBodyPtr sub_body_;

	Vector2 prePosition;						// �ړ��O�̍��W	
	Vector2 curPosition;						// �ړ���̍��W
	Vector2 mVelo;                              //�v���C���[�̑��x
	Vector2 mSevePos;                           //�ۑ��p�̍��W(�X�N���[���ŕ␳����Ă��Ȃ���Ԃ̍��W)
};

