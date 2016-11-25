#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "State/Base/StateMgr.h"
#include "PlayerBody.h"
#include "PlayerConnector.h"

#include "PlayerStruct.h"
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
	void body_chase();
	void body_clamp();
	void body_gravity();
private:
	// �ڑ�����
	void connect();
	// ��������
	void split();
	// �ڑ��\���ǂ���
	bool is_connectable();
	// �_���[�W���󂯂����ǂ���
	bool is_damaged();
	// �N���A�������ǂ���
	bool is_cleared();
	// ���S�������ǂ���
	bool is_dead();
private:
	StateMgr stateMgr_;
	// main�ƂȂ镔��
	PlayerBodyPtr retty_;
	// sub �ƂȂ镔��
	PlayerBodyPtr butty_;
	// �R�l�N�^�[
	PlayerCntrPtr cntr_;
	//�Ղ�e�N�X�`��
	PuyoTextureK* mPuyo;
	//�Ђ��ς��
	float mPower;
};

