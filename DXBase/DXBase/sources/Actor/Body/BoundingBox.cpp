#include "BoundingBox.h"
#include "Model.h"
#include"BoundingCapsule.h"
BoundingBox::BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight):
	component_(topLeft,topRight,bottomLeft,bottomRight),enabled(true) {

}
BoundingBox::BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight,bool isEnabled) :
	component_(topLeft, topRight, bottomLeft, bottomRight), enabled(isEnabled) {

}
BoundingBox::BoundingBox() :
	component_({ 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }),enabled(false) {
	
}

BoundingBox BoundingBox::translate(const Vector2& position) const {

	return BoundingBox( component_.point[0] + position,
						component_.point[1] + position,
						component_.point[2] + position,
						component_.point[3] + position,
						enabled);
}

BoundingBox BoundingBox::transform(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight) const {
	return BoundingBox(topLeft, topRight, bottomLeft, bottomRight,enabled);
}

//bool BoundingSphere::intersects(const BoundingSphere& other) const {
//	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_
//	/*gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE*/;
//}

void BoundingBox::draw() const {
	//if (!enabled)return;

	DrawLine(component_.point[0].x, component_.point[0].y, component_.point[1].x, component_.point[1].y, GetColor(255, 0, 0));
	DrawLine(component_.point[1].x, component_.point[1].y, component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0));
	DrawLine(component_.point[0].x, component_.point[0].y, component_.point[2].x, component_.point[2].y, GetColor(255, 0, 0));
	DrawLine(component_.point[2].x, component_.point[2].y, component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0));

	//DrawBox(component_.point[0].x, component_.point[0].y,
	//	component_.point[3].x, component_.point[3].y, GetColor(255, 0, 0), FALSE);
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}



bool BoundingBox::intersects(BoundingBox & other)
{
	if (!enabled)return false;

	if (component_.point[1].x >= other.component_.point[0].x&&
		component_.point[0].x <= other.component_.point[1].x)
	{
		if (component_.point[2].y >= other.component_.point[0].y&&
			component_.point[0].y <= other.component_.point[2].y)
		{
			return true;
		}
	}
	return false;
}

