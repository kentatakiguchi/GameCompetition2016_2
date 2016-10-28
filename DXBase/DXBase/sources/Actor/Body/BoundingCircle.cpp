#include "BoundingCapsule.h"
#include"BoundingBox.h"
#include"BoundingSegment.h"
#include"BoundingCircle.h"
#include "Model.h"

BoundingCircle::BoundingCircle(Vector2 center, float circleRadius) :
	component_(center, circleRadius), enabled(true) {
}

BoundingCircle::BoundingCircle(Vector2 center, float circleRadius, bool isEnabled) :
	component_(center, circleRadius), enabled(isEnabled)
{
}

BoundingCircle::BoundingCircle(float radius) :
	BoundingCircle({ 0.0f, 0.0f }, radius, false) {
}

BoundingCircle BoundingCircle::translate(const Vector2& position) const {
	return BoundingCircle(component_.point[0] + position, component_.radius, enabled);
}

BoundingCircle BoundingCircle::transform(Vector2 center, float capsuleRadius) const {
	return BoundingCircle(center, capsuleRadius, enabled);
}

//bool BoundingSphere::intersects(const BoundingSphere& other) const {
//	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_
//	/*gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE*/;
//}

void BoundingCircle::draw() const {
	DrawCircle(component_.point[0].x, component_.point[0].y, component_.radius, GetColor(255, 0, 0), FALSE);

	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}



bool BoundingCircle::intersects(BoundingBox & other)
{
	if (!other.enabled || !enabled)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };
	//端点
	float dx, dy, r;
	//線分
	Vector2 pq, pm;
	float inner, k, pqd2, pmd2 , phd2, d2;
	//内側
	Vector2 pp,inpm;
	float ininner, outer, theta[2];

	//for (int i = 0; i < 4; i++)
	//{
	//	float otherPoint1 =
	//		(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
	//		*(previousPosition_.y - other.component_.point[intSet[i][0]].y)
	//		+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
	//		*(other.component_.point[intSet[i][0]].x - previousPosition_.x);
	//	float otherPoint2 =
	//		(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
	//		*(position_.y - other.component_.point[intSet[i][0]].y)
	//		+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
	//		*(other.component_.point[intSet[i][0]].x - position_.x);
	//	if (otherPoint1*otherPoint2 < 0)
	//	{
	//		float otherPoint1 =
	//			(previousPosition_.x - position_.x)
	//			*(other.component_.point[intSet[i][0]].y - previousPosition_.y)
	//			+ (previousPosition_.y - position_.y)
	//			*(previousPosition_.x - other.component_.point[intSet[i][0]].x);
	//		float otherPoint2 =
	//			(previousPosition_.x - position_.x)
	//			*(other.component_.point[intSet[i][1]].y - previousPosition_.y)
	//			+ (previousPosition_.y - position_.y)
	//			*(previousPosition_.x - other.component_.point[intSet[i][1]].x);

	//		if (otherPoint1*otherPoint2 <= 0)
	//		{
	//			OutputDebugString("sdasd");

	//			return true;
	//		}
	//	}

	//}

	Vector2 AB = CreateVector(previousPosition_, position_);
	Vector2 AC,AD,CD,CA,CB;
	for (int i = 0; i < 4; i++)
	{
		AC = CreateVector(previousPosition_, other.component_.point[intSet[i][0]]);
		AD = CreateVector(previousPosition_, other.component_.point[intSet[i][1]]);
		CD = CreateVector(other.component_.point[intSet[i][0]], other.component_.point[intSet[i][1]]);
		CA = CreateVector(other.component_.point[intSet[i][0]], previousPosition_);
		CB = CreateVector(other.component_.point[intSet[i][0]], position_);

		if (Vector2::Cross(AB, AC)*Vector2::Cross(AB, AD) <= 0.0f&&
			Vector2::Cross(CD, CA)*Vector2::Cross(CD, CB) <= 0.0f) 
		{
			DrawFormatString(400, 400, GetColor(255, 255, 255), "deta");
			OutputDebugString("stds");
			OutputDebugString("\n");
			return true;
		}
	}

	//端点と触れているかどうか
	for (int i = 0; i < 4; i++)
	{
		dx = other.component_.point[i].x - component_.point[0].x;
		dy = other.component_.point[i].y - component_.point[0].y;
		r = component_.radius;
		if ((dx*dx) + (dy*dy) < (r*r))
		{
			return true;
		}
	}

	//線分に触れているかどうか
	for (int i = 0; i < 4; i++)
	{
		pq = CreateVector(other.component_.point[intSet[i][0]], other.component_.point[intSet[i][1]]);
		pm = CreateVector(other.component_.point[intSet[i][0]], component_.point[0]);
		
		//inner = Vector2::Dot(pq, pm);
		inner = InnerProduct(pq,pm);
		pqd2 = pq.LengthSquared();
		pmd2 = pm.LengthSquared();
		
		k = inner / pqd2;
		
		if (k < 0 || 1 < k)continue;
		
		phd2 = (inner*inner) / pqd2;
		d2 = pmd2 - phd2;

		if (d2 < component_.radius*component_.radius)return true;
	}
	//四角の内側かどうか
	{
		for (int i = 0; i < 2; i++)
		{
			pp = CreateVector(other.component_.point[i * 3], other.component_.point[1 + i]);
			inpm = CreateVector(other.component_.point[i * 3], component_.point[0]);

			ininner = InnerProduct(pp, inpm);
			outer = OuterProduct(pp, inpm);

			theta[i] = (atan2(outer, ininner)*(180 / MathHelper::Pi));
		}
		if (0 <= theta[0] && theta[0] <= 90 &&
			0 <= theta[1] && theta[1] <= 90)
		{
			return true;
		}
	}
	return false;
}
//p->qベクトルを返す

