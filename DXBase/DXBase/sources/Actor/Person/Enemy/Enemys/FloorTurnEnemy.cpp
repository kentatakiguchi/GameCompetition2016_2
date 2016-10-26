#include "FloorTurnEnemy.h"
#include "../FloorSearchPoint.h"

FloorTurnEnemy::FloorTurnEnemy(IWorld * world, const Vector3 & position) :
	BaseEnemy(world, position, 64.0f / 2.0f)
{
}

void FloorTurnEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
}

void FloorTurnEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void FloorTurnEnemy::onMessage(EventMessage event, void *)
{
}

void FloorTurnEnemy::idel()
{
}

void FloorTurnEnemy::Attack()
{
}

void FloorTurnEnemy::searchMove()
{
	// position_ += enemyManager_.cliffMove(fsPointScript->isFloor()) * speed_;
	// ŠRˆÚ“®(‰¼)
	position_ += enemyManager_.cliffMove(true) * speed_;
}

void FloorTurnEnemy::chaseMove()
{
}
