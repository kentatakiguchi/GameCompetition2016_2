#include "StateMgr.h"

#include "State_Dammy.h"

// コンストラクタ
StateMgr::StateMgr() : currentState_(std::make_shared<State_Dammy>()), element_(-1){}

StateMgr::~StateMgr()
{
}

// 更新処理
void StateMgr::action(Actor& actor, float deltaTime) {
	// 入力処理
	currentState_->input(deltaTime);
	// 更新処理
	currentState_->update(deltaTime);
	// 更新処理
	currentState_->common_update(deltaTime);
	// 終了判定がtrueになった場合ステートを変更
	if (currentState_->isEnd()) changeState(actor, currentState_->next());
}

// 衝突処理
void StateMgr::collide(const Actor & other){
	// 衝突処理
	currentState_->collide(other);
}

// 描画処理
void StateMgr::draw() const{
	// 描画処理
	currentState_->draw();
}

// ステートの追加
void StateMgr::addState(const int& state, const IStatePtr& scene) {
	states_[(unsigned int)state] = scene;
}

// ステートの変更処理
void StateMgr::changeState(Actor& actor, const IState::StateElement& element) {
	// 前ステートの終了処理
	currentState_->end();
	// 要素の格納
	element_ = element;
	// 実行ステートを変更
	currentState_ = states_[element_.state_];
	// 共通の初期化
	currentState_->common_init(actor, element_.type_);
	// 固有の初期化
	currentState_->unique_init();
}

// 現在のステート
bool StateMgr::currentState(const int& state) const {
	return element_.state_ == state;
}

bool StateMgr::currentActionType(const ActionType& type){
	return element_.type_ == type;
}

IState::StateElement StateMgr::currentElement(){
	return element_;
}

