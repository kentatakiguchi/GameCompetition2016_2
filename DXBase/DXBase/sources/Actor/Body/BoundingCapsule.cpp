#include "BoundingCapsule.h"
#include"BoundingBox.h"
#include"BoundingSegment.h"
#include"BoundingCircle.h"

BoundingCapsule::BoundingCapsule(Vector2 pos, Matrix mat, float rad, float length,bool enable):
	Body(CollisionType::CapsuleCol,true,pos,mat,rad,length)
{
}

bool BoundingCapsule::intersects(const BoundingBox & other) const{
	if (!other.enabled_ || !enabled_)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	Vector2 othersize_ = Vector2(other.width_ / 2, other.height_ / 2);//���S�_

	Vector2 otherpoints[4] = {
		(-othersize_*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//����_�̉�]
		(Vector2(othersize_.x, -othersize_.y)*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//�E��_�̉�]
		(Vector2(-othersize_.x, othersize_.y)*other.mat_.RotationMatrix()) + (other.position_ + othersize_),//�����_�̉�]
		(othersize_*other.mat_.RotationMatrix()) + (other.position_ + othersize_)//�E���_�̉�]
	};

	Vector2 thispoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};

	//���蔲��
	for (int i = 0; i < 4; i++)
	{
		if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[intSet[i][0]], otherpoints[intSet[i][1]]))return true;
	}
	if (CollisionUtil::Intersects_Box_Capsule(
		otherpoints[0], otherpoints[1], otherpoints[2], otherpoints[3],
		thispoints[0], thispoints[1], radius_)) return true;

	return false;
}

bool BoundingCapsule::intersects(const BoundingCapsule & other) const
{
	if (!other.enabled_ || !enabled_)return false;

	Vector2 thispoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};
	Vector2 otherpoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};

	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Capsule_Capsule(thispoints[0], thispoints[1], radius_, otherpoints[0], otherpoints[1], other.radius_)) return true;

	return false;
}

bool BoundingCapsule::intersects(const BoundingSegment & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	Vector2 thispoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};
	Vector2 otherpoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		other.position_ + (Vector2::Down *other.length_ / 2)*other.mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		other.position_ + (Vector2::Up *other.length_ / 2)*other.mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};
	if (CollisionUtil::IsCross(previousPosition_, position_, otherpoints[0], otherpoints[1]))return true;

	if (CollisionUtil::Intersects_Segment_Capsule(otherpoints[0], otherpoints[1], thispoints[0], thispoints[1], radius_))return true;

	return false;
}

bool BoundingCapsule::intersects(const BoundingCircle & other) const
{
	if (!enabled_ || !other.enabled_)return false;

	Vector2 thispoints[2] = {
		//��Ɖ��̒������̓_���Aposition��mat_Quaternion���g���ĉ�]�������l�����Z���ċ��߂Ă���
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};

	if (CollisionUtil::IsCross(other.previousPosition_, other.position_, thispoints[0], thispoints[1]))return true;

	if (CollisionUtil::Intersects_Circle_Capsule(other.position_, other.radius_, thispoints[0], thispoints[1], radius_))return true;

	return false;
}

void BoundingCapsule::draw(int spriteID, Matrix inv) const
{
	Vector2 thispoints[2] = {
		position_ + (Vector2::Down *length_ / 2)*mat_.RotationMatrix(),//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
		position_ + (Vector2::Up *length_ / 2)*mat_.RotationMatrix()//���_�𒆐S�ɁA���W��a�x��]������̂�Quaternion�A������position�𑫂�
	};

	Vector3 pos0 = Vector3(thispoints[0].x, thispoints[0].y) * inv;
	Vector3 pos1 = Vector3(thispoints[1].x, thispoints[1].y) * inv;

	//DrawCircle(pos0.x, pos0.y, component_.radius, GetColor(255, 0, 0), FALSE);
	//DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0), FALSE);
	//DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0), FALSE);
	//DrawCircle(pos1.x, pos1.y, component_.radius, GetColor(255, 0, 0), FALSE);

	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;

}

void BoundingCapsule::draw(int spriteID, int rotation, Matrix inv) const{
	draw(spriteID, inv);
}

IBodyPtr BoundingCapsule::translate(const Vector2 & pos) const{
	return std::make_shared<BoundingCapsule>(position_ + pos, mat_, radius_, length_, enabled_);
}

IBodyPtr BoundingCapsule::transform(const Matrix & mat) const{
	return std::make_shared<BoundingCapsule>(position_ + mat.TranslationVec2(), mat_*mat, radius_*mat.Scale().x, length_*mat.Scale().y, enabled_);//���a��Mat��x,������Mat��y
}

