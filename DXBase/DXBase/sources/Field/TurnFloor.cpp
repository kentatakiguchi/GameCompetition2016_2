#include "TurnFloor.h"

TurnFloor::TurnFloor(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}
TurnFloor::TurnFloor(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

TurnFloor::TurnFloor(std::shared_ptr<TurnFloor> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

TurnFloor::TurnFloor(TurnFloor & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "TurnFloor", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
	, defaultPos_(position), moveVelocity(1), moveCount_(CHIPSIZE*TURNRANGE)
{
}

void TurnFloor::set(Vector2 & pos)
{
	position_ = pos;
	defaultPos_ = pos;
	body_ = std::make_shared<BoundingBox>(pos, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true);
}

void TurnFloor::onUpdate(float deltaTime)
{
	defaultPos_ = position_- (moveVelocity*CHIPSIZE*TURNRANGE)+Vector2(CHIPSIZE*2,CHIPSIZE*2);

	moveCount_+=1*(ceilf(deltaTime));
	if (moveCount_ % 360 == 0) {
		moveCount_ = 0;
	}
	
	moveVelocity.x = cos(moveCount_*MathHelper::Pi/180);
	moveVelocity.y = sin(moveCount_*MathHelper::Pi / 180);

	position_ = defaultPos_ + (moveVelocity*CHIPSIZE*TURNRANGE)- Vector2(CHIPSIZE * 2, CHIPSIZE * 2);

}

void TurnFloor::onDraw() const
{
	spriteID_ == -1 ? body_->draw(-1,inv_) : body_->draw(spriteID_, rotate_, inv_);
}

void TurnFloor::onCollide(Actor & other)
{
}
