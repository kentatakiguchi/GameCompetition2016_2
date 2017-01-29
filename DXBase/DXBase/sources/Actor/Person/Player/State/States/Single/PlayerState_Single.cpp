#include "PlayerState_Single.h"

// コンストラクタ
PlayerState_Single::PlayerState_Single(const Keys& keys) :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false),
	keys_(keys) {
}

// 全てのステートに共通する初期化処理
void PlayerState_Single::common_init(Actor& actor, const ActionType& type) {
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	body_ = dynamic_cast<PlayerBody*>(&actor);
}

void PlayerState_Single::input(float deltaTime){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input(deltaTime) : key_input(deltaTime);
}

void PlayerState_Single::common_update(float deltaTime){
	body_->velocity() = Vector2::One;
}

// ステートの変更処理
void PlayerState_Single::change(const StateElement& element) {
	next_element_ = element;
	isEnd_ = true;
}

// ステートが終了したか否か
bool PlayerState_Single::isEnd() {
	return isEnd_;
}

// 次のステートの要素
IState::StateElement PlayerState_Single::next() const {
	return next_element_;
}

bool PlayerState_Single::is_butty(){
	return keys_.right == KeyCode::RIGHT;
}

bool PlayerState_Single::is_retty(){
	return keys_.right == KeyCode::D;
}

void PlayerState_Single::key_input(float deltaTime){}

void PlayerState_Single::pad_input(float deltaTime){}

