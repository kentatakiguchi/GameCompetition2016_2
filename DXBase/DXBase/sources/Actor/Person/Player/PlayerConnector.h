#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"

#include "PlayerPtr.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
#include "../../../Renderer/Puyo_Texture_K.h"

// �v���[���[�R�l�N�^
class PlayerConnector : public Actor {
public:
	// �R���X�g���N�^
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty);
	// �f�X�g���N�^
	~PlayerConnector();
	// �X�V����
	virtual void onUpdate(float deltaTime) override;
	// �`�揈��
	virtual void onDraw() const override;
	// body�擾(��)
	PlayerBodyPtr blue_body();
	// body�擾(��)
	PlayerBodyPtr red_body();
	// 
	PlayerStateMgr_Union& state_mgr();

	void state_update(float deltaTime);
	void create_point(int point_num = 0);
	float length_sum();

	Vector2 get_point(int index);
public:
	PlayerStateMgr_Union stateMgr_;
private:
	// �_���[�W���󂯂����ǂ���
	bool is_damaged();
	// �N���A�������ǂ���
	bool is_cleared();

	void puyoUpdate();
private:


	PlayerBodyPtr butty_;
	PlayerBodyPtr retty_;
	std::vector<PlayerBodyPointPtr> points;

	//�Ղ�e�N�X�`��
	PuyoTextureK* mPuyo;
	//�Ђ��ς��
	float mPower;
	//���
	Vector2 mPuyoResPos;
	Vector2 mPuyoPos;
	Vector2 mPuyoVelo;
	//�Ղ悷�鎞��
	float mPuyoTimer;
	bool mPuyoFlag;
};
