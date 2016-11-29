#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "PlayerBodyPoint.h"
#include "../../../Renderer/DrawShape.h"

PlayerConnector::PlayerConnector(){}

PlayerConnector::PlayerConnector(IWorld * world, PlayerBodyPtr butty, PlayerBodyPtr retty) :
	Actor(world, "PlayerConnector", Vector2::Zero, CollisionBase(Vector2(0, 0), Vector2(0, 0))),
	action_type_(ActionType::Right) {
	butty_ = butty;
	retty_ = retty;

	create_point(PLAYER_CNTR_DIV_NUM);

	pos = Vector2::Zero;
	scale = Vector2(2, 1);
	rotate = 0;
}

PlayerConnector::~PlayerConnector(){
}

void PlayerConnector::onUpdate(float deltaTime){
	position_ = (butty_->getPosition() + retty_->getPosition()) / 2;

	pos = position_ * inv_ - Vector2::One * distance();
}

void PlayerConnector::onLateUpdate(float deltaTime){}

void PlayerConnector::onDraw() const{
	//puyo->PuyoDraw();

	//body_.draw();
	//bezier_.draw(100, inv_);


	Vector3 main = Vector3(butty_->getPosition().x, butty_->getPosition().y) * inv_;
	Vector3 sub = Vector3(retty_->getPosition().x, retty_->getPosition().y) * inv_;
	DrawShape::Oval(Vector2(main.x, main.y), Vector2(sub.x, sub.y), PLAYER_RADIUS * 2, PLAYER_MAX_NORMAL_LENGTH * 0.75f);
	//DrawFormatString(static_cast<int>(main.x), static_cast<int>(main.y), GetColor(255, 255, 255), "main");
	//DrawFormatString(static_cast<int>(sub.x), static_cast<int>(sub.y), GetColor(255, 255, 255), "sub");
}

void PlayerConnector::onCollide(Actor & other){
	if (other.getName() == "MapChip") {
	}

	
}

void PlayerConnector::create_point(int point_num) {
	for (int i = 0; i < point_num; i++) {
		auto point = std::make_shared<PlayerBodyPoint>(world_, point_num + 1, i, *this);
		addChild(point);
		points.push_back(point);
	}
}

float PlayerConnector::distance(){
	return (butty_->getPosition() - retty_->getPosition()).Length();
}

Vector2 PlayerConnector::base_point(ActionType type){
	if (type == ActionType::Right) return points[0]->getPosition();
	if (type == ActionType::Left)  return points[points.size() - 1]->getPosition();
	return Vector2::Zero;
}

Vector2 PlayerConnector::composed_vector(Vector2 point, int index){
	auto player = std::dynamic_pointer_cast<Player>(world_->findActor("Player"));

	if (player->action_type(ActionType::Right))	action_type_ = ActionType::Right;
	if (player->action_type(ActionType::Left)) 	action_type_ = ActionType::Left;


	Vector2 t = target();
	Vector2 c = comp();
	Vector2 lerp_t = lerp_target(index);
	Vector2 current = point - t;

	float length = 0;
	float point_len = static_cast<float>(PLAYER_MAX_STRETCH_LENGTH) / static_cast<float>(PLAYER_CNTR_DIV_NUM + 1);
	float target_len = (lerp_t - point).Length();
	(target_len > point_len) ? length = point_len : length = c.Length() / (PLAYER_CNTR_DIV_NUM + 1);
	return lerp_t + (c + current).Normalize() * length;
}

Vector2 PlayerConnector::target(){
	if (action_type_ == ActionType::Right) {
		return butty_->getPosition();
	}
	if (action_type_ == ActionType::Left) {
		return retty_->getPosition();
	}
	return Vector2::Zero;
}

Vector2 PlayerConnector::comp(){
	if (action_type_ == ActionType::Right) {
		return retty_->getPosition() - butty_->getPosition();

	}
	if (action_type_ == ActionType::Left) {
		return butty_->getPosition() - retty_->getPosition();
	}
	return Vector2::Zero;
}

Vector2 PlayerConnector::lerp_target(int index){

	if (action_type_ == ActionType::Right) {
		if (index == 0) {
			return butty_->getPosition();
		}
		else {
			return points[index - 1]->getPosition();
		}
	}
	if (action_type_ == ActionType::Left) {
		if (index == points.size() - 1) {
			return retty_->getPosition();
		}
		else {
			return points[index + 1]->getPosition();
		}
	}
	return Vector2::Zero;
}


