#include "BoundigShphere.h"
#include "Model.h"

BoundingSphere::BoundingSphere(const Vector3& center, float radius) :
	component_(center, radius) {
}

BoundingSphere::BoundingSphere(float radius) :
  BoundingSphere({ 0.0f, 0.0f, 0.0f }, radius) {
}

BoundingSphere BoundingSphere::translate(const Vector3& position) const {
	return BoundingSphere(component_.center_ + position, component_.radius_);
}

BoundingSphere BoundingSphere::transform(const Matrix& matrix) const {
	return BoundingSphere(Vector3::Transform(component_.center_, matrix), component_.radius_ * matrix.Scale().y);
}

//bool BoundingSphere::intersects(const BoundingSphere& other) const {
//	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_
//	/*gsCollisionSphereAndSphere(&center, radius, &other.center, other.radius) == GS_TRUE*/;
//}

void BoundingSphere::draw() const {
	//DrawSphere3D(Vector3::Vector3ToVECTOR(component_.center_), component_.radius_, 32, GetColor( 255,0,0 ), GetColor( 255, 255, 255 ), TRUE ) ;
}



bool BoundingSphere::intersects(BoundingSphere & other)
{
	return (component_.center_ - other.component_.center_).Length() <= component_.radius_ + other.component_.radius_;
}

bool BoundingSphere::intersects(Capsule & other){
	return false;
}

bool BoundingSphere::intersects(Model & other){
	MV1_COLL_RESULT_POLY_DIM dim;
	dim = MV1CollCheck_Sphere(other.handle() , -1, Vector3::Vector3ToVECTOR(component_.center_), component_.radius_);
	// “–‚½‚Á‚½‚©‚Ç‚¤‚©‚Åˆ—‚ð•ªŠò
	if (dim.HitNum < 1) return false;
	
	// “–‚½‚Á‚½ê‡‚ÍÕ“Ë‚Ìî•ñ‚ð•`‰æ‚·‚é

	// “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚Ì”‚ð•`‰æ
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Hit Poly Num   %d", dim.HitNum);

	// “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚Ì”‚¾‚¯ŒJ‚è•Ô‚µ
	for (int i = 0; i < dim.HitNum; i++)
	{
		// “–‚½‚Á‚½ƒ|ƒŠƒSƒ“‚ð•`‰æ
		DrawTriangle3D(
			dim.Dim[i].Position[0],
			dim.Dim[i].Position[1],
			dim.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
	}
	
	return true;
}

void BoundingSphere::update(const Vector3 & center)
{
}

void BoundingSphere::debug() const
{
}