bool BoundingCircle::intersects(BoundingCircle& other)
{
	float dx, dy, r;
	dx = other.component_.point[0].x - component_.point[0].x;
	dy = other.component_.point[0].y - component_.point[0].y;
	r = other.component_.radius + component_.radius;
	return ((dx*dx) + (dy*dy) < (r*r));
}
bool BoundingCircle::intersects(BoundingCapsule & other) {
	if (!enabled || !other.enabled)return false;

	
	//2円の各+-に線を引き、その線との当たり判定
	float sin90, cos90;
	sin90 = 1;
	cos90 = 0;
	
	Vector2 A = CreateVector(other.component_.point[0], other.component_.point[1]);
	Vector2 AN = A.Normalize();
	Vector2 rotationA{ (AN.x*cos90) - (AN.y*sin90) , (AN.x*sin90) + (AN.y*cos90)};
	Vector2 A0P = other.component_.point[0] + rotationA * other.component_.radius;
	Vector2 A0M = other.component_.point[0] - rotationA * other.component_.radius;

	Vector2 A1P = other.component_.point[1] + rotationA * other.component_.radius;
	Vector2 A1M = other.component_.point[1] - rotationA * other.component_.radius;

	Vector2 pq, pm;
	float inner, k, pqd2, pmd2, phd2, d2;
	
	Vector2 As[][2]{ {A0P,A1P }, { A0M,A1M }};

	for (int i = 0; i < 2; i++)
	{
		pq = CreateVector(As[i][0], As[i][1]);
		pm = CreateVector(As[i][0], component_.point[0]);

		//inner = Vector2::Dot(pq, pm);
		inner = InnerProduct(pq, pm);
		pqd2 = pq.LengthSquared();
		pmd2 = pm.LengthSquared();

		k = inner / pqd2;

		if (k < 0 || 1 < k)continue;

		phd2 = (inner*inner) / pqd2;
		d2 = pmd2 - phd2;

		if (d2 < component_.radius*component_.radius)return true;
	}

	//円同士の判定
	float dx, dy, r;
	for (int i = 0; i < 2; i++)
	{
		dx = other.component_.point[i].x - component_.point[0].x;
		dy = other.component_.point[i].y - component_.point[0].y;
		r = other.component_.radius + component_.radius;
		if ((dx*dx) + (dy*dy) < (r*r)) {
			return true;
		};
	}

	return false;
	//DrawCircle(A0P.x, A0P.y,3, GetColor(255, 255, 255));
	//DrawCircle(A0M.x, A0M.y,3, GetColor(255, 255, 255));
	//DrawCircle(A1P.x, A1P.y,3, GetColor(255, 255, 255));
	//DrawCircle(A1M.x, A1M.y,3, GetColor(255, 255, 255));
}
//bool BoundingCircle::intersects(BoundingCapsule & other) {
//	if (!enabled)return false;
//	float xmin = min(component_.point[0].x, component_.point[1].x);
//	float xmax = max(component_.point[0].x, component_.point[1].x);
//	float ymin = min(component_.point[0].y, component_.point[1].y);
//	float ymax = max(component_.point[0].y, component_.point[1].y);
//	float oxmin = min(other.component_.point[0].x, other.component_.point[1].x);
//	float oxmax = max(other.component_.point[0].x, other.component_.point[1].x);
//	float oymin = min(other.component_.point[0].y, other.component_.point[1].y);
//	float oymax = max(other.component_.point[0].y, other.component_.point[1].y);
//
//	if (isIntersectOtherRayToThisLineCapsule(other))
//	{
//		if (isIntersectThisRayToOtherLineCapsule(other))
//		{
//			//交差している
//			return true;
//		}
//		else
//		{
//			float a1 = other.component_.point[1].y - other.component_.point[0].y;
//			float b1 = -(other.component_.point[1].x - other.component_.point[0].x);
//			float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
//				- other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
//			//自分が斜め、Otherが横(自分が点)
//			float perpendicular1 =
//				(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//			float perpendicular2 =
//				(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//			float perpendicularMain = min(perpendicular1, perpendicular2);
//			if (component_.radius + other.component_.radius >= perpendicularMain)
//			{
//				return true;
//			}
//		}
//	}
//	else if (isIntersectThisRayToOtherLineCapsule(other))
//	{
//		{
//			float a1 = component_.point[1].y - component_.point[0].y;
//			float b1 = -(component_.point[1].x - component_.point[0].x);
//			float c1 = component_.point[1].y*(component_.point[1].x - component_.point[0].x)
//				- component_.point[1].x*(component_.point[1].y - component_.point[0].y);
//			//自分が横、Otherが斜め(Otherが点)
//			float perpendicular1 =
//				(abs(a1*other.component_.point[0].x + b1*other.component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//			float perpendicular2 =
//				(abs(a1*other.component_.point[1].x + b1*other.component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//			float perpendicularMain = min(perpendicular1, perpendicular2);
//			if (component_.radius + other.component_.radius >= perpendicularMain)
//			{
//				return true;
//			}
//		}
//	}
//
//	{
//		float otherPoint1 =
//			(other.component_.point[0].x - other.component_.point[1].x)
//			*(component_.point[0].y - other.component_.point[0].y)
//			+ (other.component_.point[0].y - other.component_.point[1].y)
//			*(other.component_.point[0].x - component_.point[0].x);
//		float otherPoint2 =
//			(other.component_.point[0].x - other.component_.point[1].x)
//			*(component_.point[1].y - other.component_.point[0].y)
//			+ (other.component_.point[0].y - other.component_.point[1].y)
//			*(other.component_.point[0].x - component_.point[1].x);
//
//		if (otherPoint1 == otherPoint2)
//		{
//
//			if (xmax == xmin || ymax == ymin)
//			{
//				if (xmax + component_.radius >= oxmin - other.component_.radius&&
//					xmin - component_.radius <= oxmax + other.component_.radius&&
//					ymax + component_.radius >= oymin - other.component_.radius&&
//					ymin - component_.radius <= oymax + other.component_.radius)
//				{
//
//					float a1 = other.component_.point[1].y - other.component_.point[0].y;
//					float b1 = -(other.component_.point[1].x - other.component_.point[0].x);
//					float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
//						- other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
//					//自分が斜め、Otherが横(自分が点)
//					float perpendicular1 =
//						(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//					float perpendicular2 =
//						(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//					float perpendicularMain = min(perpendicular1, perpendicular2);
//					if (component_.radius + other.component_.radius >= perpendicularMain)
//					{
//						return true;
//					}
//
//
//				}
//			}
//			if (xmax >= oxmin&& xmin <= oxmax)
//			{
//				if (ymax >= oymin&&ymin <= oymax)
//				{
//					float a1 = other.component_.point[1].y - other.component_.point[0].y;
//					float b1 = -(other.component_.point[1].x - other.component_.point[0].x);
//					float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
//						- other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
//					//自分が斜め、Otherが横(自分が点)
//					float perpendicular1 =
//						(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//					float perpendicular2 =
//						(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//					float perpendicularMain = min(perpendicular1, perpendicular2);
//					if (component_.radius + other.component_.radius >= perpendicularMain)
//					{
//						return true;
//					}
//
//				}
//			}
//
//
//		}
//
//		//2線分が交わらない
//		float perpendicular1 =
//			sqrtf(
//				(other.component_.point[0].x - component_.point[0].x)*
//				(other.component_.point[0].x - component_.point[0].x) +
//				(other.component_.point[0].y - component_.point[0].y)*
//				(other.component_.point[0].y - component_.point[0].y)
//				);
//		float perpendicular2 =
//			sqrtf(
//				(other.component_.point[0].x - component_.point[1].x)*
//				(other.component_.point[0].x - component_.point[1].x) +
//				(other.component_.point[0].y - component_.point[1].y)*
//				(other.component_.point[0].y - component_.point[1].y)
//				);
//		float perpendicular3 =
//			sqrtf(
//				(other.component_.point[1].x - component_.point[0].x)*
//				(other.component_.point[1].x - component_.point[0].x) +
//				(other.component_.point[1].y - component_.point[0].y)*
//				(other.component_.point[1].y - component_.point[0].y)
//				);
//		float perpendicular4 =
//			sqrtf(
//				(other.component_.point[1].x - component_.point[1].x)*
//				(other.component_.point[1].x - component_.point[1].x) +
//				(other.component_.point[1].y - component_.point[1].y)*
//				(other.component_.point[1].y - component_.point[1].y)
//				);
//		float perpendicularMin1 = min(perpendicular1, perpendicular2);
//		float perpendicularMin2 = min(perpendicular3, perpendicular4);
//		float perpendicularMain = min(perpendicularMin1, perpendicularMin2);
//		if (component_.radius + other.component_.radius >= perpendicularMain)
//		{
//			return true;
//		}
//	}
//	return false;
//}

