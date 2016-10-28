#include "CollisionBase.h"

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
void CollisionBase::RotateCapsule(Vector2 point1, Vector2 point2,float radius)
{
	if (type_ != CollisionType::CapsuleCol) return;

	movePoint[0] = point1;
	movePoint[1] = point2;
	radius_ = radius;
}
void CollisionBase::update(Vector2 position)
{
	MovePos(position);
}
void CollisionBase::draw() const
{
	switch (type_)
	{
	case BoxCol:
		box_.draw();
		break;
	case CapsuleCol:
		capsule_.draw();
		break;
	case CircleCol:
		circle_.draw();
		break;
	case SegmentCol:
		segment_.draw();
		break;
	case NoneCol:
		break;
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
