#include "BoundingCapsule.h"
#include"BoundingBox.h"
#include"BoundingSegment.h"
#include"BoundingCircle.h"


BoundingCircle::BoundingCircle(Vector2 pos, Matrix mat, float rad, bool enable) :
	Body(CollisionType::CircleCol, enable, pos, mat, rad)
{
}

bool BoundingCircle::intersects(const BoundingBox & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 othersize_ = Vector2(other.width_ / 2, other.height_ / 2);//中心点
	Vector2 otherpoints[4] = {
		(-othersize_*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//左上点の回転
		(Vector2(othersize_.x, -othersize_.y)*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//右上点の回転
		(Vector2(-othersize_.x, othersize_.y)*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//左下点の回転
		(othersize_*other.mat_.RotationMatrix()) + (other.position_ + othersize_)//右下点の回転
	};

	for (int i = 0; i < 4; i++)
	{
		if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[intSet[i][0]], otherpoints[intSet[i][1]]))return true;
	}

	if (CollisionUtil::Intersects_Box_Circle(otherpoints[0], otherpoints[1], otherpoints[2], otherpoints[3], position_, radius_))return true;

	return false;
}

bool BoundingCircle::intersects(const BoundingCapsule & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	//すり抜けたか
	Vector2 otherpoints[2] = {
		//上と下の長さ分の点を、positionにmat_Quaternionを使って回転させた値を加算して求めている
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Circle_Capsule(position_, radius_, otherpoints[0], otherpoints[1], other.radius_))return true;

	return false;
	//DrawCircle(A0P.x, A0P.y,3, GetColor(255, 255, 255));
	//DrawCircle(A0M.x, A0M.y,3, GetColor(255, 255, 255));
	//DrawCircle(A1P.x, A1P.y,3, GetColor(255, 255, 255));
	//DrawCircle(A1M.x, A1M.y,3, GetColor(255, 255, 255));
}

bool BoundingCircle::intersects(const BoundingSegment & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	Vector2 otherpoints[2] = {
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Circle(otherpoints[0], otherpoints[1], position_, radius_))return true;

	return false;
}

bool BoundingCircle::intersects(const BoundingCircle & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	if (CollisionUtil::IsCross(previousPosition_, position_, other.previousPosition_, other.position_))return true;

	if (CollisionUtil::Intersects_Circle_Circle(position_, radius_, other.position_, other.radius_))return true;

	return false;
}

void BoundingCircle::draw(int spriteID, Matrix inv) const
{
	Vector3 pos0 = Vector3(position_.x, position_.y) * inv;

}

void BoundingCircle::draw(int spriteID, int rotation, Matrix inv) const
{
	Vector3 pos0 = Vector3(position_.x, position_.y) * inv;

}

IBodyPtr BoundingCircle::translate(const Vector2 & pos) const
{
	return std::make_shared<BoundingCircle>(position_ + pos, mat_, radius_, enabled_);
}

IBodyPtr BoundingCircle::transform(const Matrix & mat) const
{
	return std::make_shared<BoundingCircle>(position_ + mat.TranslationVec2(), mat_*mat, radius_*mat.Scale().y, enabled_);
}