bool BoundingCircle::intersects(BoundingSegment & other) {
	if (!enabled || !other.enabled)return false;

	float dx, dy, r;

	for (int i = 0; i < 2; i++)
	{
		dx = other.component_.point[i].x - component_.point[0].x;
		dy = other.component_.point[i].y - component_.point[0].y;
		r = component_.radius;
		if ((dx*dx) + (dy*dy) < (r*r))
		{
			return true;
		}
	}

	Vector2 pq, pm;
	float inner, k, pqd2, pmd2, phd2, d2;

		pq = CreateVector(other.component_.point[0], other.component_.point[1]);
		pm = CreateVector(other.component_.point[0], component_.point[0]);

		//inner = Vector2::Dot(pq, pm);
		inner = InnerProduct(pq, pm);
		pqd2 = pq.LengthSquared();
		pmd2 = pm.LengthSquared();

		k = inner / pqd2;

		if (k < 0 || 1 < k) return false;

		phd2 = (inner*inner) / pqd2;
		d2 = pmd2 - phd2;

		if (d2 < component_.radius*component_.radius)return true;

		return false;
}
//bool BoundingCircle::intersects(BoundingSegment & other) {
//
//	if (!enabled || !other.enabled)return false;
//
//
//	int intSet[][2] = { { 0,1 } };
//
//	int i = 0;
//	{
//		float xmin = min(component_.point[0].x, component_.point[1].x);
//		float xmax = max(component_.point[0].x, component_.point[1].x);
//		float ymin = min(component_.point[0].y, component_.point[1].y);
//		float ymax = max(component_.point[0].y, component_.point[1].y);
//		float oxmin = min(other.component_.point[intSet[i][0]].x, other.component_.point[intSet[i][1]].x);
//		float oxmax = max(other.component_.point[intSet[i][0]].x, other.component_.point[intSet[i][1]].x);
//		float oymin = min(other.component_.point[intSet[i][0]].y, other.component_.point[intSet[i][1]].y);
//		float oymax = max(other.component_.point[intSet[i][0]].y, other.component_.point[intSet[i][1]].y);
//
//		if (isIntersectOtherRayToThisLineSegment(other))
//		{
//			if (isIntersectThisRayToOtherLineSegment(other))
//			{
//				//DrawFormatString(375, 50*i, GetColor(255, 255, 255), "当たった");
//				//交差している
//				return true;
//			}
//			else if (xmax + component_.radius >= oxmin &&
//				xmin - component_.radius <= oxmax &&
//				ymax + component_.radius >= oymin &&
//				ymin - component_.radius <= oymax)
//			{
//				float a1 = component_.point[0].y - component_.point[1].y;
//				float b1 = -(component_.point[0].x - component_.point[1].x);
//				float c1 = (component_.point[0].x*component_.point[1].y)
//					- (component_.point[1].x*component_.point[0].y);
//				//自分が斜め、Otherが横(自分が点)
//				float perpendicular1 =
//					(abs(a1*other.component_.point[intSet[i][0]].x + b1*other.component_.point[intSet[i][0]].y + c1)) / sqrtf(a1*a1 + b1*b1);
//				float perpendicular2 =
//					(abs(a1*other.component_.point[intSet[i][1]].x + b1*other.component_.point[intSet[i][1]].y + c1)) / sqrtf(a1*a1 + b1*b1);
//				float perpendicularMain = min(perpendicular1, perpendicular2);
//				if (component_.radius >= perpendicularMain)
//				{
//
//					return true;
//				}
//			}
//		}
//
//
//		//else if (isIntersectOtherRayToThisLineBox(other, intSet[i][0], intSet[i][1]))
//		//{
//
//		//	float a1 = other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y;
//		//	float b1 = -(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x);
//		//	float c1 = other.component_.point[intSet[i][0]].x*other.component_.point[intSet[i][1]].y
//		//		- other.component_.point[intSet[i][1]].x*other.component_.point[intSet[i][0]].y;
//		//	//自分が横、Otherが斜め(Otherが点)
//		//	float perpendicular1 =
//		//		(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//		//	float perpendicular2 =
//		//		(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//		//	float perpendicularMain = min(perpendicular1, perpendicular2);
//		//	if (component_.radius >= perpendicularMain)
//		//	{
//		//		return true;
//		//	}
//		//}
//
//
//		{
//			float otherPoint1 =
//				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
//				*(component_.point[0].y - other.component_.point[intSet[i][0]].y)
//				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
//				*(other.component_.point[intSet[i][0]].x - component_.point[0].x);
//			float otherPoint2 =
//				(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x)
//				*(component_.point[1].y - other.component_.point[intSet[i][0]].y)
//				+ (other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y)
//				*(other.component_.point[intSet[i][0]].x - component_.point[1].x);
//			if (otherPoint1 == otherPoint2)
//			{
//				if (xmax >= oxmin&& xmin <= oxmax)
//				{
//					if (ymax >= oymin&&ymin <= oymax)
//					{
//						float a1 = other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y;
//						float b1 = -(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x);
//						float c1 = other.component_.point[intSet[i][1]].y*(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x)
//							- other.component_.point[intSet[i][1]].x*(other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y);
//						//自分が斜め、Otherが横(自分が点)
//						float perpendicular1 =
//							(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
//						float perpendicular2 =
//							(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
//						float perpendicularMain = min(perpendicular1, perpendicular2);
//						if (component_.radius >= perpendicularMain)
//						{
//							return true;
//						}
//					}
//				}
//			}
//			//2線分が交わらない
//			float perpendicular1 =
//				sqrtf(
//					(component_.point[0].x - other.component_.point[intSet[i][0]].x)*
//					(component_.point[0].x - other.component_.point[intSet[i][0]].x) +
//					(component_.point[0].y - other.component_.point[intSet[i][0]].y)*
//					(component_.point[0].y - other.component_.point[intSet[i][0]].y)
//					);
//			float perpendicular2 =
//				sqrtf(
//					(component_.point[0].x - other.component_.point[intSet[i][1]].x)*
//					(component_.point[0].x - other.component_.point[intSet[i][1]].x) +
//					(component_.point[0].y - other.component_.point[intSet[i][1]].y)*
//					(component_.point[0].y - other.component_.point[intSet[i][1]].y)
//					);
//			float perpendicular3 =
//				sqrtf(
//					(component_.point[1].x - other.component_.point[intSet[i][0]].x)*
//					(component_.point[1].x - other.component_.point[intSet[i][0]].x) +
//					(component_.point[1].y - other.component_.point[intSet[i][0]].y)*
//					(component_.point[1].y - other.component_.point[intSet[i][0]].y)
//					);
//			float perpendicular4 =
//				sqrtf(
//					(component_.point[1].x - other.component_.point[intSet[i][1]].x)*
//					(component_.point[1].x - other.component_.point[intSet[i][1]].x) +
//					(component_.point[1].y - other.component_.point[intSet[i][1]].y)*
//					(component_.point[1].y - other.component_.point[intSet[i][1]].y)
//					);
//			float perpendicularMin1 = min(perpendicular1, perpendicular2);
//			float perpendicularMin2 = min(perpendicular3, perpendicular4);
//			float perpendicularMain = min(perpendicularMin1, perpendicularMin2);
//			if (component_.radius >= perpendicularMain)
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//
//}


