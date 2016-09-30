#include "Capsule.h"

Capsule::Capsule(const Segment & segment, float radius):
	segment_(segment), radius_(radius){

}

Capsule::Capsule():
	radius_(0.5f){

}

void Capsule::draw() const{
	DrawCapsule3D(Vector3::Vector3ToVECTOR(segment_.start), Vector3::Vector3ToVECTOR(segment_.end), radius_, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}
