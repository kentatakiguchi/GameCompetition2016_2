#include "PlayerAnimation2D.h"

#include "../../ResourceLoader/ResourceLoader.h"

PlayerAnimation2D::PlayerAnimation2D(const std::string& name) {
	if (name == "") return;
	//butty
	if (name == "PlayerBody1") {
		add(PlayerAnimID::IDLE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_IDLE), 256, 8, 4, 1);
		add(PlayerAnimID::MOVE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_MOVE), 256, 8, 4, 1);
		add(PlayerAnimID::HOLD, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_HOLD), 256, 8, 4, 1);
		add(PlayerAnimID::SWIM, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_SWIM), 256, 8, 4, 1);
		add(PlayerAnimID::DEATH, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_SWIM_TURN),   256, 8, 2, 5);
		add(PlayerAnimID::DAMAGE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_DEATH),      256, 8, 2, 0);
		add(PlayerAnimID::DIV_IDLE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_DAMAGE),   256, 8, 2, 0);
		add(PlayerAnimID::DIV_MOVE, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_DIV_IDLE), 256, 8, 2, 0);
		add(PlayerAnimID::TURN, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_DIV_MOVE),     256, 8, 2, 1);
		add(PlayerAnimID::SWIM_TURN, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_BUTTY_TURN),    256, 8, 2, 5);
	}
	//retty
	if (name == "PlayerBody2") {
		add(PlayerAnimID::IDLE,		 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_IDLE), 256, 8, 4, 1);
		add(PlayerAnimID::MOVE,		 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_MOVE), 256, 8, 4, 1);
		add(PlayerAnimID::HOLD,		 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_HOLD), 256, 8, 4, 1);
		add(PlayerAnimID::SWIM,		 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_SWIM), 256, 8, 4, 1);
		add(PlayerAnimID::DEATH,	 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_SWIM_TURN), 256, 8, 2, 5);
		add(PlayerAnimID::DAMAGE,	 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_DEATH), 256, 8, 2, 0);
		add(PlayerAnimID::DIV_IDLE,  ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_DAMAGE), 256, 8, 2, 0);
		add(PlayerAnimID::DIV_MOVE,  ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_DIV_IDLE), 256, 8, 2, 0);
		add(PlayerAnimID::TURN,		 ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_DIV_MOVE), 256, 8, 2, 1);
		add(PlayerAnimID::SWIM_TURN, ResourceLoader::GetInstance().getTextureID(TextureID::PLAYER_RETTY_TURN), 256, 8, 2, 5);
	}
}

void PlayerAnimation2D::add(const PlayerAnimID & id, const int & res, const int & size, const int & row, const int & column, const int & surplus){
	add_anim(static_cast<int>(id), res, size, row, column, surplus);
}

void PlayerAnimation2D::change(const PlayerAnimID& id, const float& speed){
	change_param(static_cast<int>(id), speed);
}

void PlayerAnimation2D::change_dir(const ActionType& type){
	change_dir_type(static_cast<int>(PlayerAnimID::TURN), type);
}

