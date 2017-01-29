#include "PlayerState_Union.h"

#include "../../../../../../Define.h"

// コンストラクタ
PlayerState_Union::PlayerState_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty) :
	element_(-1),
	next_element_(-1),
	timer_(0),
	isEnd_(false),
	butty_(butty),
	retty_(retty){
}

// 全てのステートに共通する初期化処理
void PlayerState_Union::common_init(Actor& actor, const ActionType& type){
	element_ = StateElement(-1, type);
	timer_ = 0;
	isEnd_ = false;
	velocity_ = Vector2::Zero;

	cntr_ = dynamic_cast<PlayerConnector*>(&actor);
}

void PlayerState_Union::input(float deltaTime){
	InputMgr::GetInstance().isConnectGamePad() ? pad_input(deltaTime) : key_input(deltaTime);
}

void PlayerState_Union::common_update(float deltaTime){
	butty_->position() += butty_->hit_vector();
	retty_->position() += retty_->hit_vector();

	butty_->velocity() = Vector2::One;
	retty_->velocity() = Vector2::One;
	butty_->position() = Vector2::Clamp(butty_->position(), Vector2::One * PLAYER_RADIUS, Vector2::One * 10000);
	retty_->position() = Vector2::Clamp(retty_->position(), Vector2::One * PLAYER_RADIUS, Vector2::One * 10000);
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

void PlayerState_Union::key_input(float deltaTime){}

void PlayerState_Union::pad_input(float deltaTime){}

// キー系フラグ
bool PlayerState_Union::holdable_keyR(){
	return InputMgr::GetInstance().IsKeyDown(KeyCode::R_SHIFT) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_keyL() {
	return InputMgr::GetInstance().IsKeyDown(KeyCode::L_SHIFT) && retty_->able_to_hold();
}

bool PlayerState_Union::move_keyR(){
	return InputMgr::GetInstance().KeyVector_R().Length() > 0/* && butty_->able_to_jump()*/;
}

bool PlayerState_Union::move_keyL(){
	return InputMgr::GetInstance().KeyVector_L().Length() > 0/* && retty_->able_to_jump()*/;
}

bool PlayerState_Union::jump_key(){
	return InputMgr::GetInstance().KeyVector_R().y <= Vector2::Down.y && InputMgr::GetInstance().KeyVector_L().y <= Vector2::Down.y;
}

// パッド系フラグ
bool PlayerState_Union::holdable_padR() {
	return InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && butty_->able_to_hold();
}

bool PlayerState_Union::holdable_padL() {
	return InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && retty_->able_to_hold();
}

bool PlayerState_Union::move_padR() {
	return InputMgr::GetInstance().AnalogPadVectorR().Length() > 0/* && butty_->able_to_jump()*/;
}

bool PlayerState_Union::move_padL() {
	return InputMgr::GetInstance().AnalogPadVectorL().Length() > 0/* && retty_->able_to_jump()*/;
}

bool PlayerState_Union::jump_pad() {
	return InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L2) && InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R2);
}

void PlayerState_Union::chase(Vector2 &position, int pointIndex){
	Vector2::Spring(position, cntr_->get_point(pointIndex), velocity_, SPRING_STIFFNESS, SPRING_FRICTION, SPRING_MASS);
}

Vector2 PlayerState_Union::clamp(const Vector2 &position, int pointIndex) {
	return Vector2::ClampTarget(position, cntr_->get_point(pointIndex), PLAYER_MAX_DIV_LENGTH);
}



