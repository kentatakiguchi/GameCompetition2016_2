#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"

#include "PlayerPtr.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
#include "../../../Renderer/Puyo_Texture_K.h"

// �v���[���[�R�l�N�^
class PlayerConnector : public Actor {
public:
	// �R���X�g���N�^
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr& butty, PlayerBodyPtr& retty);
	// �f�X�g���N�^
	~PlayerConnector();
	//// �X�V����
	//virtual void onUpdate(float deltaTime) override;

	// �p�������̍X�V����
	void onUpdate(float deltaTime);
	// �`�揈��
	virtual void onDraw() const override;

	void point_chase(float deltaTime);

	void create_point(int point_num = 0);

	Vector2 get_point(int index);

	//�����ړ��֐�(���x��)
	void ForcedMove(Vector2 velocity);

public:
	PlayerStateMgr_Union stateMgr_;
private:
	// �_���[�W���󂯂����ǂ���
	bool is_damaged();
	// �N���A�������ǂ���
	bool is_cleared();

	void puyoUpdate();
private:
	float timer_;

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
