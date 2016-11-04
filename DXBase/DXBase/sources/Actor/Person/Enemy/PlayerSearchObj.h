#ifndef PLAYER_SEARCH_OBJ_H_
#define PLAYER_SEARCH_OBJ_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class PlayerSearchObj : public Actor {
public:
	PlayerSearchObj(IWorld* world, const Vector2& enemyPosition, const Vector2& playerPosition);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	// �G�ƃv���C���[�̈ʒu��ݒ肵�܂�
	void setPosition(const Vector2& enemyPosition, const Vector2& playerPosition);

private:
	Vector2 enemyPosition_;
	Vector2 playerPosition_;

	Vector2 samplePos_;
};

#endif