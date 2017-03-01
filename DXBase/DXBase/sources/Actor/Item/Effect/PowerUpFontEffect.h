#ifndef POWER_UP_FONT_EFFECT_H_
#define POWER_UP_FONT_EFFECT_H_

#include "PowerUpEffect.h"

class PowerUpFontEffect : public PowerUpEffect {
public:
	PowerUpFontEffect(
		IWorld* world, const Vector2& position);
	void onUpdate(float deltaTime) override;

public:
	// �A�j���[�V�������I����������Ԃ��܂�
	bool isEnd();
	// �A�j���[�V�����̋t�Đ����s���܂�
	void animaReverse();
};

#endif