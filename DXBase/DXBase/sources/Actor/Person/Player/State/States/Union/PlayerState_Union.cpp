#include "PlayerState_Union.h"

// コンストラクタ
PlayerState_Union::PlayerState_Union() : 
	element_(-1),
	timer_(0),
	isEnd_(false){
}

// 全てのステートに共通する初期化処理
void PlayerState_Union::common_init(Actor& actor, ActionType type){
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	player_ = dynamic_cast<Player*>(&actor);
	butty_ = player_->blue_body();
	retty_ = player_->red_body();
	cntr_ = player_->connector();
	//struct_ = ;


	//main_body_ = player_->getMainBody();
	//sub_body_ = player_->getSubBody();

	// いずれかのBodyがnullでない場合return
	//if (main_body_ != nullptr || sub_body_ != nullptr)return;

	//auto body1_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody1"));
	//auto body2_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody2"));

	//main_body_ = body1_;
	//sub_body_ = body2_;

	//player_->setBody(main_body_, sub_body_);

	//main_body_->set_partner(sub_body_);
	//sub_body_->set_partner(main_body_);

}

// ステートの変更処理
void PlayerState_Union::change(StateElement element){
	element_ = element;
	isEnd_ = true;
}

// ステートが終了したか否か
bool PlayerState_Union::isEnd(){
	return isEnd_;
}

// 次のステートの要素
IState::StateElement PlayerState_Union::next() const{
	return element_;
}

bool PlayerState_Union::holdable_keyR(){
	return InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_keyL() {
	return InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && retty_->able_to_hold();
}

bool PlayerState_Union::holdable_padR() {
	return InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_padL() {
	return InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && retty_->able_to_hold();
}



