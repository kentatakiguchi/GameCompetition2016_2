#include "StateMgr.h"

#include "State_Dammy.h"

// コンストラクタ
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()), element_(-1){}

// 更新処理
void StateMgr::action(Actor& actor, float deltaTime) {
	// 入力処理
	currentState_->input();
	// 更新処理
	currentState_->update(deltaTime);
	// 終了判定がtrueになった場合ステートを変更
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

// ステートの変更処理
void StateMgr::changeState(Actor& actor, IState::StateElement element) {
	// 前ステートの終了処理
	currentState_->end();
	// 要素の格納
	element_ = element;
	// 実行ステートを変更
	currentState_ = states_[element_.state_];
	// 共通の初期化
	currentState_->common_init(actor, element_.action_type_);
	// 固有の初期化
	currentState_->unique_init();
}

// ステートの追加
void StateMgr::add(unsigned int state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// 現在のステート
bool StateMgr::currentState(unsigned int state) {
	return element_.state_ == state;
}

bool StateMgr::currentActionType(ActionType action_type){
	return element_.action_type_ == action_type;
}

IState::StateElement StateMgr::currentElement(){
	return element_;
}

