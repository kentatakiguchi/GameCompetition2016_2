#ifndef PLAYER_SEARCH_OBJ_H_
#define PLAYER_SEARCH_OBJ_H_

#include "../../Base/Actor.h"

class PlayerSearchObj : public Actor {
public:
	PlayerSearchObj(
		IWorld* world,
		const Vector2& enemyPosition,
		const Vector2& playerPosition);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	// �G�ƃv���C���[�̈ʒu��ݒ肵�܂�
	void setPosition(const Vector2& enemyPosition, const Vector2& playerPosition);
	// �v���C���[�������Ă��邩��Ԃ��܂�
	bool isPlayerLook();

private:
	Vector2 enemyPosition_;		// �G�̈ʒu
	Vector2 playerPosition_;	// �v���C���[�̈ʒu
	Vector2 blockPosition_;		// �u���b�N�̈ʒu
	bool isBlockHit_;
};

#endif