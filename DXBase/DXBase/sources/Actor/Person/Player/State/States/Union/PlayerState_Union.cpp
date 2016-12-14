#include "PlayerState_Union.h"

// コンストラクタ
PlayerState_Union::PlayerState_Union() :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false){
}

// 全てのステートに共通する初期化処理
void PlayerState_Union::common_init(Actor& actor, const ActionType& type){
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	cntr_ = dynamic_cast<PlayerConnector*>(&actor);
	butty_ = cntr_->blue_body();
	retty_ = cntr_->red_body();

	//player_ = dynamic_cast<Player*>(&actor);
	//cntr_ = player_->connector();
}

void PlayerState_Union::input(){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input() : key_input();
}

// ステートの変更処理
void PlayerState_Union::change(const StateElement& element){
	next_element_ = element;
	isEnd_ = true;
}

// ステートが終了したか否か
bool PlayerState_Union::isEnd(){
	return isEnd_;
}

// 次のステートの要素
IState::StateElement PlayerState_Union::next() const{
	return next_element_;
}

void PlayerState_Union::change(const PlayerState_Enum_Union & id, const ActionType & type){
	change(StateElement(static_cast<int>(id), type));
}

void PlayerState_Union::key_input(){}

void PlayerState_Union::pad_input(){}

// キー系フラグ
bool PlayerState_Union::holdable_keyR(){
	return InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_keyL() {
	return InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && retty_->able_to_hold();
}

bool PlayerState_Union::move_keyR(){
	return InputMgr::GetInstance().KeyVector_R().Length() > 0;
}

bool PlayerState_Union::move_keyL(){
	return InputMgr::GetInstance().KeyVector_L().Length() > 0;
}

bool PlayerState_Union::jump_key(){
	return InputMgr::GetInstance().KeyVector_R().y <= Vector2::Down.y && InputMgr::GetInstance().KeyVector_L().y <= Vector2::Down.y;
}

// パッド系フラグ
bool PlayerState_Union::holdable_padR() {
	return InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_R1) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_padL() {
	return InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_L1) && retty_->able_to_hold();
}

bool PlayerState_Union::move_padR() {
	return InputMgr::GetInstance().AnalogPadVectorR().Length() > 0;
}

bool PlayerState_Union::move_padL() {
	return InputMgr::GetInstance().AnalogPadVectorL().Length() > 0;
}

bool PlayerState_Union::jump_pad() {
	return InputMgr::GetInstance().AnalogPadVectorR().y <= Vector2::Down.y && InputMgr::GetInstance().AnalogPadVectorL().y <= Vector2::Down.y;
}



