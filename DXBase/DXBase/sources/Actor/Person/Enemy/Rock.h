#ifndef ROCK_H_
#define ROCK_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Enemy/EnemyAnimation2D.h"

class Rock : public Actor {
private:
	enum class State {
		Idel,
		Fall,
		Dead
	};

public:
	Rock(IWorld* world, const Vector2&  position, const float bodyScale = 64.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

private:
	// ��Ԃ̕ύX
	void changeState(State state);
	// �ҋ@���
	void idel(float deltaTime);
	// �������
	void fall(float deltaTime);
	// ���S���
	void deadMove(float deltaTime);

private:
	float speed_;	// ���x
	float timer_;	// ����
	State state_;	// ���
	int animeNum_;
	EnemyAnimation2D animation_;
};

#endif
