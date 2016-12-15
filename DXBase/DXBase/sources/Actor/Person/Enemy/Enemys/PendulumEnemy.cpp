#include "PendulumEnemy.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

PendulumEnemy::PendulumEnemy(IWorld * world, const Vector3 & position) :
	BaseEnemy(world, position, 64.0f / 2.0f),
	threadPoint_(Vector3::Zero),
	rotateStr_("")
{
}

void PendulumEnemy::onUpdate(float deltaTime)
{
	BaseEnemy::onUpdate(deltaTime);
	threadPoint_ = enemyManager_.getThreadPoint();
	rotateStr_ = std::to_string(enemyManager_.rotate_ * MathHelper::Pi / 180.0f);
}

void PendulumEnemy::onDraw() const
{
	BaseEnemy::onDraw();
	DrawGraph(threadPoint_.x - scale_, threadPoint_.y - scale_,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	DrawLine(
		position_.x, position_.y,
		threadPoint_.x, threadPoint_.y, GetColor(255, 0, 0));

	DrawString(
		position_.x - scale_,
		position_.y - 50 - scale_, rotateStr_.c_str(), GetColor(255, 255, 255));
}

void PendulumEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
}

void PendulumEnemy::onMessage(EventMessage event, void *)
{
}

void PendulumEnemy::idel()
{
}

void PendulumEnemy::Attack()
{
}

void PendulumEnemy::searchMove()
{
	position_ = enemyManager_.threadMove();
}

void PendulumEnemy::chaseMove()
{
}
