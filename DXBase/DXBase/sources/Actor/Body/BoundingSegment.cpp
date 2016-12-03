#include "BoundingSegment.h"
#include"BoundingCapsule.h"
#include"BoundingBox.h"
#include"BoundingCircle.h"

BoundingSegment::BoundingSegment(const Vector2& startPoint, const Vector2& endPoint) :
	component_(startPoint, endPoint), enabled(true) {

}
BoundingSegment::BoundingSegment(const Vector2& startPoint, const Vector2& endPoint, bool isEnabled) :
	component_(startPoint,endPoint), enabled(isEnabled) {

}
BoundingSegment::BoundingSegment() :
	component_({ 0.0f, 0.0f }, { 0.0f, 0.0f }), enabled(false) {

}

BoundingSegment BoundingSegment::translate(const Vector2& position) const {

	return BoundingSegment(component_.point[0] + position,
		component_.point[1] + position,
		enabled);
}

BoundingSegment BoundingSegment::transform(const Vector2& startPoint, const Vector2& endPoint) const {
	return BoundingSegment(startPoint,endPoint,enabled);
}

//bool BoundingSphere::intersects(const BoundingSphere& other) const {
//	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_
//	/*gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE*/;
//}

void BoundingSegment::draw() const {
	//if (!enabled)return;

	DrawLine(component_.point[0].x, component_.point[0].y, component_.point[1].x, component_.point[1].y, GetColor(255, 0, 0));

	//DrawBox(component_.point[0].x, component_.point[0].y,
	//	component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0), FALSE);
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}

void BoundingSegment::draw(Matrix inv) const {
	//if (!enabled)return;

	Vector3 pos0 = Vector3(component_.point[0].x, component_.point[0].y) * inv;
	Vector3 pos1 = Vector3(component_.point[1].x, component_.point[1].y) * inv;

	DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0));

	//DrawBox(component_.point[0].x, component_.point[0].y,
	//	component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0), FALSE);
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}
void BoundingSegment::draw(int spriteID, Matrix inv) const {
	//if (!enabled)return;

	Vector3 pos0 = Vector3(component_.point[0].x, component_.point[0].y) * inv;
	Vector3 pos1 = Vector3(component_.point[1].x, component_.point[1].y) * inv;

	DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, GetColor(255, 0, 0));

	DrawModiGraph(pos0.x, pos0.y, pos1.x, pos1.y, pos1.x, pos1.y, pos1.x, pos0.y,  spriteID, TRUE);
	//DrawBox(component_.point[0].x, component_.point[0].y,
	//	component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0), FALSE);
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}

