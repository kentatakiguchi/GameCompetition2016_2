#include "PlayerState_Single.h"

// コンストラクタ
PlayerState_Single::PlayerState_Single() :
	element_(-1),
	timer_(0),
	isEnd_(false) {
}

// 全てのステートに共通する初期化処理
void PlayerState_Single::common_init(Actor & actor, ActionType type) {
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;

	player_body_ = dynamic_cast<PlayerBody*>(&actor);
	//main_body_ = player_->getMainBody();
	//sub_body_ = player_->getSubBody();

	//// いずれかのBodyがnullでない場合return
	//if (main_body_ != nullptr || sub_body_ != nullptr)return;

	//auto body1_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody1"));
	//auto body2_ = std::static_pointer_cast<PlayerBody>(actor.findCildren((const std::string)"PlayerBody2"));

	//main_body_ = body1_;
	//sub_body_ = body2_;

	//player_->setBody(main_body_, sub_body_);

	//main_body_->target(sub_body_);
	//sub_body_->target(main_body_);
}

// ステートの変更処理
void PlayerState_Single::change(StateElement element) {
	element_ = element;
	isEnd_ = true;
}

// ステートが終了したか否か
bool PlayerState_Single::isEnd() {
	return isEnd_;
}

// 次のステートの要素
IState::StateElement PlayerState_Single::next() const {
	return element_;
}
