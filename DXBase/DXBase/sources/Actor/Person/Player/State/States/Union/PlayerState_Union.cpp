#include "PlayerState_Union.h"

#include "../../../../../../Define.h"
#include "../../../../../../Input/InputMgr.h"

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
void PlayerState_Union::common_init(Actor& actor, const StateElement& element){
	element_ = element;
	timer_ = 0;
	isEnd_ = false;

	cntr_ = dynamic_cast<PlayerConnector*>(&actor);
}

void PlayerState_Union::input(float deltaTime){}

void PlayerState_Union::common_update(float deltaTime){
	butty_->position() += butty_->hit_vector();
	retty_->position() += retty_->hit_vector();

	butty_->velocity() = Vector2::One;
	retty_->velocity() = Vector2::One;
	butty_->position() = Vector2::Clamp(butty_->position(), Vector2::One * PLAYER_RADIUS, Vector2::One * 50000);
	retty_->position() = Vector2::Clamp(retty_->position(), Vector2::One * PLAYER_RADIUS, Vector2::One * 50000);
}

// 衝突処理
void PlayerState_Union::collide(const Actor & other) {}

// 描画処理
void PlayerState_Union::draw() const {}

// ステートの変更処理
void PlayerState_Union::change(const StateElement& element){
	if (element_.state_ == element.state_)return;
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

//void PlayerState_Union::key_input(float deltaTime){}
//
//void PlayerState_Union::pad_input(float deltaTime){}

// キー系フラグ
bool PlayerState_Union::holdable_keyR(){
	return InputMgr::GetInstance().IsKeyOn(KeyCode::R_SHIFT) && butty_->getColliderOpponent() == HitOpponent::FLOOR_HIT;
}

bool PlayerState_Union::holdable_keyL() {
	return InputMgr::GetInstance().IsKeyOn(KeyCode::L_SHIFT) && retty_->getColliderOpponent() == HitOpponent::FLOOR_HIT;
}

bool PlayerState_Union::move_keyR(){
	return InputMgr::GetInstance().KeyVectorR().Length() > 0/* && butty_->able_to_jump()*/;
}

bool PlayerState_Union::move_keyL(){
	return InputMgr::GetInstance().KeyVectorL().Length() > 0/* && retty_->able_to_jump()*/;
}

bool PlayerState_Union::jump_key(){
	return InputMgr::GetInstance().KeyVectorR().y <= Vector2::Down.y && InputMgr::GetInstance().KeyVectorL().y <= Vector2::Down.y;
}

// パッド系フラグ
bool PlayerState_Union::holdable_padR() {
	return InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_R1) && butty_->getColliderOpponent() == HitOpponent::FLOOR_HIT;
}

bool PlayerState_Union::holdable_padL() {
	return InputMgr::GetInstance().IsButtonOn(Buttons::BUTTON_L1) && retty_->getColliderOpponent() == HitOpponent::FLOOR_HIT;
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

Vector2 PlayerState_Union::speed_b(float deltaTime){
	return butty_->velocity() * PLAYER_SPEED * butty_->dump() * deltaTime * static_cast<float>(GetRefreshRate());
}

Vector2 PlayerState_Union::speed_r(float deltaTime){
	return retty_->velocity() * PLAYER_SPEED * retty_->dump() * deltaTime * static_cast<float>(GetRefreshRate());
}

void PlayerState_Union::chase(Vector2 &position, int pointIndex){
	Vector2::Spring(position, cntr_->get_point(pointIndex), velocity_, SPRING_STIFFNESS, SPRING_FRICTION, SPRING_MASS);
}

Vector2 PlayerState_Union::clamp(const Vector2 &position, int pointIndex) {
	return Vector2::ClampTarget(position, cntr_->get_point(pointIndex), PLAYER_MAX_DIV_LENGTH);
}

bool PlayerState_Union::isOnFloor() {
	return  (butty_->getOpponent() == HitOpponent::FLOOR_TOP || butty_->getOpponent() == HitOpponent::FLOOR_HIT) &&
			(retty_->getOpponent() == HitOpponent::FLOOR_TOP || retty_->getOpponent() == HitOpponent::FLOOR_HIT);
}

Vector2 PlayerState_Union::gravity(float deltaTime) const{
	return 	Vector2::Up * GRAVITY * deltaTime * static_cast<float>(GetRefreshRate());
}
