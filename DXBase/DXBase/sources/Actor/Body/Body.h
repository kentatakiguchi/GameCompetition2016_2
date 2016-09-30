#pragma once

#include <string>
#include "../../Math/Math.h"
#include "ShapeType.h"

class BoundingSphere;
class Capsule;
class Model;

struct BodyData {
	std::string name;
	Vector3 position;
	ShapeType type;
};

class Body
{
public:
	virtual ~Body() {}
	virtual bool intersects(BoundingSphere& other) = 0;
	virtual bool intersects(Capsule& other) = 0;
	virtual bool intersects(Model& other) = 0;
	virtual void update(const Vector3& center) = 0;
	virtual void debug() const = 0;
};

