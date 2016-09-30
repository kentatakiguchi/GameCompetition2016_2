#pragma once

#include "../../Math/Math.h"
#include "Body.h"

class Model : public Body {
public:
	Model(const int modelHandle, const Vector3& center);

	explicit Model(const Vector3& center = Vector3::Zero);

	int handle();

	// Body ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual bool intersects(BoundingSphere & other) override;

	virtual bool intersects(Capsule & other) override;

	virtual void update(const Vector3 & center) override;

	virtual void debug() const override;

	void draw() const;
private:
	int modelHandle_;

	bool enabled;
};

