#include "PlayerEffect2D.h"

#include "../../ResourceLoader/ResourceLoader.h"

PlayerEffect2D::PlayerEffect2D(){
	add(PlayerEffectID::SEP_EXP, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_EFFECT_SEP_EXP), 256, 8, 6, 0);
	add(PlayerEffectID::SEP_MOVE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_EFFECT_SEP_MOVE), 256, 7, 9, 6);

}

void PlayerEffect2D::add(const PlayerEffectID & id, const int & res, const int & size, const int & row, const int & column, const int & surplus){
	add_anim(static_cast<int>(id), res, size, row, column, surplus);
}

void PlayerEffect2D::change(const PlayerEffectID & id, const float & speed){
	change_param(static_cast<int>(id), speed);
}
