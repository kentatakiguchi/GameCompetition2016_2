#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
//#include "EventMessage.h"
#include "PlayerPtr.h"
#include "State/States/Union/PlayerStateMgr_Union.h"
#include "../../../Renderer/Puyo_Texture_K.h"

#include "Player.h"

// �v���[���[
class PlayerConnector : public Actor {
public:
	PlayerConnector(IWorld* world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty);
	~PlayerConnector();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
	PlayerBodyPtr blue_body();
	PlayerBodyPtr red_body();
	PlayerStateMgr_Union& state_mgr();
	void state_action(float deltaTime);
	void create_point(int point_num = 0);

	Vector2 get_point(int index);
	std::vector<Vector2> get_points();
private:
	// �_���[�W���󂯂����ǂ���
	bool is_damaged();
	// �N���A�������ǂ���
	bool is_cleared();
	// ���S�������ǂ���
	bool is_dead();

	void puyoUpdate();
private:
	PlayerStateMgr_Union stateMgr_;

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