bool BoundingSegment::intersects(BoundingBox & other)
{
	if (!enabled || !other.enabled)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };
	
	Vector2 AB = CreateVector(previousPosition_, position_);
	Vector2 AC, AD, CD, CA, CB;

	for (int i = 0; i < 4; i++)
	{
		//‚·‚è”²‚¯‚½‚©
		AC = CreateVector(previousPosition_, other.component_.point[intSet[i][0]]);
		AD = CreateVector(previousPosition_, other.component_.point[intSet[i][1]]);
		CD = CreateVector(other.component_.point[intSet[i][0]], other.component_.point[intSet[i][1]]);
		CA = CreateVector(other.component_.point[intSet[i][0]], previousPosition_);
		CB = CreateVector(other.component_.point[intSet[i][0]], position_);

		if (OuterProduct(AB, AC)*OuterProduct(AB, AD) <= 0.0f&&
			OuterProduct(CD, CA)*OuterProduct(CD, CB) < 0.0f)
		{
			DrawFormatString(400, 400, GetColor(255, 255, 255), "deta");
			return true;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		float otherPoint1 =
			(component_.point[0].x - component_.point[1].x)
			*(other.component_.point[intSet[i][0]].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - other.component_.point[intSet[i][0]].x);
		float otherPoint2 =
			(component_.point[0].x - component_.point[1].x)
			*(other.component_.point[intSet[i][1]].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - other.component_.point[intSet[i][1]].x);

		if (otherPoint1*otherPoint2 < 0)
		{
			float otherPoint1 =
				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
				*(component_.point[0].y - other.component_.point[intSet[i][0]].y)
				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
				*(other.component_.point[intSet[i][0]].x - component_.point[0].x);
			float otherPoint2 =
				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
				*(component_.point[1].y - other.component_.point[intSet[i][0]].y)
				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
				*(other.component_.point[intSet[i][0]].x - component_.point[1].x);

			if (otherPoint1*otherPoint2 < 0)
			{

				return true;
			}

		}
	}
	return false;


	//if (component_.point[1].x >= other.component_.point[0].x&&
	//	component_.point[0].x <= other.component_.point[1].x)
	//{
	//	if (component_.point[2].y >= other.component_.point[0].y&&
	//		component_.point[0].y <= other.component_.point[2].y)
	//	{
	//		return true;
	//	}
	//}
	//return false;
}
bool BoundingSegment::intersects(BoundingCapsule & other) {
	if (!enabled || !other.enabled)return false;

	Vector2 AB = CreateVector(previousPosition_, position_);
	Vector2 AC, AD, CD, CA, CB;

	for (int i = 0; i < 4; i++)
	{
		//‚·‚è”²‚¯‚½‚©
		AC = CreateVector(previousPosition_, other.component_.point[0]);
		AD = CreateVector(previousPosition_, other.component_.point[1]);
		CD = CreateVector(other.component_.point[0], other.component_.point[1]);
		CA = CreateVector(other.component_.point[0], previousPosition_);
		CB = CreateVector(other.component_.point[0], position_);

		if (OuterProduct(AB, AC)*OuterProduct(AB, AD) <= 0.0f&&
			OuterProduct(CD, CA)*OuterProduct(CD, CB) < 0.0f)
		{
			DrawFormatString(400, 400, GetColor(255, 255, 255), "deta");
			return true;
		}
	}


	//2‰~‚ÌŠe+-‚Éü‚ðˆø‚«A‚»‚Ìü‚Æ‚Ì“–‚½‚è”»’è
	float sin90, cos90;
	sin90 = 1;
	cos90 = 0;

	Vector2 A = CreateVector(other.component_.point[0], other.component_.point[1]);
	Vector2 AN = A.Normalize();
	Vector2 rotationA{ (AN.x*cos90) - (AN.y*sin90) , (AN.x*sin90) + (AN.y*cos90) };
	Vector2 A0P = other.component_.point[0] + rotationA * other.component_.radius;
	Vector2 A0M = other.component_.point[0] - rotationA * other.component_.radius;

	Vector2 A1P = other.component_.point[1] + rotationA * other.component_.radius;
	Vector2 A1M = other.component_.point[1] - rotationA * other.component_.radius;

	Vector2 pq, pm;
	float inner, k, pqd2, pmd2, phd2, d2;

	Vector2 As[][2]{ { A0P,A1P },{ A0M,A1M } };

		//gensuisindou
	//ü•ª‚Æ‚Ì“–‚½‚è”»’è
	for (int i = 0; i < 2; i++)
	{
		float otherPoint1 =
			(component_.point[0].x - component_.point[1].x)
			*(As[i][0].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - As[i][0].x);
		float otherPoint2 =
			(component_.point[0].x - component_.point[1].x)
			*(As[i][1].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - As[i][1].x);

		if (otherPoint1*otherPoint2 < 0)
		{
			float otherPoint1 =
				(As[i][0].x - As[i][1].x)
				*(component_.point[0].y - As[i][0].y)
				+ (As[i][0].y - As[i][1].y)
				*(As[i][0].x - component_.point[0].x);
			float otherPoint2 =
				(As[i][0].x - As[i][1].x)
				*(component_.point[1].y - As[i][0].y)
				+ (As[i][0].y - As[i][1].y)
				*(As[i][0].x - component_.point[1].x);

			if (otherPoint1*otherPoint2 < 0)
			{

				return true;
			}
		}
	}
	//‰~‚Æ‚Ì“–‚½‚è”»’è
	float dx, dy, r;

	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < 2; x++)
		{
			dx = component_.point[i].x - other.component_.point[x].x;
			dy = component_.point[i].y - other.component_.point[x].y;
			r = other.component_.radius;
			if ((dx*dx) + (dy*dy) < (r*r))
			{
				return true;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		pq = CreateVector(component_.point[0], component_.point[1]);
		pm = CreateVector(component_.point[0], other.component_.point[i]);

		inner = InnerProduct(pq, pm);
		pqd2 = pq.LengthSquared();
		pmd2 = pm.LengthSquared();

		k = inner / pqd2;

		if (k < 0 || 1 < k) continue ;

		phd2 = (inner*inner) / pqd2;
		d2 = pmd2 - phd2;

		if (d2 < other.component_.radius*other.component_.radius)return true;
	}
	return false;
}
bool BoundingSegment::intersects(BoundingSegment & other)
{
	if (!enabled || !other.enabled)return false;

	int intSet[][2] = { { 0,1 } };

	Vector2 AB = CreateVector(previousPosition_, position_);
	Vector2 AC, AD, CD, CA, CB;

	//‚·‚è”²‚¯‚½‚©
	AC = CreateVector(previousPosition_, other.component_.point[0]);
	AD = CreateVector(previousPosition_, other.component_.point[1]);
	CD = CreateVector(other.component_.point[0], other.component_.point[1]);
	CA = CreateVector(other.component_.point[0], previousPosition_);
	CB = CreateVector(other.component_.point[0], position_);

	if (OuterProduct(AB, AC)*OuterProduct(AB, AD) <= 0.0f&&
		OuterProduct(CD, CA)*OuterProduct(CD, CB) < 0.0f)
	{
		DrawFormatString(400, 400, GetColor(255, 255, 255), "deta");
		return true;
	}



	for (int i = 0; i < 1; i++)
	{
		float otherPoint1 =
			(component_.point[0].x - component_.point[1].x)
			*(other.component_.point[intSet[i][0]].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - other.component_.point[intSet[i][0]].x);
		float otherPoint2 =
			(component_.point[0].x - component_.point[1].x)
			*(other.component_.point[intSet[i][1]].y - component_.point[0].y)
			+ (component_.point[0].y - component_.point[1].y)
			*(component_.point[0].x - other.component_.point[intSet[i][1]].x);

		if (otherPoint1*otherPoint2 < 0)
		{
			float otherPoint1 =
				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
				*(component_.point[0].y - other.component_.point[intSet[i][0]].y)
				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
				*(other.component_.point[intSet[i][0]].x - component_.point[0].x);
			float otherPoint2 =
				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
				*(component_.point[1].y - other.component_.point[intSet[i][0]].y)
				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
				*(other.component_.point[intSet[i][0]].x - component_.point[1].x);

			if (otherPoint1*otherPoint2 < 0)
			{

				return true;
			}

		}
	}
	return false;
}
bool BoundingSegment::intersects(BoundingCircle & other) {
	if (!enabled || !other.enabled)return false;

	Vector2 AB = CreateVector(other.previousPosition_, other.position_);
	Vector2 AC, AD, CD, CA, CB;

	//‚·‚è”²‚¯‚½‚©
	AC = CreateVector(other.previousPosition_, component_.point[0]);
	AD = CreateVector(other.previousPosition_, component_.point[1]);
	CD = CreateVector(component_.point[0], component_.point[1]);
	CA = CreateVector(component_.point[0], other.previousPosition_);
	CB = CreateVector(component_.point[0], other.position_);

	if (OuterProduct(AB, AC)*OuterProduct(AB, AD) <= 0.0f&&
		OuterProduct(CD, CA)*OuterProduct(CD, CB) < 0.0f)
	{
		DrawFormatString(400, 400, GetColor(255, 255, 255), "deta");
		return true;
	}



	float dx, dy, r;

	for (int i = 0; i < 2; i++)
	{
		dx = component_.point[i].x - other.component_.point[0].x;
		dy = component_.point[i].y - other.component_.point[0].y;
		r = other.component_.radius;
		if ((dx*dx) + (dy*dy) < (r*r))
		{
			return true;
		}
	}


	Vector2 pq, pm;
	float inner, k, pqd2, pmd2, phd2, d2;

	pq = CreateVector(component_.point[0], component_.point[1]);
	pm = CreateVector(component_.point[0], other.component_.point[0]);

	//inner = Vector2::Dot(pq, pm);
	inner = InnerProduct(pq, pm);
	pqd2 = pq.LengthSquared();
	pmd2 = pm.LengthSquared();

	k = inner / pqd2;

	if (k < 0 || 1 < k) return false;

	phd2 = (inner*inner) / pqd2;
	d2 = pmd2 - phd2;

	if (d2 < other.component_.radius*other.component_.radius)return true;

	return false;

}

