#include "SceneChangeBossAnm.h"

#include "../../ResourceLoader/ResourceLoader.h"

#include <algorithm>

SceneChangeBossAnm::SceneChangeBossAnm() :
	alpha_(255), isFirst(true){
	add_anim(0, ResourceLoader::GetInstance().getAnimationIDs(AnimationID::BOSS_WAIT_TEX));
	change_param(0, 1);
	change_dir_type(0, ActionType::Left);
	//add(PlayerEffectID::SEP_EXP, ResourceLoader::GetInstance().getAnimationIDs(AnimationID::PLAYER_EFFECT_SEP_EXP));
	//add(PlayerEffectID::SEP_MOVE, ResourceLoader::GetInstance().getAnimationIDs(AnimationID::PLAYER_EFFECT_SEP_MOVE));
}

void SceneChangeBossAnm::update_e(float deltaTime) {
	//alpha_ = std::max<float>(alpha_ - deltaTime * 60, 0);
	update(deltaTime);
}
void SceneChangeBossAnm::Turn()
{
	if (!isFirst)return;
	change_dir_type(0, ActionType::Right);

}
void SceneChangeBossAnm::draw_e(const Vector2 & position, const Vector2 & origin, const float & scale)const {
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);

	Vector2 drawPos = Vector2(position.x - ((ResourceLoader::GetInstance().GetTextureSize(AnimationID::BOSS_WAIT_TEX).x / 2)*scale), position.y);

	draw(drawPos, origin, scale);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
