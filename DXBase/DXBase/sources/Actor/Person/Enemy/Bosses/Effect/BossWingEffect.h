#ifndef BOSS_WING_EFFECT_H_
#define BOSS_WING_EFFECT_H_

#include "../../../../Base/Actor.h"

class BossWingEffect : public Actor {
private:
	enum class State {
		FlyOut,
		Fall,
		Dead
	};

public:
	BossWingEffect(
		IWorld* world, 
		const Vector2& position, 
		const float bodyScale = 16.0f);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;

private:
	// ��Ԃ̕ύX
	void changeState(State state);
	// �r�o���
	void flyOut(float deltaTime);
	// �������
	void fall(float deltaTime);
	// ���S���
	void deadMove(float deltaTime);
	// �x�W�F�Ȑ����擾���܂�(�n�_�E�I�_0)
	Vector2 bezier(float deltaTime, const Vector2& direPoint);
	// �x�W�F�Ȑ����擾���܂�(�n�_�ƏI�_�̎w��)
	Vector2 bezier(
		float deltaTime, const Vector2& startPoint,
		const Vector2& direPoint, const Vector2& endPoint);
	void groundClamp(Actor& actor);

private:
	//float scale_;		// �傫��
	float rotaSpeed_;
	float degree_;		// �r�o���̊p�x
	float texDegree_;	// �e�N�X�`���̊p�x
	float stateTimer_;	// ��ԃ^�C�}
	float bezierTimer_;	// �x�W�F�^�C�}
	float flyPower_;
	float alpha_;
	bool isTexTurn_;
	Vector2 direction_;	// ����
	State state_;		// ���
};

#endif
