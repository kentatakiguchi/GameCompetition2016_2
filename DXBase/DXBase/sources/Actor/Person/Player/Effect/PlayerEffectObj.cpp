#include "PlayerEffectObj.h"

// コンストラクタ
PlayerEffectObj::PlayerEffectObj(IWorld* world, const Vector2& position, const PlayerEffectID & id, const float& speed):
	Actor(world, "PlayerEffect", position, CollisionBase()){
	effect_.change(id, speed);
}

// デストラクタ
PlayerEffectObj::~PlayerEffectObj(){}

// 更新処理
void PlayerEffectObj::onUpdate(float deltaTime){
	effect_.update(deltaTime);
	if (effect_.end_anim())dead();
}

// 描画処理
void PlayerEffectObj::onDraw() const{
	effect_.draw(position_ * inv_, Vector2::One * 128, 3.0f);
}
