#ifndef PRICKLE_H_
#define PRICKLE_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"

class Prickle : public Actor {
public:
	Prickle(IWorld* world, const Vector2& enemyPosition, const Vector2& addPosition, const float bodyScale);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// �ʒu�����܂�
	void setEnemyPosition(const Vector2& position);
	// ���������܂�
	void setDirection(const Vector2& direction);
	// �v���C���[�ɗ^����_���[�W�ʂ�Ԃ��܂�
	int getAP();

private:
	int ap_;				// �v���C���[�ɗ^����_���[�W��

	Vector2 direction_;		// ����
	Vector2 enemyPosition_;	// �G�̈ʒu
	Vector2 addPosition_;	// �ǉ��̈ʒu
	Vector2 totalPosition_;	// ���v�̈ʒu
};

#endif
