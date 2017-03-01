#ifndef MOVE_ITEM_H_
#define MOVE_ITEM_H_

#include "Items.h"

class MoveItem : public Items {
public:
	MoveItem(IWorld* world, Vector2 position, 
		const Vector2& direction = Vector2::Zero,
		const float speed = 4.0f,
		const bool isUseGravity = false) :
		Items(world, position),
		gTimer_(0.0f),
		moveSpeed_(speed),
		direction_(direction),
		isUseGravity_(isUseGravity),
		isGround_(false){
	}

	void onUpdate(float deltaTime) override {
		Items::onUpdate(deltaTime);

		if (ismyHit_) return;
		move(deltaTime);

		isGround_ = false;
	}

	void onCollide(Actor& other) override {
		// �ǂɓ���������A���S����
		auto actorName = other.getName();
		if (actorName == "Boss") return;
		auto getFloorName = strstr(actorName.c_str(), "Floor");
		if (getFloorName != NULL) {
			dead();
			return;
		}
		Items::onCollide(other);
		// ���ɓ����������̏���
		// groundClamp();
	}
	// �ړ�
	void move(float deltaTime) {
		position_ += moveSpeed_ * direction_ * (deltaTime * 60.0f);
		if (!isUseGravity_ || isGround_) return;
		gTimer_ += deltaTime;
		position_.y += gTimer_ * 9.8f * (deltaTime * 60.0f);
	}

private:
	float gTimer_;		// �d�͎���
	float moveSpeed_;	// �ړ���
	Vector2 direction_;	// ����
	bool isUseGravity_;	// �d�͂��g����
	bool isGround_;		// ���ɐڒn������
};

#endif