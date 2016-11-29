#include "PlayerState_Single.h"

// コンストラクタ
PlayerState_Single::PlayerState_Single() :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false) {
}

// 全てのステートに共通する初期化処理
void PlayerState_Single::common_init(Actor& actor, ActionType type) {
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	//player_body_ = std::dynamic_pointer_cast<PlayerBody>(actor);
	player_body_ = dynamic_cast<PlayerBody*>(&actor);
}

void PlayerState_Single::input(){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input() : key_input();
}

// ステートの変更処理
void PlayerState_Single::change(StateElement element) {
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

void PlayerState_Single::key_input(){}

void PlayerState_Single::pad_input(){}

