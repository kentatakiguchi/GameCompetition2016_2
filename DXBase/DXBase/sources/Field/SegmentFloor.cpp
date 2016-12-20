#include "SegmentFloor.h"
#include"../Input/InputMgr.h"
//std::make_shared<BoundingSegment>((enemyPosition + playerPosition) / 2, Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (enemyPosition - playerPosition).Normalize()))), Vector2::Distance(enemyPosition, playerPosition), true)
SegmentFloor::SegmentFloor(IWorld * world, Vector2 & startPosition,Vector2& endPosition) :spriteID_(-1),
MapChip(world, Vector2(((startPosition.x+endPosition.x)/2), ((startPosition.y + endPosition.y) / 2)), "SegmentCollider", std::make_shared<BoundingSegment>(position_,
	Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (endPosition - startPosition).Normalize()))),(startPosition-endPosition).Length(),true))
{
	Vector2 Vector2(0, -1);
	rotate_ = 0;
}

SegmentFloor::SegmentFloor(int spriteID, IWorld * world, Vector2 & startPosition, Vector2& endPosition) :spriteID_(spriteID),
MapChip(world, Vector2(((startPosition.x + endPosition.x) / 2), ((startPosition.y + endPosition.y) / 2)), "SegmentCollider", std::make_shared<BoundingSegment>(position_,
	Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (endPosition - startPosition).Normalize()))), (startPosition - endPosition).Length(), true))
{
	rotate_ = 0;
}

SegmentFloor::SegmentFloor(std::shared_ptr<SegmentFloor> chip, IWorld * world, Vector2 & startPosition, Vector2& endPosition) :spriteID_(-1),
MapChip(world, Vector2(((startPosition.x + endPosition.x) / 2), ((startPosition.y + endPosition.y) / 2)), "SegmentCollider", std::make_shared<BoundingSegment>(position_,
	Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (endPosition - startPosition).Normalize()))), (startPosition - endPosition).Length(), true))
{
	rotate_ = 0;
}

SegmentFloor::SegmentFloor(SegmentFloor & chip, IWorld * world, Vector2 & startPosition, Vector2& endPosition) :spriteID_(-1),
MapChip(world, Vector2(((startPosition.x + endPosition.x) / 2), ((startPosition.y + endPosition.y) / 2)), "SegmentCollider", std::make_shared<BoundingSegment>(position_,
	Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (endPosition - startPosition).Normalize()))), (startPosition - endPosition).Length(), true))
{
	rotate_ = 0;
}

void SegmentFloor::set(Vector2 & pos)
{
	//position_ = pos;
	//body_ = CollisionBase(
	//	Vector2{ pos.x ,pos.y },
	//	Vector2{ pos.x + (CHIPSIZE),pos.y },
	//	Vector2{ pos.x ,pos.y + (CHIPSIZE) },
	//	Vector2{ pos.x + (CHIPSIZE),pos.y + (CHIPSIZE) });
}

void SegmentFloor::onUpdate(float deltaTime)
{
}

void SegmentFloor::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, inv_);
}

void SegmentFloor::onCollide(Actor & other)
{
}
