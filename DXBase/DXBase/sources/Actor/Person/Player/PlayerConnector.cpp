#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "PlayerBody_Point.h"
#include "../../../Renderer/DrawShape.h"

PlayerConnector::PlayerConnector(){}

PlayerConnector::PlayerConnector(IWorld * world, PlayerBodyPtr main, PlayerBodyPtr sub) :
	Actor(world, "PlayerConnector", Vector2::Zero, CollisionBase(Vector2(0, 0), Vector2(0, 0))) {
	main_ = main;
	sub_ = sub;

	points = std::vector<Vector2>(3);

	create_point(3);

	puyo = new PuyoTextureK(TextureID::PUYO_TEST_TEX, position_, Vector2::One, 0);
}

PlayerConnector::~PlayerConnector(){
	delete puyo;
}

void PlayerConnector::onUpdate(float deltaTime){
	position_ = (main_->getPosition() + sub_->getPosition()) / 2;
	puyo->PuyoUpdate();
	puyo->SetPosition(position_, Vector2::One, 0);

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::X)) {
		dead();
	}
	for (int i = 0; i < 3; i++) {
		auto player = world_->findActor("Body_Point" + std::to_string(i + 1));
		points[i] = player->getPosition();
	}

	bezier_.set(main_->getPosition(), sub_->getPosition(), points, 100);
}

void PlayerConnector::onLateUpdate(float deltaTime){}

void PlayerConnector::onDraw() const{
	//puyo->PuyoDraw();

	body_.draw();
	bezier_.draw(100, inv_);


	Vector3 main = Vector3(main_->getPosition().x, main_->getPosition().y) * inv_;
	Vector3 sub = Vector3(sub_->getPosition().x, sub_->getPosition().y) * inv_;
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
		addChild(std::make_shared<PlayerBody_Point>(world_, "Body_Point", point_num + 1, i + 1, main_, sub_));
	}
}
