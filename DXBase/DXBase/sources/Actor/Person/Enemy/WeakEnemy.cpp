#include "WeakEnemy.h"

WeakEnemy::WeakEnemy(IWorld * world, const Vector3& position) :
	BaseEnemy(world, position)
{
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

void WeakEnemy::searchMove()
{
	BaseEnemy::searchMove();
}

void WeakEnemy::chaseMove()
{
	//BaseEnemy::chaseMove();
	BaseEnemy::findPlayer();
	color_ = GetColor(255, 0, 0);
	if (playerLength() > 10) changeState(State::Search, ENEMY_WALK);
	// ‚’¼ˆÚ“®
	//position_ += position_.Up * -speed_ * BaseEnemy::playerDirection().y;
	// ’ÇÕ
	position_ += BaseEnemy::playerNormalizeDirection() * -speed_;
}

void WeakEnemy::Attack()
{
	BaseEnemy::Attack();
}
