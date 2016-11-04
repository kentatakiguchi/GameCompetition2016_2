#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include "../../../Define.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(
		IWorld* world, 
		const Vector2& enemyPosition,
		const Vector2& addPosition, 
		const Vector2& bodyScale
		);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// �ʒu�̐ݒ�
	void setPosition(const Vector2& position);
	// �����̐ݒ�
	void setDirection(const Vector2& direction);
	// �G�̑傫�������܂�
	void setEnemyScale(const Vector2& scale);
	// ���Ɠ�����������Ԃ��܂�
	bool isFloor();
	bool isGround();
	// ���Ɠ��������ꏊ��Ԃ��܂�
	Vector2 getFloorPosition();
	// ���Ƃ̈ʒu���N�����v���܂�
	void clampPosition(const Vector2& thisPosition, const Vector2& otherPosition);

private:
	int turnCount_;			// �U�������
	bool isFloor_;
	bool isGround_;
	Vector2 direction_;		// ����
	Vector2 scale_;			// �G�̑傫��
	Vector2 enemyPosition_;
	Vector2 addPosition_;
	Vector2 floorPosition_;	// ���̈ʒu
};

#endif