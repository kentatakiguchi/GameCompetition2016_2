#include "PlayerState_Single_Idle.h"

PlayerState_Single_Idle::PlayerState_Single_Idle(const Keys& keys) : PlayerState_Single(keys) {
	NumIDs[0] = TextureID::NUMBER_ZERO_TEX;
	NumIDs[1] = TextureID::NUMBER_ONE_TEX;
	NumIDs[2] = TextureID::NUMBER_TWO_TEX;
	NumIDs[3] = TextureID::NUMBER_THREE_TEX;
	NumIDs[4] = TextureID::NUMBER_FOUR_TEX;
	NumIDs[5] = TextureID::NUMBER_FIVE_TEX;
}

void PlayerState_Single_Idle::unique_init(){
	body_->reset_enemy();
	body_->animation().change(PlayerAnimID::DIV_IDLE);

	target_ = body_->position();

	button_R1_ = TextureID::BUTTON_R1_UP_TEX;
	button_L1_ = TextureID::BUTTON_L1_UP_TEX;

	if (body_->get_partner_vector().x > 0) {
		body_->animation().change_dir(PlayerAnimID::DIV_IDLE, ActionType::Right);
	}
	else {
		body_->animation().change_dir(PlayerAnimID::DIV_IDLE, ActionType::Left);
	}
}

void PlayerState_Single_Idle::update(float deltaTime){
	if (timer_ >= PLAYER_DEAD_LIMIT) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::DEAD));
	}

	if ((int)(timer_ * 10) % 2 < 1) body_->alpha_ -= (int)(deltaTime * static_cast<float>(GetRefreshRate()) * 20);
	else body_->alpha_ += deltaTime * static_cast<float>(GetRefreshRate()) * 20;
	body_->alpha_ = MathHelper::Clamp(body_->alpha_, 100, 255);

	move(deltaTime);
}

void PlayerState_Single_Idle::collide(const Actor & other){
	if ((body_->getName() == "PlayerBody1" && other.getName() == "PlayerBody2Collider") ||
		(body_->getName() == "PlayerBody2" && other.getName() == "PlayerBody1Collider")) {
		change(StateElement((unsigned int)PlayerState_Enum_Single::STAND_BY));
	}
}

void PlayerState_Single_Idle::draw() const {
	if (is_butty())return;
	int graphNum = (int)ceil(PLAYER_DEAD_LIMIT - timer_);
	graphNum = min((int)PLAYER_DEAD_LIMIT, max(0, graphNum));
	//Vector2 drawPos = (body_->getPosition() + Vector2(-(CHIPSIZE / 2), -(ResourceLoader::GetInstance().GetTextureSize(AnimationID::PLAYER_BUTTY_IDLE).y / 2)))* body_->inv_;
	//DrawGraph(drawPos.x, drawPos.y, ResourceLoader::GetInstance().getTextureID(NumIDs.at(graphNum)), TRUE);
	
	Vector2 screen_center = SCREEN_SIZE * 0.5f;

	DrawRotaGraph(static_cast<int>(screen_center.x), static_cast<int>(screen_center.y), (((MathHelper::Sin(timer_ * 60.0f * 5.5f) + 1.0f) * 0.5f) + 1.0f) * 2.0f, 0.0f, ResourceLoader::GetInstance().getTextureID(NumIDs.at(graphNum)), TRUE);
	DrawRotaGraph(static_cast<int>(screen_center.x), static_cast<int>(screen_center.y) - 300, (((MathHelper::Sin(timer_ * 60.0f * 5.5f) + 1.0f) * 0.5f) + 1.0f), 0.0f, ResourceLoader::GetInstance().getTextureID(TextureID::HURRY_TEX), TRUE);
	DrawRotaGraph(static_cast<int>(screen_center.x) + 500, static_cast<int>(screen_center.y), 1.0f, 0.0f, ResourceLoader::GetInstance().getTextureID(button_R1_), TRUE);
	DrawRotaGraph(static_cast<int>(screen_center.x) - 500, static_cast<int>(screen_center.y), 1.0f, 0.0f, ResourceLoader::GetInstance().getTextureID(button_L1_), TRUE);

	//DrawGraph(static_cast<int>(SCREEN_SIZE.x) / 2, static_cast<int>(SCREEN_SIZE.y) / 2, ResourceLoader::GetInstance().getTextureID(NumIDs.at(graphNum)), TRUE);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", PLAYER_DEAD_LIMIT-dead_limit_);
}

void PlayerState_Single_Idle::end(){

	body_->alpha_ = 255.0f;
}

void PlayerState_Single_Idle::key_input(float deltaTime){
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) || InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) {
		target_ += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate());
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT)) {
		target_ += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate());
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT)) {
		target_ += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate());
	}

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT)) {
		button_L1_ = TextureID::BUTTON_L1_PUSH_TEX;
	}
	else {
		button_L1_ = TextureID::BUTTON_L1_UP_TEX;
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT)) {
		button_R1_ = TextureID::BUTTON_R1_PUSH_TEX;
	}
	else {
		button_R1_ = TextureID::BUTTON_R1_UP_TEX;
	}
}

void PlayerState_Single_Idle::pad_input(float deltaTime) {
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1)) {
		target_ += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate());
	}
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1)) {
		target_ += body_->get_partner_vector() * 20 * deltaTime * static_cast<float>(GetRefreshRate());
	}

	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1)) {
		button_L1_ = TextureID::BUTTON_L1_PUSH_TEX;
	}
	else {
		button_L1_ = TextureID::BUTTON_L1_UP_TEX;
	}
	if (InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1)) {
		button_R1_ = TextureID::BUTTON_R1_PUSH_TEX;
	}
	else{
		button_R1_ = TextureID::BUTTON_R1_UP_TEX;
	}
}

void PlayerState_Single_Idle::move(float deltaTime){
	body_->position().x = MathHelper::Lerp(body_->position().x, target_.x, 0.2f);
	Vector2 gravity = Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());
	body_->position() += gravity;
}