bool BoundingCircle::isIntersectOtherRayToThisLineSegment(BoundingSegment & other)
{
	float otherPoint1 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[0].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[0].x);
	float otherPoint2 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[1].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}
bool BoundingCircle::isIntersectThisRayToOtherLineSegment(BoundingSegment & other)
{
	float otherPoint1 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[0].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[0].x);
	float otherPoint2 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[1].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{
		return true;
	}
	return false;
}
bool BoundingCircle::isIntersectOtherRayToThisLineCapsule(BoundingCapsule & other)
{
	float otherPoint1 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[0].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[0].x);
	float otherPoint2 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[1].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}
bool BoundingCircle::isIntersectThisRayToOtherLineCapsule(BoundingCapsule & other)
{
	float otherPoint1 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[0].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[0].x);
	float otherPoint2 =
		(other.component_.point[0].x - other.component_.point[1].x)
		*(component_.point[1].y - other.component_.point[0].y)
		+ (other.component_.point[0].y - other.component_.point[1].y)
		*(other.component_.point[0].x - component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{
		return true;
	}
	return false;
}
bool BoundingCircle::isIntersectOtherRayToThisLineBox(BoundingBox & other, int point1, int point2)
{
	float otherPoint1 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[point1].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[point1].x);
	float otherPoint2 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[point2].y - component_.point[0].y)
		+ (component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[point2].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}
bool BoundingCircle::isIntersectThisRayToOtherLineBox(BoundingBox & other, int point1, int point2)
{
	float otherPoint1 =
		(other.component_.point[point1].x - other.component_.point[point2].x)
		*(component_.point[0].y - other.component_.point[point1].y)
		+ (other.component_.point[point1].y - other.component_.point[point2].y)
		*(other.component_.point[point1].x - component_.point[0].x);
	float otherPoint2 =
		(other.component_.point[point1].x - other.component_.point[point2].x)
		*(component_.point[1].y - other.component_.point[point1].y)
		+ (other.component_.point[point1].y - other.component_.point[point2].y)
		*(other.component_.point[point1].x - component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{
		//DrawFormatString(375, 200, GetColor(255, 255, 255), "当たった");

		return true;
	}
	return false;
}


void BoundingCircle::update(const Vector2 & center)
{
}

void BoundingCircle::debug() const
{
}
