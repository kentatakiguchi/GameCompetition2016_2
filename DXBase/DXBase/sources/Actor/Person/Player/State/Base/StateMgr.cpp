#include "StateMgr.h"

// コンストラクタ
StateMgr::StateMgr() {}

// 更新処理
void StateMgr::action(Actor & actor, float deltaTime) {
	// 更新処理
	currentState_->update(actor, deltaTime);
	currentState_->end();
	// 終了判定がtrueになった場合ステートを変更
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

// ステートの変更処理
void StateMgr::changeState(Actor & actor, IState::StateElement element) {
	// 次のステート名を代入
	currentStateName_ = element.state_;
	// 実行ステートを変更
	currentState_ = states_[currentStateName_];
	// 共通の初期化
	currentState_->common_init(actor, element.action_type_);
	// 固有の初期化
	currentState_->unique_init(actor);
}

// ステートの追加
void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// 現在のステート
bool StateMgr::currentState(unsigned int state) {
	return currentStateName_ == state;
}

