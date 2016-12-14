#include "PlayerEffectObj.h"

// �R���X�g���N�^
PlayerEffectObj::PlayerEffectObj(IWorld* world, const Vector2& position, const PlayerEffectID & id, const float& speed):
	Actor(world, "PlayerEffect", position, CollisionBase()){
	effect_.change(id, speed);
}

// �f�X�g���N�^
PlayerEffectObj::~PlayerEffectObj(){}

// �X�V����
void PlayerEffectObj::onUpdate(float deltaTime){
	effect_.update(deltaTime);
	if (effect_.end_anim())dead();
}

// �`�揈��
void PlayerEffectObj::onDraw() const{
	effect_.draw(position_ * inv_, Vector2::One * 128, 3.0f);
}