//bool BoundingBox::isIntersectOtherRayToThisLine(BoundingBox & other, int point1, int point2)
//{
//	float otherPoint1 =
//		(component_.point[0].x - component_.point[1].x)
//		*(other.component_.point[point1].y - component_.point[0].y)
//		+ (component_.point[0].y - component_.point[1].y)
//		*(component_.point[0].x - other.component_.point[point1].x);
//	float otherPoint2 =
//		(component_.point[0].x - component_.point[1].x)
//		*(other.component_.point[point2].y - component_.point[0].y)
//		+ (component_.point[0].y - component_.point[1].y)
//		*(component_.point[0].x - other.component_.point[point2].x);
//
//	if (otherPoint1*otherPoint2 < 0)
//	{
//		return true;
//	}
//	return false;
//}
bool BoundingSegment::isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2)
{
	float otherPoint1 =
		(component_.point[point1].x - component_.point[point2].x)
		*(other.component_.point[0].y - component_.point[point1].y)
		+ (component_.point[point1].y - component_.point[point2].y)
		*(component_.point[point1].x - other.component_.point[0].x);
	float otherPoint2 =
		(component_.point[point1].x - component_.point[point2].x)
		*(other.component_.point[1].y - component_.point[point1].y)
		+ (component_.point[point1].y - component_.point[point2].y)
		*(component_.point[point1].x - other.component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}

bool BoundingSegment::isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2)
{
	float otherPoint1 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[point1].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[point1].x);
	float otherPoint2 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[point2].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[point2].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}

void BoundingSegment::update(const Vector2 & center)
{
}

void BoundingSegment::debug() const
{
}
