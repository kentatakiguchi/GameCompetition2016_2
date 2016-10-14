#include "BaseEnemy.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../Base/ActorGroup.h"
#include "Enemy_AttackRange.h"

BaseEnemy::BaseEnemy(IWorld * world, const Vector3& position) :
	Actor(world, "BaseEnemy", position, BoundingSphere(1.0f)),
	hp_(10),
	ap_(0),
	speed_(0.3f),
	color_(GetColor(255, 255, 255)),
	stateTimer_(0.0f),
	state_(State::Idel),
	animation_(),
	player_(nullptr)
{
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::onUpdate(float deltaTime)
{
	// ��Ԃ̍X�V
	updateState(deltaTime);
	// �A�j���[�V�����̕ύX
	//animation_.change(motion_);
	// �A�j���[�V�����̍X�V
	//animation_.update(deltaTime);
}

void BaseEnemy::onDraw() const
{
	//auto vec2Position = Vector2(position_.x, position_.y);
	//animation_.draw(vec2Position, NULL, 1.0f, 0.0f);
	//DrawRotaGraph2(position_.x, position_.y, 0.5f, 0.5f, 0.0f, 0.0f, 1, 1);
	DrawSphere3D(Vector3::Vector3ToVECTOR(position_), 1.0f, 16, color_, GetColor(0, 0, 0), 1);
}

void BaseEnemy::onCollide(Actor & actor)
{
	if (actor.getName() != "Player_AttackRange" || actor.getName() != "Player") return;
	// �_���[�W
	// hp_ -= player->GetAP(); �Ƃ�
	hp_ -= 10;
	if (hp_ <= 0) changeState(State::Dead, ENEMY_DEAD);
	else changeState(State::Damage, ENEMY_DAMAGE);
	body_.enabled = false;
}

void BaseEnemy::onMessage(EventMessage event, void *)
{
}

void BaseEnemy::idle()
{
	color_ = GetColor(255, 255, 255);
	//position_ += BaseEnemy::playerNormalizeDirection() * -speed_;
	if (playerLength() < 100) changeState(State::Search, ENEMY_WALK);
}
// ���G�ړ����܂�(�f�t�H���g)
void BaseEnemy::searchMove()
{
	// �v���C���[�̑{��
	findPlayer();
	color_ = GetColor(0, 255, 0);
	// ��苗�����Ȃ�ǐՂ���
	if (playerLength() <= 10) changeState(State::Chase, ENEMY_WALK);
	else if(playerLength() >= 100) changeState(State::Idel, ENEMY_IDLE);
}
// �v���C���[��ǐՂ��܂�(�f�t�H���g)
void BaseEnemy::chaseMove()
{
	// �v���C���[�̑{��
	findPlayer();
	color_ = GetColor(255, 0, 0);
	if (playerLength() > 10) changeState(State::Search, ENEMY_WALK);
	// �O���Ɉړ�(��)
	//auto distance = position_ - player_->getPosition();
	////auto direction = 1.0f;
	//if (distance.x < 0)
	//	direction_ = -1;
	//else if(distance.x > 0) direction_ = 1;
	//else direction_ = 0;

	//// ���������Ɉړ�
	//position_ += position_.Left * -speed_ * playerDirection().x;
	//// �ړ�
	//position_ += BaseEnemy::playerNormalizeDirection() * -speed_;
}

//void BaseEnemy::shortDistanceAttack()
//{
//}
//
//void BaseEnemy::centerDistanceAttack()
//{
//}
//
//void BaseEnemy::longDistanceAttack()
//{
//}

void BaseEnemy::Attack()
{
	/*world_->addActor(
		ActorGroup::Enemy_AttackRange, std::make_shared<Enemy_AttackRange>(world_, position_));*/
	if (stateTimer_ >= 3.0f)
		changeState(State::Search, ENEMY_IDLE);
}

void BaseEnemy::damageMove()
{
	color_ = GetColor(100, 100, 100);
	if (stateTimer_ >= 3.0f)
		changeState(State::Chase, ENEMY_WALK);
}

void BaseEnemy::deadMove()
{
	//if (stateTimer_ >= 3.0f) dead();
}

void BaseEnemy::changeState(State state, unsigned int motion)
{
	state_ = state;
	stateTimer_ = 0.0f;
	motion_ = motion;
}

void BaseEnemy::findPlayer()
{
	// �v���C���[�����Ȃ���Αҋ@���
	if (player_ == nullptr) {
		changeState(State::Idel, ENEMY_IDLE);
		return;
	}
}

// �v���C���[�Ƃ̋�����Ԃ��܂�
float BaseEnemy::playerLength()
{
	// �v���C���[�̈ʒu���擾
	Vector3 target = player_->getPosition();
	target_ = Vector2(target.x, target.y);
	Vector2 vec2Position_ = Vector2(position_.x, position_.y);
	Vector2 length = target_ - vec2Position_;
	return length.Length();
}

// �v���C���[�Ƃ̕�����P�ʃx�N�g���Ŏ擾���܂�
Vector2 BaseEnemy::playerDirection()
{
	// �����̌v�Z
	auto distance = position_ - player_->getPosition();
	auto direction = Vector2().Zero;
	//auto direction = 1.0f;
	// �����̒l����
	// X
	if (distance.x < 0)
		direction.x = -1;
	else if (distance.x > 0)
		direction.x = 1;
	else direction.x = 0;
	// Y
	if (distance.y < 0)
		direction.y = 1;
	else if (distance.x > 0)
		direction.y = -1;
	else direction.y = 0;
	return direction;
}

// �v���C���[�Ƃ̕����𐳋K�����ꂽ�x�N�g���Ŏ擾���܂�
Vector3 BaseEnemy::playerNormalizeDirection()
{
	// �����̌v�Z
	auto distance = position_ - player_->getPosition();
	//// �ϊ�
	//auto nomaDistance = Vector2(distance.x, distance.y);
	//// ���K��
	//nomaDistance = nomaDistance.Normalize(nomaDistance);
	//auto distance3 = Vector3(nomaDistance.x, nomaDistance.y, 0.0f);
	distance = distance.Normalize(distance);
	return distance;
}

// �G�����ݍ��܂ꂽ���̃X�P�[���|�C���g��Ԃ��܂�
float BaseEnemy::getSP()
{
	return 1.0f;
}

// �G�̑傫����Ԃ��܂�
int BaseEnemy::getScale()
{
	return 1;
}

void BaseEnemy::updateState(float deltaTime)
{
	// �v���C���[�̑{��
	player_ = world_->findActor("Player");

	switch (state_)
	{
	case State::Idel: idle(); break;
	case State::Search: searchMove(); break;
	case State::Chase: chaseMove(); break;
	case State::Attack: Attack(); break;
		// State::Return: ; break;
	case State::Damage: damageMove(); break;
	case State::Dead: deadMove(); break;
	}

	stateTimer_ += deltaTime;
}
