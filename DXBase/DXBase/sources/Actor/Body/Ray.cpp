#include "Ray.h"

Ray::Ray(const Vector3 & position, const Vector3 & direction) :
	position(position), direction(direction){

}

Ray::Ray() : 
	Ray({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }){

}
