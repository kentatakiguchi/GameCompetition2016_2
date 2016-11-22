#include "StateMgr.h"

#include "State_Dammy.h"

// コンストラクタ
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()){}

// 更新処理
void StateMgr::action(float deltaTime) {
	// 更新処理
	currentState_->update(deltaTime);
	// 終了判定がtrueになった場合ステートを変更
	if (currentState_->isEnd()) changeState(currentState_->next());
}

// ステートの変更処理
void StateMgr::changeState(IState::StateElement element) {
	// 前ステートの終了処理
	currentState_->end();
	// 次のステート名を代入
	currentStateName_ = element.state_;
	// 実行ステートを変更
	currentState_ = states_[currentStateName_];
	// 共通の初期化
	currentState_->common_init(element.action_type_);
	// 固有の初期化
	currentState_->unique_init();
}

// ステートの追加
void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// 現在のステート
bool StateMgr::currentState(unsigned int state) {
	return currentStateName_ == state;
}

