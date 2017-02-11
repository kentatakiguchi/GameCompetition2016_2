#ifndef PRICKLE_H_
#define PRICKLE_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Base/Animation2D.h"

// �g�Q�N���X (�G�l�~�[�̏������Ă��镐��)
class Prickle : public Actor {
public:
	Prickle(
		IWorld* world,
		const Vector2& enemyPosition
		, const Vector2& addPosition,
		const Vector2& bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
	// �ʒu�����܂�
	void setEnemyPosition(const Vector2& position);
	// �ǉ��ʒu�����܂�
	void setAddPosition(const Vector2& position);
	// ���������܂�
	void setDirection(const Vector2& direction);
	// �v���C���[�ɗ^����_���[�W�ʂ�Ԃ��܂�
	int getAP();

private:
	int ap_;				// �v���C���[�ɗ^����_���[�W��
	Vector2 direction_;		// ����
	Vector2 enemyPosition_;	// �G�̈ʒu
	Vector2 addPosition_;	// �ǉ��̈ʒu
};

#endif
