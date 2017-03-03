#ifndef BOSS_SCROLL_POINT_H_
#define BOSS_SCROLL_POINT_H_

#include "../../../../../Base/Actor.h"

class BossScrollPoint : public Actor {
public:
	BossScrollPoint(
		IWorld* world,
		const Vector2& position);
	void onUpdate(float deltaTime) override;

public:
	// ���{�X�X�e�[�W���ɓ���������Ԃ��܂�
	bool isInMBossStage();

private:
	// �v���C���[�̈ʒu���v�Z
	void playerPosition(const std::string name);
	// �X�N���[�����̈ړ�
	void scrollMove(float deltaTime);

private:
	bool isPlayerIn_;				// �v���C���[���͈͓��ɓ����Ă��邩
	Vector2 prevPlayerDirection_;	// �v���C���[�̕���(�N����)
	ActorPtr player_;				// �N�������v���C���[
};

#endif