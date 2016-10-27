#include "Player.h"
#include "State/States/State_Dammy.h"
#include "State/States/PlayerState_StandBy.h"
#include "State/States/PlayerState_Idle.h"
#include "State/States/PlayerState_Move.h"
#include "State/States/PlayerState_Hold.h"
#include "State/States/PlayerState_Jump.h"
#include "State/States/PlayerState_Attack.h"
#include "State/States/PlayerState_Attack2.h"
#include "State/States/PlayerState_Damage.h"

#include "PlayerBody.h"
#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Math/Vector3.h"
#include <memory>
#include <algorithm>

const float CENTER_HEIGHT = 5.0f;
const float MAX_NORMAL_LENGTH = 100.0f;
//const float MAX_STRETCH_LENGTH = 100.0f;

Player::Player(IWorld * world, const Vector3 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0,0), Vector2(0, 0), 10.0f)),
prePosition(Vector2::Zero),
mVelo(Vector2::Zero),
curPosition(Vector2::Zero),
mSevePos(Vector2::Zero)
{

	// ���f���̓ǂݍ���
	//modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	//animation_ = Animation(modelHandle_);
	
	//������Ԃ𐳖ʂɐݒ�
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), 90);
	rotation_.NormalizeRotationMatrix();

	addChild(std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector3(MAX_NORMAL_LENGTH / 2, 0, 0)));
	addChild(std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector3(MAX_NORMAL_LENGTH / 2, 0, 0)));
	addChild(std::make_shared<PlayerConnector>(world_));

	stateMgr_.add((unsigned int)Player_EnumState::STAND_BY, std::make_shared<PlayerState_StandBy>());
	stateMgr_.add((unsigned int)Player_EnumState::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)Player_EnumState::MOVE, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::HOLD, std::make_shared<PlayerState_Hold>());
	stateMgr_.add((unsigned int)Player_EnumState::JUMP, std::make_shared<PlayerState_Jump>());
	stateMgr_.add((unsigned int)Player_EnumState::QUICK, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)Player_EnumState::ATTACK2, std::make_shared<PlayerState_Attack2>());
	stateMgr_.add((unsigned int)Player_EnumState::DAMAGE, std::make_shared<PlayerState_Damage>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)Player_EnumState::STAND_BY));

	hp_ = 10;

	//world_->addActor(ActorGroup::Player, std::make_shared<PlayerBody_Connector>(world_, position_));

}

Player::~Player(){}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(*this, deltaTime);
	//1�t���[���O�̍��W
	prePosition = curPosition;
	//position_�ɃX�N���[���֌W�̈ړ��ʂ����ׂđ����Ă��邽�߃X�N���[�����X���C����t���Ă����Ȃ��Ȃ��Ă��܂�//
	position_ = (main_body_->getPosition() + sub_body_->getPosition())/2;
	//�ړ���̍��W
	curPosition = (Vector2((main_body_->getPosition() + sub_body_->getPosition()).x,
		(main_body_->getPosition() + sub_body_->getPosition()).y)) / 2;
	//���x���v�Z
	mVelo = prePosition - curPosition;
	

	body_.transform(Vector2(main_body_->getPosition().x, main_body_->getPosition().y), Vector2(sub_body_->getPosition().x, sub_body_->getPosition().y), 10);

	//animation_.changeAnim(motion_);
	//animation_.update(deltaTime);

	//���[�V�����J��
	//changeMotion(deltaTime)
	// �V�������W��ۑ�����
	//position_ = Vector3::Lerp(position_, curPosition, 0.8f);
}

void Player::onLateUpdate(float deltaTime){
	body_.transform(Vector2(main_body_->getPosition().x, main_body_->getPosition().y), Vector2(sub_body_->getPosition().x, sub_body_->getPosition().y), 10);

	body_.draw();

	if (main_body_ == nullptr || sub_body_ == nullptr)return;

	createOval(main_body_->getPosition(), sub_body_->getPosition(), body_.GetCapsule().component_.radius * 5);
}

void Player::onDraw() const {
	DrawFormatString(main_body_->getPosition().x, main_body_->getPosition().y, GetColor(255, 255, 255), "main");
	DrawFormatString(sub_body_->getPosition().x, sub_body_->getPosition().y, GetColor(255, 255, 255), "sub");
	DrawFormatString(300,555,GetColor(255, 255, 255), "Velo: %f,%f",mVelo.x,mVelo.y);
	DrawCircle(position_.x, position_.y, 10.0f, GetColor(255, 255, 255), TRUE);
}

void Player::onCollide(Actor & other){
	//if (stateMgr_.currentState() == (unsigned int)Player_EnumState::DAMAGE)return;


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

void Player::createOval(Vector3 main_pos, Vector3 sub_pos, int height) const
{
	Vector3 vec = (main_pos - sub_pos).Normalize();
	Vector2 sign = Vector2(MathHelper::Sign(vec.x), MathHelper::Sign(vec.y));
	vec *= sign.x;
	float angle = Vector3::Angle(Vector3::Right * sign.x, vec) * sign.y;

	Vector3 center = (main_pos + sub_pos) / 2;

	float dis = Vector3::Distance(main_pos, sub_pos);

	float a = 0;
	if (dis > MAX_NORMAL_LENGTH) a = dis;
	else a = MAX_NORMAL_LENGTH;

	float b = height;

	for (int i = 0; i < dis * 4; i++) {
		float x = i - dis * 2;
		float y = std::sqrt(b * b * (1 - ((x * x) / (a * a))));

		Vector3 pos_p = Vector3(x, y) * Matrix::CreateFromAxisAngle(Vector3::Forward, angle) + center;
		Vector3 pos_n = Vector3(x, -y) * Matrix::CreateFromAxisAngle(Vector3::Forward, angle) + center;
	
		DrawPixel(pos_p.x, pos_p.y, GetColor(0, 255, 0));
		DrawPixel(pos_n.x, pos_n.y, GetColor(0, 255, 0));
	}
}

void Player::createOval(Vector3 center, float width, int height) const{
}

void Player::createWindow()
{
	int handle, i, j, grhandle;

	// ��̃t���J���[�摜���쐬����
	handle = MakeARGB8ColorSoftImage(256, 256);

	// �c�����ɓ����O���f�[�V���������^���Ԃȉ摜���쐬����
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			// �F���Z�b�g
			DrawPixelSoftImage(handle, j, i, 255, 0, 0, i);
		}
	}

	// �������ǂ����킩��悤�ɉ�ʂ�΂œh��Ԃ�
	DrawBox(0, 0, 640, 480, GetColor(0, 255, 0), TRUE);

	// �O���t�B�b�N�n���h�����쐬
	grhandle = CreateGraphFromSoftImage(handle);

	// �g���I���������
	DeleteSoftImage(handle);

	// �O���t�B�b�N�n���h����`��
	DrawGraph(0, 0, grhandle, TRUE);
}


