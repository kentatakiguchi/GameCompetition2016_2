#include "BoundingSegment.h"
#include"BoundingCapsule.h"
#include"BoundingBox.h"
#include"BoundingCircle.h"

BoundingSegment::BoundingSegment(Vector2 pos, Matrix mat, float length, bool enable) :
	Body(CollisionType::SegmentCol, enable, pos, mat, 0, length)//lengthは全体の長さ
{

}

bool BoundingSegment::intersects(const BoundingBox & other) const
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

	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	for (int i = 0; i < 4; i++) {
		if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[intSet[i][0]], otherpoints[intSet[i][1]]))return true;
	}

	if (CollisionUtil::Intersects_Segment_Box(otherpoints[0], otherpoints[1], thispoints[0], thispoints[1], thispoints[2], thispoints[3]))return true;

	return false;
}

bool BoundingSegment::intersects(const BoundingCapsule & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};
	Vector2 otherpoints[2] = {
		//上と下の長さ分の点を、positionにmat_Quaternionを使って回転させた値を加算して求めている
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(thispoints[0], thispoints[1], otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Capsule(thispoints[0], thispoints[1], otherpoints[0], otherpoints[1], other.radius_))return true;

	return false;
}

bool BoundingSegment::intersects(const BoundingSegment & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	int intSet[][2] = { { 0,1 } };

	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};
	Vector2 otherpoints[2] = {
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Segment(thispoints[0], thispoints[1], otherpoints[0], otherpoints[1]))return true;

	return false;
}

bool BoundingSegment::intersects(const BoundingCircle & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};

	if (CollisionUtil::IsCross(other.previousPosition_, other.position_, thispoints[0], thispoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Circle(thispoints[0], thispoints[1], other.position_, other.radius_))return true;

	return false;
}

void BoundingSegment::draw(int spriteID, Matrix inv) const
{
	//if (!enabled)return;

	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//原点を中心に、座標をa度回転させるのがQuaternion、こいつにpositionを足す
	};


	Vector3 pos0, pos1;

	if (thispoints[0].y <= thispoints[1].y) {
		pos0 = Vector3(thispoints[0].x, thispoints[0].y) * inv;
		pos1 = Vector3(thispoints[1].x, thispoints[1].y) * inv;
	}
	else {
		pos0 = Vector3(thispoints[1].x, thispoints[1].y) * inv;
		pos1 = Vector3(thispoints[0].x, thispoints[0].y) * inv;

	}

	//DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0));

	DrawModiGraph(pos1.x, pos1.y, pos0.x, pos0.y, pos0.x, pos0.y, pos0.x, pos1.y, spriteID, TRUE);
	//DrawBox(component_.point[0].x, component_.point[0].y,
	//	component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0), FALSE);
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}

void BoundingSegment::draw(int spriteID, int rotation, Matrix inv) const
{
	draw(spriteID, inv);
}

IBodyPtr BoundingSegment::translate(const Vector2 & pos) const{
	return std::make_shared<BoundingSegment>(position_ + pos, mat_, length_, enabled_);
}

IBodyPtr BoundingSegment::transform(const Matrix & mat) const{
	return std::make_shared<BoundingSegment>(position_ + mat.TranslationVec2(), mat_*mat, length_*mat.Scale().y, enabled_);
}

std::vector<Vector2> BoundingSegment::points() const{
	std::vector<Vector2> points = std::vector<Vector2>();
	points.push_back(position_ + (Vector2::Down * length_ / 2) * mat_.RotationMatrix());
	points.push_back(position_ + (Vector2::Up * length_ / 2) * mat_.RotationMatrix());
	return points;
}

