#include "BoundingCapsule.h"
#include"BoundingBox.h"
#include "Model.h"

BoundingCapsule::BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius) :
	component_(startPoint, endPoint, capsuleRadius),enabled(true) {
}

BoundingCapsule::BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius, bool isEnabled):
	component_(startPoint, endPoint, capsuleRadius),enabled(isEnabled)
{
}

BoundingCapsule::BoundingCapsule(float radius) :
	BoundingCapsule({ 0.0f, 0.0f }, { 0.0f, 0.0f }, radius,false) {
}

BoundingCapsule BoundingCapsule::translate(const Vector2& position) const {
	return BoundingCapsule(component_.point[0] + position,
		component_.point[1] + position,component_.radius,enabled);
}

BoundingCapsule BoundingCapsule::transform(Vector2 startPoint, Vector2 endPoint, float capsuleRadius) const {
	return BoundingCapsule(startPoint, endPoint, capsuleRadius,enabled);
}

//bool BoundingSphere::intersects(const BoundingSphere& other) const {
//	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_
//	/*gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE*/;
//}

void BoundingCapsule::draw() const {
	DrawCircle(component_.point[0].x, component_.point[0].y, component_.radius, GetColor(255, 0, 0), FALSE);
	DrawLine(component_.point[0].x, component_.point[0].y, component_.point[1].x, component_.point[1].y, GetColor(255, 0, 0), FALSE);
	DrawLine(component_.point[0].x, component_.point[0].y, component_.point[1].x, component_.point[1].y, GetColor(255, 0, 0), FALSE);
	DrawCircle(component_.point[1].x, component_.point[1].y, component_.radius, GetColor(255, 0, 0), FALSE);

	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}



