#include "CollisionBase.h"
#include"../../Define.h"

CollisionBase::CollisionBase():box_(),capsule_(),circle_(),segment_(),type_(NoneCol)
{
}

CollisionBase::CollisionBase(const Vector2 & topLeft, const Vector2 & topRight, const Vector2 & bottomLeft, const Vector2 & bottomRight) :
	box_(topLeft, topRight, bottomLeft, bottomRight), capsule_(),segment_(),circle_(), type_(BoxCol)
{
	
}

CollisionBase::CollisionBase(Vector2& startPoint, Vector2& endPoint, float capsuleRadius):
	box_(),capsule_(startPoint,endPoint,capsuleRadius),segment_(),circle_(),type_(CapsuleCol)
{

}

CollisionBase::CollisionBase(Vector2 & center, float circleRadius):
	circle_(center, circleRadius), box_(), capsule_(), segment_(),  type_(CircleCol)
{
}

CollisionBase::CollisionBase(Vector2 & startPoint, Vector2 & endPoint):
	box_(), capsule_(), segment_(startPoint,endPoint), circle_(), type_(SegmentCol)
{

}

void CollisionBase::setPosition(Vector2 position)
{
	position_ = position;
	previousPosition_ = position;
	switch (type_)
	{
	case BoxCol:
	{
		box_.position_ = position;
		box_.previousPosition_ = position;
		
		movePoint[0] = position - box_.component_.point[0];
		movePoint[1] = position - box_.component_.point[1];
		movePoint[2] = position - box_.component_.point[2];
		movePoint[3] = position - box_.component_.point[3];
		
		for (int i = 0; i < 4; i++)
		{
			myvect[i] = movePoint[i];
		}

		//leng[0] = (movePoint[0] + testVect[0]).Length();
		//leng[1] = (movePoint[1] + testVect[1]).Length();
		//leng[2] = (movePoint[2] + testVect[2]).Length();
		//leng[3] = (movePoint[3] + testVect[3]).Length();

		break;
	}
	case CapsuleCol:
	{
		capsule_.position_ = position;
		capsule_.previousPosition_ = position;

		movePoint[0] = position - capsule_.component_.point[0];
		movePoint[1] = position - capsule_.component_.point[1];
		radius_ = capsule_.component_.radius;
		break;
	}
	case CircleCol:
	{	
		circle_.position_ = position;
		circle_.previousPosition_ = position;

		radius_ = circle_.component_.radius;
	break;
	}
	case SegmentCol:
	{
		segment_.position_ = position;
		segment_.previousPosition_ = position;

		movePoint[0] = position - segment_.component_.point[0];
		movePoint[1] = position - segment_.component_.point[1];

		break;
	}
	case NoneCol:
	{	break;
	}
	default:
	{	break;
	}
	}
}
Vector2 CollisionBase::setSegmentPoint(Vector2& position,Vector2 & startPoint, Vector2 & endPoint)
{
	if (type_ != CollisionType::SegmentCol)return Vector2::Zero;

	movePoint[0] =position-startPoint;
	movePoint[1] =position-endPoint;

	return (startPoint + endPoint)/2;
}

