#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
//#include "PlayerBody.h"
//#include "PlayerConnector.h"

#include "PlayerPtr.h"
#include "../../../Renderer/Puyo_Texture_K.h"

// �v���[���[
class Player : public Actor {
public:
	enum class MOTION {};
public:
	Player(IWorld* world, const Vector2& position);
	~Player();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	PlayerBodyPtr blue_body();
	PlayerBodyPtr red_body();
	PlayerCntrPtr connector();

	void set_body();
public:
	// �ڑ�����
	void connect();
	// �ڑ��\���ǂ���
	bool is_connectable();
	// ���S�������ǂ���
	bool is_dead();
private:
	//PlayerStateMgr_Union stateMgr_;
	// main�ƂȂ镔��
	PlayerBodyPtr retty_;
	// sub �ƂȂ镔��
	PlayerBodyPtr butty_;
	// �R�l�N�^�[
	//PlayerCntrPtr cntr_;
};

