#include "PlayerState_Single.h"

#include "../../../../../../Input/InputMgr.h"

#include "../../../Effect/PlayerEffectObj.h"

// コンストラクタ
PlayerState_Single::PlayerState_Single(const Keys& keys) :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false),
	keys_(keys) {
}

// 全てのステートに共通する初期化処理
void PlayerState_Single::common_init(Actor & actor, const StateElement & element){
	element_ = element;
	timer_ = 0;
	isEnd_ = false;

	body_ = dynamic_cast<PlayerBody*>(&actor);
}

void PlayerState_Single::input(float deltaTime){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input(deltaTime) : key_input(deltaTime);
}

void PlayerState_Single::common_update(float deltaTime){

	timer_ += deltaTime;


	body_->collider();
	body_->velocity() = Vector2::One;
}

// 衝突処理

void PlayerState_Single::collide(const Actor & other) {}

// 描画処理

void PlayerState_Single::draw() const {}

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

bool PlayerState_Single::is_butty() const{
	return keys_.right == KeyCode::RIGHT;
}

bool PlayerState_Single::is_retty()const {
	return keys_.right == KeyCode::D;
}

void PlayerState_Single::key_input(float deltaTime){}

void PlayerState_Single::pad_input(float deltaTime){}

