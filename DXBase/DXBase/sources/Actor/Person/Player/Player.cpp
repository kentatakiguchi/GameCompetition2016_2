#include "Player.h"
#include "State/Player_StateMgr.h"
#include "State/States/State_Dammy.h"
#include "State/States/PlayerState_Idle.h"
#include "State/States/PlayerState_Move.h"
#include "State/States/PlayerState_MoveL.h"
#include "State/States/PlayerState_Hold.h"
#include "State/States/PlayerState_Jump.h"
#include "State/States/PlayerState_Attack.h"
#include "State/States/PlayerState_Attack2.h"
#include "State/States/PlayerState_Damage.h"

#include "PlayerBody.h"
#include "PlayerBody_Connector.h"
#include"../../Body/CollisionBase.h"

#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Math/Vector3.h"
#include <memory>
#include <algorithm>

const float CENTER_HEIGHT = 5.0f;
const float MAX_NORMAL_LENGTH = 100.0f;
//const float MAX_STRETCH_LENGTH = 100.0f;

Player::Player(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, CollisionBase()){

	// モデルの読み込み
	//modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	//animation_ = Animation(modelHandle_);
	
	//初期状態を正面に設定
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 90);
	rotation_.NormalizeRotationMatrix();

	addChild(std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector3(MAX_NORMAL_LENGTH / 2, 0, 0)));
	addChild(std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector3(MAX_NORMAL_LENGTH / 2, 0, 0)));

	stateMgr_.add((unsigned int)Player_EnumState::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)Player_EnumState::MOVE_R, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::MOVE_L, std::make_shared<PlayerState_MoveL>());
	stateMgr_.add((unsigned int)Player_EnumState::HOLD, std::make_shared<PlayerState_Hold>());
	stateMgr_.add((unsigned int)Player_EnumState::JUMP, std::make_shared<PlayerState_Jump>());
	stateMgr_.add((unsigned int)Player_EnumState::QUICK, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK2, std::make_shared<PlayerState_Attack2>());
	stateMgr_.add((unsigned int)Player_EnumState::DAMAGE, std::make_shared<PlayerState_Damage>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)Player_EnumState::IDLE));

	hp_ = 10;

	//world_->addActor(ActorGroup::Player, std::make_shared<PlayerBody_Connector>(world_, position_));

}

Player::~Player(){}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(*this, deltaTime);

	//animation_.changeAnim(motion_);
	//animation_.update(deltaTime);

	//モーション遷移
	//changeMotion(deltaTime);

	// 新しい座標を保存する
	//position_ = Vector3::Lerp(position_, curPosition, 0.8f);
}

void Player::onDraw() const{
	if (main_body_ == nullptr || sub_body_ == nullptr)return;
	// プレイヤーの描画
	Vector3 center =  (main_body_->getPosition() + sub_body_->getPosition()) / 2;
	float dis = Vector3::Distance(main_body_->getPosition(), sub_body_->getPosition());
	if (dis > MAX_NORMAL_LENGTH) {
		//DrawOval(center.x, center.y, dis, body_.component_.radius_ * 5, GetColor(0, 255, 255), TRUE);
	}
	else {
		//DrawOval(center.x, center.y, MAX_NORMAL_LENGTH, body_.component_.radius_ * 5, GetColor(0, 255, 255), TRUE);

	}

	//DrawFormatString(25, 25, GetColor(255, 255, 255), "座標 : x->%d, z->%d", (int)position_.x, (int)position_.z);
	//DrawFormatString(25, 50, GetColor(255, 255, 255), "HP : %d", hp_);
}

void Player::onCollide(Actor & other){
	//if (stateMgr_.currentState() == (unsigned int)Player_EnumState::DAMAGE)return;

	//if (other.getName() == "Enemy_AttackRange") {
	//	stateMgr_.changeState(*this, (unsigned int)Player_EnumState::DAMAGE);
	//	hp_ -= 1;
	//}
}

void Player::changeMotion(float deltaTime){

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L)) {
		motion_ = (motion_ + 1) % 10;
		//animation_.changeAnim(motion_);
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::K)) {
		motion_ = ((motion_ - 1) + 10) % 10;
		//animation_.changeAnim(motion_);
	}
}

void Player::setBody(PlayerBodyPtr main, PlayerBodyPtr sub){
	main_body_ = main;	
	sub_body_ = sub;
}

Player::PlayerBodyPtr Player::getMainBody() {
	return main_body_;
}

Player::PlayerBodyPtr Player::getSubBody(){
	return sub_body_;
}

void Player::createWindow()
{
	int handle, i, j, grhandle;

	// 空のフルカラー画像を作成する
	handle = MakeARGB8ColorSoftImage(256, 256);

	// 縦方向に透明グラデーションした真っ赤な画像を作成する
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			// 色をセット
			DrawPixelSoftImage(handle, j, i, 255, 0, 0, i);
		}
	}

	// 透明かどうかわかるように画面を緑で塗りつぶす
	DrawBox(0, 0, 640, 480, GetColor(0, 255, 0), TRUE);

	// グラフィックハンドルを作成
	grhandle = CreateGraphFromSoftImage(handle);

	// 使い終わったら解放
	DeleteSoftImage(handle);

	// グラフィックハンドルを描画
	DrawGraph(0, 0, grhandle, TRUE);
}


