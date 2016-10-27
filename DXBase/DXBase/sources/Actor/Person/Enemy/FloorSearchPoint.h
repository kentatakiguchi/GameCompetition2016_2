#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(IWorld* world,const Vector3& pointPosition , const Vector3&  collidePosition);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// �ʒu�̐ݒ�
	void setPosition(Vector3 position);
	// �����̐ݒ�(X)
	void setDirectionX(int direction);
	// �����̐ݒ�(Y)
	void setDirectionY(int direction);
	// �G�̑傫�������܂�
	void setEnemyScale(const Vector2 scale);
	// ���Ɠ�����������Ԃ��܂�
	bool isFloor();
	bool isGround();

private:
	int turnCount_;			// �U�������
	bool isFloor_;
	bool isGround_;
	Vector2 direction_;			// ����
	Vector2 enemyScale_;	// �G�̑傫��
	Vector3 pointPosition_;
};

#endif