bool BoundingBox::intersects(BoundingCapsule & other) {
	if (!enabled||!other.enabled)return false;


	int intSet[][2] = { {0,1},{0,2},{1,3},{2,3} };

	for (int i = 0; i < 4; i++)
	{
		if (isIntersectOtherRayToThisLine(other, intSet[i][0], intSet[i][1]))
		{
			if (isIntersectThisRayToOtherLine(other, intSet[i][0], intSet[i][1]))
			{
				
				//DrawFormatString(375, 50*i, GetColor(255, 255, 255), "当たった");

				//交差している
				return true;
			}
			else
			{

				float a1 = other.component_.point[0].y - other.component_.point[1].y;
				float b1 = -(other.component_.point[0].x - other.component_.point[1].x);
				float c1 = (other.component_.point[0].x*other.component_.point[1].y)
					- (other.component_.point[1].x*other.component_.point[0].y);
				//自分が斜め、Otherが横(自分が点)
				float perpendicular1 =
					(abs(a1*component_.point[intSet[i][0]].x + b1*component_.point[intSet[i][0]].y + c1)) / sqrtf(a1*a1 + b1*b1);
				float perpendicular2 =
					(abs(a1*component_.point[intSet[i][1]].x + b1*component_.point[intSet[i][1]].y + c1)) / sqrtf(a1*a1 + b1*b1);
				float perpendicularMain = min(perpendicular1, perpendicular2);
				if (other.component_.radius >= perpendicularMain)
				{
					return true;
				}
			}
		}
		
		else if (isIntersectThisRayToOtherLine(other, intSet[i][0], intSet[i][1]))
		//else if()
		{
			//DrawFormatString(200 * i, 100, GetColor(255, 255, 255), "kurikaesi");

			float a1 = component_.point[intSet[i][0]].y - component_.point[intSet[i][1]].y;
			float b1 = -(component_.point[intSet[i][0]].x - component_.point[intSet[i][1]].x);
			float c1 = (component_.point[intSet[i][0]].x*component_.point[intSet[i][1]].y)
				- (component_.point[intSet[i][1]].x*component_.point[intSet[i][0]].y);
			//自分が横、Otherが斜め(Otherが点)
			float perpendicular1 =
				(abs(a1*other.component_.point[0].x + b1*other.component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicular2 =
				(abs(a1*other.component_.point[1].x + b1*other.component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
			float perpendicularMain = min(perpendicular1, perpendicular2);
			if (other.component_.radius >= perpendicularMain)
			{
				return true;
			}
		}

		//else
		{
			float otherPoint1 =
				(component_.point[intSet[i][0]].x - component_.point[intSet[i][1]].x)
				*(other.component_.point[0].y - component_.point[intSet[i][0]].y)
				+ (component_.point[intSet[i][0]].y - component_.point[intSet[i][1]].y)
				*(component_.point[intSet[i][0]].x - other.component_.point[0].x);
			float otherPoint2 =
				(component_.point[intSet[i][0]].x - component_.point[intSet[i][1]].x)
				*(other.component_.point[1].y - component_.point[intSet[i][0]].y)
				+ (component_.point[intSet[i][0]].y - component_.point[intSet[i][1]].y)
				*(component_.point[intSet[i][0]].x - other.component_.point[1].x);

			if (otherPoint1 == otherPoint2)
			{
				float xmin = min(other.component_.point[0].x, other.component_.point[1].x);
				float xmax = max(other.component_.point[0].x, other.component_.point[1].x);
				float ymin = min(other.component_.point[0].y, other.component_.point[1].y);
				float ymax = max(other.component_.point[0].y, other.component_.point[1].y);
				float oxmin = min(component_.point[intSet[i][0]].x, component_.point[intSet[i][1]].x);
				float oxmax = max(component_.point[intSet[i][0]].x, component_.point[intSet[i][1]].x);
				float oymin = min(component_.point[intSet[i][0]].y, component_.point[intSet[i][1]].y);
				float oymax = max(component_.point[intSet[i][0]].y, component_.point[intSet[i][1]].y);

				if (xmax == xmin || ymax == ymin)
				{
					if (xmax + other.component_.radius >= oxmin &&
						xmin - other.component_.radius <= oxmax &&
						ymax + other.component_.radius >= oymin &&
						ymin - other.component_.radius <= oymax)
					{

						float a1 = component_.point[intSet[i][1]].y - component_.point[intSet[i][0]].y;
						float b1 = -(component_.point[intSet[i][1]].x - component_.point[intSet[i][0]].x);
						float c1 = component_.point[intSet[i][1]].y*(component_.point[intSet[i][1]].x - component_.point[intSet[i][0]].x)
							- component_.point[intSet[i][1]].x*(component_.point[intSet[i][1]].y - component_.point[intSet[i][0]].y);
						//自分が斜め、Otherが横(自分が点)
						float perpendicular1 =
							(abs(a1*other.component_.point[0].x + b1*other.component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicular2 =
							(abs(a1*other.component_.point[1].x + b1*other.component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicularMain = min(perpendicular1, perpendicular2);
						if (other.component_.radius >= perpendicularMain)
						{
							return true;
						}


					}
				}
				if (xmax >= oxmin&& xmin <= oxmax)
				{
					if (ymax >= oymin&&ymin <= oymax)
					{
						float a1 = component_.point[intSet[i][1]].y - component_.point[intSet[i][0]].y;
						float b1 = -(component_.point[intSet[i][1]].x - component_.point[intSet[i][0]].x);
						float c1 = component_.point[intSet[i][1]].y*(component_.point[intSet[i][1]].x - component_.point[intSet[i][0]].x)
							- component_.point[intSet[i][1]].x*(component_.point[intSet[i][1]].y - component_.point[intSet[i][0]].y);
						//自分が斜め、Otherが横(自分が点)
						float perpendicular1 =
							(abs(a1*other.component_.point[0].x + b1*other.component_.point[0].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicular2 =
							(abs(a1*other.component_.point[1].x + b1*other.component_.point[1].y + c1)) / sqrtf(a1*a1 + b1*b1);
						float perpendicularMain = min(perpendicular1, perpendicular2);
						if (other.component_.radius >= perpendicularMain)
						{
							return true;
						}

					}
				}
			}

			//2線分が交わらない
			float perpendicular1 =
				sqrtf(
					(other.component_.point[0].x - component_.point[intSet[i][0]].x)*
					(other.component_.point[0].x - component_.point[intSet[i][0]].x) +
					(other.component_.point[0].y - component_.point[intSet[i][0]].y)*
					(other.component_.point[0].y - component_.point[intSet[i][0]].y)
					);
			float perpendicular2 =
				sqrtf(
					(other.component_.point[0].x - component_.point[intSet[i][1]].x)*
					(other.component_.point[0].x - component_.point[intSet[i][1]].x) +
					(other.component_.point[0].y - component_.point[intSet[i][1]].y)*
					(other.component_.point[0].y - component_.point[intSet[i][1]].y)
					);
			float perpendicular3 =
				sqrtf(
					(other.component_.point[1].x - component_.point[intSet[i][0]].x)*
					(other.component_.point[1].x - component_.point[intSet[i][0]].x) +
					(other.component_.point[1].y - component_.point[intSet[i][0]].y)*
					(other.component_.point[1].y - component_.point[intSet[i][0]].y)
					);
			float perpendicular4 =
				sqrtf(
					(other.component_.point[1].x - component_.point[intSet[i][1]].x)*
					(other.component_.point[1].x - component_.point[intSet[i][1]].x) +
					(other.component_.point[1].y - component_.point[intSet[i][1]].y)*
					(other.component_.point[1].y - component_.point[intSet[i][1]].y)
					);
			float perpendicularMin1 = min(perpendicular1, perpendicular2);
			float perpendicularMin2 = min(perpendicular3, perpendicular4);
			float perpendicularMain = min(perpendicularMin1, perpendicularMin2);
			if (other.component_.radius >= perpendicularMain)
			{
				return true;
			}
		}
	}
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
bool BoundingBox::isIntersectOtherRayToThisLine(BoundingCapsule & other,int point1,int point2)
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

bool BoundingBox::isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2)
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

void BoundingBox::update(const Vector2 & center)
{
}

void BoundingBox::debug() const
{
}
