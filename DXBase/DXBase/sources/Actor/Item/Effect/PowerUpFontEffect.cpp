#include "PowerUpFontEffect.h"

PowerUpFontEffect::PowerUpFontEffect(
	IWorld * world, 
	const Vector2 & position) : 
	PowerUpEffect(world, "PowerUpFontEffect", position, Vector2::One * 192, 
		POWER_UP_FONT_NUMBER, AnimationID::PLAYER_EFFECT_POWER_UP)
{
}

void PowerUpFontEffect::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);
}

// �A�j���[�V�������I����������Ԃ��܂�
bool PowerUpFontEffect::isEnd()
{
	return animation_.isReverse_ && animation_.getFrame() == 0;
}

// �A�j���[�V�����̋t�Đ����s���܂�
void PowerUpFontEffect::animaReverse()
{
	animation_.setIsReverse(true);
}
