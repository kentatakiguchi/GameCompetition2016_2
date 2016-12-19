#include "BoundingBox.h"
#include"BoundingSegment.h"
#include"BoundingCircle.h"
#include"BoundingCapsule.h"
BoundingBox::BoundingBox(Vector2 pos, Matrix mat, float width, float height, bool enable) :
	Body(CollisionType::BoxCol, true, pos, mat, 0, 0, width, height)
{

}
bool BoundingBox::intersects(const BoundingBox & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 size_ = Vector2(width_ / 2, height_ / 2);//中心点

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};

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

	if (CollisionUtil::Intersects_Box_Box(
		thispoints[0], thispoints[1], thispoints[2], thispoints[3],
		otherpoints[0], otherpoints[1], otherpoints[2], otherpoints[3])) {
		return true;
	}
	return false;
}
bool BoundingBox::intersects(const BoundingCapsule & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 size_ = Vector2(width_ / 2, height_ / 2);//中心点

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};

	Vector2 otherpoints[2] = {
		//上と下の長さ分の点を、positionにmat_Quaternionを使って回転させた値を加算して求めている
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す

	};

	//すり抜け
	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Box_Capsule(
		thispoints[0], thispoints[1], thispoints[2], thispoints[3],
		otherpoints[0], otherpoints[1], other.radius_)) return true;

	return false;
}
bool BoundingBox::intersects(const BoundingSegment & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 size_ = Vector2(width_ / 2, height_ / 2);//中心点

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};

	Vector2 otherpoints[2] = {
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Box(otherpoints[0], otherpoints[1], thispoints[0], thispoints[1], thispoints[2], thispoints[3]))return true;

	return false;
}
bool BoundingBox::intersects(const BoundingCircle & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 size_ = Vector2(width_ / 2, height_ / 2);

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};
	for (int i = 0; i < 4; i++) {
		if (CollisionUtil::IsCross(other.previousPosition_, other.position_, thispoints[intSet[i][0]], thispoints[intSet[i][1]])) return true;
	}

	if (CollisionUtil::Intersects_Box_Circle(thispoints[0], thispoints[1], thispoints[2], thispoints[3], other.position_, other.radius_)) return true;

	return false;
}
void BoundingBox::draw(int spriteID, Matrix inv) const
{
	Vector2 size_ = Vector2(width_ / 2, height_ / 2);//中心点

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};

	Vector3 pos0 = Vector3(thispoints[0].x, thispoints[0].y) * inv;
	Vector3 pos1 = Vector3(thispoints[1].x, thispoints[1].y) * inv;
	Vector3 pos2 = Vector3(thispoints[2].x, thispoints[2].y) * inv;
	Vector3 pos3 = Vector3(thispoints[3].x, thispoints[3].y) * inv;

	DrawGraph(pos0.x, pos0.y, spriteID, TRUE);

}
void BoundingBox::draw(int spriteID, int rotation, Matrix inv) const
{
	Vector2 size_ = Vector2(width_ / 2, height_ / 2);//中心点

	Vector2 thispoints[4] = {
		(-size_*mat_.RotationMatrix()) + (position_ + size_),//左上点の回転
		(Vector2(size_.x, -size_.y)*mat_.RotationMatrix()) + (position_ + size_),//右上点の回転
		(Vector2(-size_.x, size_.y)*mat_.RotationMatrix()) + (position_ + size_),//左下点の回転
		(size_*mat_.RotationMatrix()) + (position_ + size_)//右下点の回転
	};

	Vector3 pos0 = Vector3(thispoints[0].x, thispoints[0].y) * inv;
	Vector3 pos1 = Vector3(thispoints[1].x, thispoints[1].y) * inv;
	Vector3 pos2 = Vector3(thispoints[2].x, thispoints[2].y) * inv;
	Vector3 pos3 = Vector3(thispoints[3].x, thispoints[3].y) * inv;

	Vector2 centerMath1, centerMath2, center;

	centerMath1.x = (pos0.x + pos1.x) / 2;
	centerMath1.y = (pos0.y + pos1.y) / 2;
	centerMath2.x = (pos2.x + pos3.x) / 2;
	centerMath2.y = (pos2.y + pos3.y) / 2;
	center = (centerMath1 + centerMath2) / 2;

	DrawRotaGraph(center.x, center.y, 1, (rotation*MathHelper::Pi / 180), spriteID, TRUE);

	//DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0));
	//DrawLine(pos1.x, pos1.y, pos3.x, pos3.y, GetColor(255, 0, 0));
	//DrawLine(pos0.x, pos0.y, pos2.x, pos2.y, GetColor(255, 0, 0));
	//DrawLine(pos2.x, pos2.y, pos3.x, pos3.y, GetColor(255, 0, 0));

}

IBodyPtr BoundingBox::translate(const Vector2 & pos) const
{
	return std::make_shared<BoundingBox>(position_ + pos, mat_, width_, height_, enabled_);
}
IBodyPtr BoundingBox::transform(const Matrix & mat) const
{
	return std::make_shared<BoundingBox>(position_ + mat.TranslationVec2(), mat_*mat, width_*mat.Scale().x, height_*mat.Scale().y, enabled_);
}
