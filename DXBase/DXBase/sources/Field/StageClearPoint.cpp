#include "StageClearPoint.h"
#include"../Input/InputMgr.h"

StageClearPoint::StageClearPoint(IWorld * world, Vector2 & position) :spriteID_(-1),
	MapChip(world, Vector2(position.x, position.y), "StageClearPoint", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}
StageClearPoint::StageClearPoint(int spriteID,IWorld * world, Vector2 & position) :spriteID_(spriteID),
	MapChip(world, Vector2(position.x, position.y), "StageClearPoint", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

StageClearPoint::StageClearPoint(std::shared_ptr<StageClearPoint> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "StageClearPoint", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

StageClearPoint::StageClearPoint(StageClearPoint & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), "StageClearPoint", std::make_shared<BoundingBox>(position, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true))
{
}

void StageClearPoint::set(Vector2 & pos)
{
	position_ = pos;
	body_ = std::make_shared<BoundingBox>(pos, Matrix::CreateRotationZ(0), CHIPSIZE, CHIPSIZE, true);
}

void StageClearPoint::onUpdate(float deltaTime)
{
}

void StageClearPoint::onDraw() const
{
	body_->draw(ResourceLoader::GetInstance().getTextureID(TextureID::CHIP4_TEX),0,inv_);
}

void StageClearPoint::onCollide(Actor & other)
{
}
