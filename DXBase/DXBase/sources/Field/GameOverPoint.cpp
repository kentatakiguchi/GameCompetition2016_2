#include "GameOverPoint.h"
#include"../Input/InputMgr.h"

GameOverPoint::GameOverPoint(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "GameOverPoint", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}
GameOverPoint::GameOverPoint(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "GameOverPoint", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

GameOverPoint::GameOverPoint(std::shared_ptr<GameOverPoint> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "GameOverPoint", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

GameOverPoint::GameOverPoint(GameOverPoint & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "GameOverPoint", std::make_shared<BoundingBox>(Vector2(0, 0), Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

void GameOverPoint::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(Vector2(0, 0), rotation_, CHIPSIZE, CHIPSIZE, true);
}

void GameOverPoint::onUpdate(float deltaTime)
{
}

void GameOverPoint::onDraw() const
{
	body_->draw(ResourceLoader::GetInstance().getTextureID(TextureID::CHIP1_TEX), 0, inv_);
}

void GameOverPoint::onCollide(Actor & other)
{
}
