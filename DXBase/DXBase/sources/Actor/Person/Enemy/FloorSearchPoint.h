#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(IWorld* world, const Vector3&  position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// �ʒu�̐ݒ�
	void setPosition(Vector3 position);
	// �����̐ݒ�
	void setDirection(int direction);
	// �G�̑傫�������܂�
	void setEnemyScale(const Vector2 scale);
	// ���Ɠ�����������Ԃ��܂�
	bool isFloor();

private:
	int direction_;			// ����
	int turnCount_;			// �U�������
	bool isFloor_;
	Vector2 enemyScale_;	// �G�̑傫��
	Vector2 vec2Position_;
};

#endif