void CollisionBase::RotateCapsule(Vector2 point1, Vector2 point2,float radius)
{
	if (type_ != CollisionType::CapsuleCol) return;

	movePoint[0] = point1;
	movePoint[1] = point2;
	radius_ = radius;
}
void CollisionBase::RotateSegment(Vector2 point1, Vector2 point2)
{
	if (type_ != CollisionType::SegmentCol) return;

	movePoint[0] = point1;
	movePoint[1] = point2;
}
void CollisionBase::RotateBox(int rotation)
{
	if (type_ != CollisionType::BoxCol) return;



	for (int i = 0; i < 4; i++)
	{
		Vector2 thisVect;

		thisVect = myvect[i];

		Vector2 vect;
		vect.x = (CHIPSIZE*TURNLESS_FLOOR_SIZE) / 2;
		vect.y = (CHIPSIZE) /2;

		thisVect -= vect;


		movePoint[i].x = thisVect.x * cosf(rotation * MathHelper::Pi / 180) - thisVect.y * sinf(rotation * MathHelper::Pi / 180);
		movePoint[i].y = thisVect.x * sinf(rotation * MathHelper::Pi / 180) + thisVect.y * cosf(rotation * MathHelper::Pi / 180);
		
		movePoint[i] += vect;
		
	}
	//float turnx;
	//float turny;
	//Vector2 turn;


	//turnx= cosf((rotates[0]) * MathHelper::Pi / 180);
	//turny= sinf((rotates[0]) * MathHelper::Pi / 180);
	//turn= Vector2(turnx, turny);
	//movePoint[0].x = (turn.x*32);
	//movePoint[0].y =(turn.y*16);

	//turnx = cosf((rotates[1])*MathHelper::Pi / 180);
	//turny = sinf((rotates[1])*MathHelper::Pi / 180);
	//turn = Vector2(turnx, turny);
	//movePoint[1].x = (turn.x * 32);
	//movePoint[1].y = (turn.y * 16);

	//turnx = cosf((rotates[2])*MathHelper::Pi / 180);
	//turny = sinf((rotates[2])*MathHelper::Pi / 180);
	//turn = Vector2(turnx, turny);
	//movePoint[2].x = (turn.x * 32);
	//movePoint[2].y = (turn.y * 16);

	//turnx = cosf((rotates[3])*MathHelper::Pi / 180);
	//turny = sinf((rotates[3])*MathHelper::Pi / 180);
	//turn = Vector2(turnx, turny);
	//movePoint[3].x = (turn.x * 32);
	//movePoint[3].y = (turn.y * 16);

	for (int i = 0; i < 4; i++)
		DrawFormatString(movePoint[i].x, movePoint[i].y, GetColor(255, 255, 255), "%d", i);
	//leng = (position_ - movePoint[1].Normalize()).Length();
	//movePoint[1] = turn + Vector2(1, 1)*leng;
	//leng = (position_ - movePoint[2].Normalize()).Length();
	//movePoint[2] = turn + Vector2(1, 1)*leng;
	//leng = (position_ - movePoint[3].Normalize()).Length();
	//movePoint[3] = turn + Vector2(1, 1)*leng;
}
void CollisionBase::update(Vector2 position)
{
	MovePos(position);
}

void CollisionBase::draw(Matrix inv) const
{
	switch (type_)
	{
	case BoxCol:
		box_.draw(inv);
		break;
	case CapsuleCol:
		capsule_.draw(inv);
		break;
	case CircleCol:
		circle_.draw(inv);
		break;
	case SegmentCol:
		segment_.draw(inv);
		break;
	case NoneCol:
		break;
	default:
		break;
	}
}

void CollisionBase::draw(int spriteID, Matrix inv) const
{
	switch (type_)
	{
	case BoxCol:
		box_.draw(spriteID, inv);
		break;
	case CapsuleCol:
		capsule_.draw(inv);
		break;
	case CircleCol:
		circle_.draw(inv);
		break;
	case SegmentCol:
		segment_.draw(inv);
		break;
	case NoneCol:
		break;
	default:
		break;
	}

}
void CollisionBase::draw(int spriteID,int rotation, Matrix inv) const
{
	switch (type_)
	{
	case BoxCol:
	{	box_.draw(spriteID, rotation, inv);
		break;
	}
	case CapsuleCol:
	{	capsule_.draw(inv);
		break;
	}
	case CircleCol:
	{	circle_.draw(inv);
		break;
	}
	case SegmentCol:
	{		segment_.draw(inv);
		break;
	}
	case NoneCol:
	{	Vector3 pos = Vector3(position_.x, position_.y)*inv;
		DrawTurnGraph(pos.x, pos.y, spriteID, rotation);
		break;
	}
	default:
		break;
	}

}

void CollisionBase::transform(Vector2 & topLeft, Vector2 & topRight, Vector2 & bottomLeft, Vector2 & bottomRight)
{
	box_= box_.transform(topLeft,topRight,bottomLeft,bottomRight);
}

void CollisionBase::transform(Vector2 & startPoint, Vector2 & endPoint, float capsuleRadius)
{
	capsule_= capsule_.transform(startPoint, endPoint, capsuleRadius);
}

void CollisionBase::transform(Vector2 & center, float circleRadius)
{
	circle_ = circle_.transform(center, circleRadius);
}

void CollisionBase::transform(Vector2 & startPoint, Vector2 & endPoint)
{
	segment_ = segment_.transform(startPoint, endPoint);
}

