#include "WeakEnemy.h"

WeakEnemy::WeakEnemy(IWorld * world, const Vector2& position) :
	BaseEnemy(world, position, 64.0f)
{
	BaseEnemy::Initialize();
}

void WeakEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
}

void WeakEnemy::onDraw() const
{
	BaseEnemy::onDraw();
}

void WeakEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void WeakEnemy::onMessage(EventMessage event, void *)
{
}

void WeakEnemy::idel()
{
	BaseEnemy::idle();
}

void WeakEnemy::attack()
{
	BaseEnemy::attack();
}

// ���G���̍s���ł�
void WeakEnemy::searchMove()
{
	//BaseEnemy::searchMove();
	// �ʏ펞�̑��x�ɖ߂�
	//speed_ = initSpeed_;
	//auto direction = 1;
	//if ((int)(stateTimer_ / 2.0f) % 2 == 1)
	//	direction = -1;
	//// �����ړ�
	//position_.y += -speed_ * direction;

	// �{�b�N�X�ړ�
	//position_ += enemyManager_.boxMove() * speed_;
}

// �ǐՎ��̍s���ł�
void WeakEnemy::chaseMove()
{
	// �ʏ펞�������߂ɂ���
	speed_ = initSpeed_ + 1.5f;
	auto point = position_ - player_->getPosition();
	// �v���C���[�̎��t�߂ɗ�����~�܂�
	if (std::abs(point.x) < speed_ ||
		std::abs(point.y) < speed_) return;
	// �ǐ�
	position_ += enemyManager_.getPlayerNormalizeDirection() * -speed_;
	//// �����ړ�
	//position_ += position_.Up * -speed_ * BaseEnemy::playerDirection().y;
}