bool BoundingCapsule::intersects(BoundingBox & other)
{
	if (!other.enabled||!enabled)return false;

	int intSet[][2] = { { 0,1 },{ 0,2 },{ 1,3 },{ 2,3 } };

	for (int i = 0; i < 4; i++)
	{
		//DrawFormatString(200 * i, 100, GetColor(255, 255, 255), "kurikaesi");
		if (isIntersectThisRayToOtherLineBox(other, intSet[i][0], intSet[i][1]))
		{
			if (isIntersectOtherRayToThisLineBox(other, intSet[i][0], intSet[i][1]))
			{

				//交差している
				return true;
			}
			else
			{
				float a1 = component_.point[0].y - component_.point[1].y;
				float b1 = -(component_.point[0].x - component_.point[1].x);
				float c1 = component_.point[0].x*component_.point[1].y
					- component_.point[1].x*component_.point[0].y;

				float perpendicular1 =
					(abs(a1*other.component_.point[intSet[i][0]].x + b1*other.component_.point[intSet[i][0]].y + c1)) / sqrtf(a1*a1 + b1*b1);
				float perpendicular2 =
					(abs(a1*other.component_.point[intSet[i][1]].x + b1*other.component_.point[intSet[i][1]].y + c1)) / sqrtf(a1*a1 + b1*b1);
				float perpendicularMain = min(perpendicular1, perpendicular2);
				if (component_.radius >= perpendicularMain)
				{

					return true;
				}
			}
		}
		else if (isIntersectOtherRayToThisLineBox(other, intSet[i][0], intSet[i][1]))
		{

			float a1 = other.component_.point[intSet[i][0]].y - other.component_.point[intSet[i][1]].y;
			float b1 = -(other.component_.point[intSet[i][0]].x - other.component_.point[intSet[i][1]].x);
			float c1 = other.component_.point[intSet[i][0]].x*other.component_.point[intSet[i][1]].y
				- other.component_.point[intSet[i][1]].x*other.component_.point[intSet[i][0]].y;
			//自分が横、Otherが斜め(Otherが点)
			float perpendicular1 =
				(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicular2 =
				(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicularMain = min(perpendicular1, perpendicular2);
			if (component_.radius >= perpendicularMain)
			{
				return true;
			}
		}

		//else
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

			if (otherPoint1 == otherPoint2)
			{
				float xmin = min(component_.point[0].x, component_.point[1].x);
				float xmax = max(component_.point[0].x, component_.point[1].x);
				float ymin = min(component_.point[0].y, component_.point[1].y);
				float ymax = max(component_.point[0].y, component_.point[1].y);
				float oxmin = min(other.component_.point[intSet[i][0]].x, other.component_.point[intSet[i][1]].x);
				float oxmax = max(other.component_.point[intSet[i][0]].x, other.component_.point[intSet[i][1]].x);
				float oymin = min(other.component_.point[intSet[i][0]].y, other.component_.point[intSet[i][1]].y);
				float oymax = max(other.component_.point[intSet[i][0]].y, other.component_.point[intSet[i][1]].y);

				if (xmax == xmin || ymax == ymin)
				{
					if (xmax + component_.radius >= oxmin &&
						xmin - component_.radius <= oxmax &&
						ymax + component_.radius >= oymin &&
						ymin - component_.radius <= oymax)
					{

						float a1 = other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y;
						float b1 = -(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x);
						float c1 = other.component_.point[intSet[i][1]].y*(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x)
							- other.component_.point[intSet[i][1]].x*(other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y);
						//自分が斜め、Otherが横(自分が点)
						float perpendicular1 =
							(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicular2 =
							(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicularMain = min(perpendicular1, perpendicular2);
						if (component_.radius >= perpendicularMain)
						{
							return true;
						}


					}
				}
				if (xmax >= oxmin&& xmin <= oxmax)
				{
					if (ymax >= oymin&&ymin <= oymax)
					{
						float a1 = other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y;
						float b1 = -(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x);
						float c1 = other.component_.point[intSet[i][1]].y*(other.component_.point[intSet[i][1]].x - other.component_.point[intSet[i][0]].x)
							- other.component_.point[intSet[i][1]].x*(other.component_.point[intSet[i][1]].y - other.component_.point[intSet[i][0]].y);
						//自分が斜め、Otherが横(自分が点)
						float perpendicular1 =
							(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicular2 =
							(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicularMain = min(perpendicular1, perpendicular2);
						if (component_.radius >= perpendicularMain)
						{

							return true;
						}

					}
				}
			}
			//2線分が交わらない
			float perpendicular1 =
				sqrtf(
					(other.component_.point[intSet[i][0]].x - component_.point[0].x)*
					(other.component_.point[intSet[i][0]].x - component_.point[0].x) +
					(other.component_.point[intSet[i][0]].y - component_.point[0].y)*
					(other.component_.point[intSet[i][0]].y - component_.point[0].y)
					);
			float perpendicular2 =
				sqrtf(
					(other.component_.point[intSet[i][0]].x - component_.point[1].x)*
					(other.component_.point[intSet[i][0]].x - component_.point[1].x) +
					(other.component_.point[intSet[i][0]].y - component_.point[1].y)*
					(other.component_.point[intSet[i][0]].y - component_.point[1].y)
					);
			float perpendicular3 =
				sqrtf(
					(other.component_.point[intSet[i][1]].x - component_.point[0].x)*
					(other.component_.point[intSet[i][1]].x - component_.point[0].x) +
					(other.component_.point[intSet[i][1]].y - component_.point[0].y)*
					(other.component_.point[intSet[i][1]].y - component_.point[0].y)
					);
			float perpendicular4 =
				sqrtf(
					(other.component_.point[intSet[i][1]].x - component_.point[1].x)*
					(other.component_.point[intSet[i][1]].x - component_.point[1].x) +
					(other.component_.point[intSet[i][1]].y - component_.point[1].y)*
					(other.component_.point[intSet[i][1]].y - component_.point[1].y)
					);
			float perpendicularMin1 = min(perpendicular1, perpendicular2);
			float perpendicularMin2 = min(perpendicular3, perpendicular4);
			float perpendicularMain = min(perpendicularMin1, perpendicularMin2);
			if (component_.radius >= perpendicularMain)
			{

				return true;
			}
		}
	}
	return false;


}
bool BoundingCapsule::intersects(BoundingCapsule & other) {
	if (!enabled)return false;

	if (isIntersectOtherRayToThisLineCapsule(other))
	{
		if (isIntersectThisRayToOtherLineCapsule(other))
		{
			//交差している
			return true;
		}
		else
		{
			float a1 = other.component_.point[1].y-other.component_.point[0].y;
			float b1 = -(other.component_.point[1].x-other.component_.point[0].x);
			float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
					 - other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
			//自分が斜め、Otherが横(自分が点)
			float perpendicular1 =
				(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicular2 =
				(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicularMain = min(perpendicular1, perpendicular2);
			if (component_.radius + other.component_.radius >= perpendicularMain)
			{
				return true;
			}
		}
	}
	else if (isIntersectThisRayToOtherLineCapsule(other))
	{
		float a1 = component_.point[1].y - component_.point[0].y;
		float b1 = -(component_.point[1].x - component_.point[0].x);
		float c1 = component_.point[1].y*(component_.point[1].x - component_.point[0].x)
			- component_.point[1].x*(component_.point[1].y - component_.point[0].y);
		//自分が横、Otherが斜め(Otherが点)
		float perpendicular1 =
			(abs(a1*other.component_.point[0].x + b1*other.component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
		float perpendicular2 =
			(abs(a1*other.component_.point[1].x + b1*other.component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
		float perpendicularMain = min(perpendicular1, perpendicular2);
		if (component_.radius + other.component_.radius >= perpendicularMain)
		{
			return true;
		}
	}
	
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

		if (otherPoint1 == otherPoint2)
		{
			float xmin = min(component_.point[0].x, component_.point[1].x);
			float xmax = max(component_.point[0].x, component_.point[1].x);
			float ymin = min(component_.point[0].y, component_.point[1].y);
			float ymax = max(component_.point[0].y, component_.point[1].y);
			float oxmin = min(other.component_.point[0].x, other.component_.point[1].x);
			float oxmax = max(other.component_.point[0].x, other.component_.point[1].x);
			float oymin = min(other.component_.point[0].y, other.component_.point[1].y);
			float oymax = max(other.component_.point[0].y, other.component_.point[1].y);

			if (xmax == xmin || ymax == ymin)
			{
				if (xmax + component_.radius >= oxmin - other.component_.radius&&
					xmin-component_.radius<=oxmax+other.component_.radius&&
					ymax+component_.radius>=oymin-other.component_.radius&&
					ymin - component_.radius <= oymax + other.component_.radius)
				{
									
					float a1 = other.component_.point[1].y - other.component_.point[0].y;
					float b1 = -(other.component_.point[1].x - other.component_.point[0].x);
					float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
						- other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
					//自分が斜め、Otherが横(自分が点)
					float perpendicular1 =
						(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
					float perpendicular2 =
						(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
					float perpendicularMain = min(perpendicular1, perpendicular2);
					if (component_.radius + other.component_.radius >= perpendicularMain)
					{
						return true;
					}


				}
			}
			if (xmax >= oxmin&& xmin <= oxmax)
			{
				if (ymax >= oymin&&ymin <= oymax)
				{
					float a1 = other.component_.point[1].y - other.component_.point[0].y;
					float b1 = -(other.component_.point[1].x - other.component_.point[0].x);
					float c1 = other.component_.point[1].y*(other.component_.point[1].x - other.component_.point[0].x)
						- other.component_.point[1].x*(other.component_.point[1].y - other.component_.point[0].y);
					//自分が斜め、Otherが横(自分が点)
					float perpendicular1 =
						(abs(a1*component_.point[0].x + b1*component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
					float perpendicular2 =
						(abs(a1*component_.point[1].x + b1*component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
					float perpendicularMain = min(perpendicular1, perpendicular2);
					if (component_.radius + other.component_.radius >= perpendicularMain)
					{
						return true;
					}

				}
			}

			
		}

		//2線分が交わらない
		float perpendicular1 =
			sqrtf(
				(other.component_.point[0].x - component_.point[0].x)*
				(other.component_.point[0].x - component_.point[0].x)+
				(other.component_.point[0].y - component_.point[0].y)*
				(other.component_.point[0].y - component_.point[0].y)
				);
		float perpendicular2 =
			sqrtf(
				(other.component_.point[0].x - component_.point[1].x)*
				(other.component_.point[0].x - component_.point[1].x) +
				(other.component_.point[0].y - component_.point[1].y)*
				(other.component_.point[0].y - component_.point[1].y)
				);
		float perpendicular3 =
			sqrtf(
				(other.component_.point[1].x - component_.point[0].x)*
				(other.component_.point[1].x - component_.point[0].x) +
				(other.component_.point[1].y - component_.point[0].y)*
				(other.component_.point[1].y - component_.point[0].y)
				);
		float perpendicular4 =
			sqrtf(
				(other.component_.point[1].x - component_.point[1].x)*
				(other.component_.point[1].x - component_.point[1].x) +
				(other.component_.point[1].y - component_.point[1].y)*
				(other.component_.point[1].y - component_.point[1].y)
				);
		float perpendicularMin1 = min(perpendicular1, perpendicular2);
		float perpendicularMin2 = min(perpendicular3, perpendicular4);
		float perpendicularMain = min(perpendicularMin1, perpendicularMin2);
		if (component_.radius + other.component_.radius >= perpendicularMain)
		{
			return true;
		}
	}
	return false;
}



bool BoundingCapsule::isIntersectOtherRayToThisLineCapsule(BoundingCapsule & other)
{
	float otherPoint1 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[0].y - component_.point[0].y)
		+(component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[0].x);
	float otherPoint2 =
		(component_.point[0].x - component_.point[1].x)
		*(other.component_.point[1].y - component_.point[0].y)
		+(component_.point[0].y - component_.point[1].y)
		*(component_.point[0].x - other.component_.point[1].x);

	if (otherPoint1*otherPoint2 < 0)
	{

		return true;
	}
	return false;
}
bool BoundingCapsule::isIntersectThisRayToOtherLineCapsule(BoundingCapsule & other)
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
bool BoundingCapsule::isIntersectOtherRayToThisLineBox(BoundingBox & other,int point1,int point2)
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
bool BoundingCapsule::isIntersectThisRayToOtherLineBox(BoundingBox & other,int point1,int point2)
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


void BoundingCapsule::update(const Vector2 & center)
{
}

void BoundingCapsule::debug() const
{
}