void CollisionBase::MovePos(Vector2 & position)
{
	previousPosition_ = position_;
	position_ = position;
	switch (type_)
	{
	case BoxCol:
		box_ = BoundingBox(Vector2( position + movePoint[0] ), Vector2( position + movePoint[1] ), Vector2( position + movePoint[2] ), Vector2( position + movePoint[3] ));
		box_.previousPosition_ = previousPosition_;
		box_.position_ = position;
		break;
	case CapsuleCol:
		capsule_ = BoundingCapsule(Vector2( position + movePoint[0] ), Vector2( position + movePoint[1] ), radius_);
		capsule_.previousPosition_ = previousPosition_;
		capsule_.position_ = position;
		break;
	case CircleCol:		
		circle_ = BoundingCircle(position,radius_);
		circle_.previousPosition_ = previousPosition_;
		circle_.position_ = position;
		break;
	case SegmentCol:	
		segment_ = BoundingSegment(Vector2( position + movePoint[0] ), Vector2( position + movePoint[1] ));
		segment_.previousPosition_ = previousPosition_;
		segment_.position_ = position;
		break;
	case NoneCol:
		break;
	default:
		break;
	}
}

void CollisionBase::translate(Vector2 position)
{
	switch (type_)
	{
	case BoxCol:
		box_= box_.translate(position);
		break;
	case CapsuleCol:
		capsule_=capsule_.translate(position);
		break;
	case CircleCol:
		circle_ = circle_.translate(position);
		break;
	case SegmentCol:
		segment_ = segment_.translate(position);
		break;
	case NoneCol:
		break;
	default:
		break;
	}
}

bool CollisionBase::intersects(CollisionBase & other)
{
	switch (type_)
	{
	case BoxCol:
		switch (other.type_)
		{
		case BoxCol:
			return box_.intersects(other.box_);
			break;
		case CapsuleCol:
			return box_.intersects(other.capsule_);
			break;
		case CircleCol:
			return box_.intersects(other.circle_);
			break;
		case SegmentCol:
			return box_.intersects(other.segment_);
			break;
		case NoneCol:
			break;
		default:
			break;
		}
		break;
	case CapsuleCol:
		switch (other.type_)
		{
		case BoxCol:
			return capsule_.intersects(other.box_);
			break;
		case CapsuleCol:
			return capsule_.intersects(other.capsule_);
			break;
		case CircleCol:
			return capsule_.intersects(other.circle_);
			break;
		case SegmentCol:
			return capsule_.intersects(other.segment_);
			break;
		case NoneCol:
			break;
		default:
			break;
		}
		break;
	case CircleCol:
		switch (other.type_)
		{
		case BoxCol:
			return circle_.intersects(other.box_);
			break;
		case CapsuleCol:
			return circle_.intersects(other.capsule_);
			break;
		case CircleCol:
			return circle_.intersects(other.circle_);
			break;
		case SegmentCol:
			return circle_.intersects(other.segment_);
			break;
		case NoneCol:
			break;
		default:
			break;
		}
		break;
	case SegmentCol:
		switch (other.type_)
		{
		case BoxCol:
			return segment_.intersects(other.box_);
			break;
		case CapsuleCol:
			return segment_.intersects(other.capsule_);
			break;
		case CircleCol:
			return segment_.intersects(other.circle_);
			break;
		case SegmentCol:
			return segment_.intersects(other.segment_);
			break;
		case NoneCol:
			break;
		default:
			break;
		}
		break;
	case NoneCol:
		break;
	default:
		break;
	}
	return false;
}

CollisionType CollisionBase::GetType() const
{
	return type_;
}

BoundingBox CollisionBase::GetBox() const
{
	return box_;
}

BoundingCapsule CollisionBase::GetCapsule() const
{
	return capsule_;
}

BoundingCircle CollisionBase::GetCircle() const
{
	return circle_;
}

BoundingSegment CollisionBase::GetSegment() const
{
	return segment_;
}

Vector2 CollisionBase::GetColliderVelocity()
{
	Vector2 getVect = position_ - previousPosition_;
	return getVect;
}

void CollisionBase::enabled(bool change)
{
	switch (type_)
	{
	case BoxCol:
		box_.enabled = change;
		break;
	case CapsuleCol:
		capsule_.enabled = change;
		break;
	case CircleCol:
		circle_.enabled = change;
		break;
	case SegmentCol:
		segment_.enabled = change;
		break;
	case NoneCol:
		break;
	default:
		break;
	}
}
