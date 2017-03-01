#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"

class FloorSearchPoint : public Actor {
public:
	// �R���X�g���N�^(��`)
	FloorSearchPoint(
		IWorld* world, 
		const Vector2& enemyPosition,
		const Vector2& addPosition, 
		const Vector2& bodyScale
		);
	// �R���X�g���N�^(�~)
	FloorSearchPoint(
		IWorld* world,
		const Vector2& enemyPosition,
		const Vector2& addPosition,
		const float radius
		);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// �ʒu�̐ݒ�
	void setPosition(const Vector2& position);
	// �����̐ݒ�
	void setDirection(const Vector2& direction);
	// ���Ɠ�����������Ԃ��܂�
	bool isFloor();
	bool isGround();
	// ���Ɠ��������ꏊ��Ԃ��܂�
	Vector2 getFloorPosition();

private:
	int turnCount_;			// �U�������
	bool isFloor_;
	bool isGround_;
	bool isGroundBegin_;
	Vector2 direction_;		// ����
	Vector2 enemyPosition_;
	Vector2 addPosition_;
	Vector2 floorPosition_;	// ���̈ʒu
};

#endif