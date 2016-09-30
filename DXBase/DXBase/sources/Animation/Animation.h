#pragma once

#include "DxLib.h"
#include <string>

class Animation {
public:
	struct AnimParams{
		int id_;
		float count_;
	};
	explicit Animation(const unsigned int &modelHandle_);
	void update(float deltaTime);
	void process();
	void changeAnim(int id);
	bool isAnimEnd();
private:
	unsigned int modelHandle_;
	AnimParams currAnim_;
	AnimParams prevAnim_;
	float animBlendRate_;
	int id_;
};