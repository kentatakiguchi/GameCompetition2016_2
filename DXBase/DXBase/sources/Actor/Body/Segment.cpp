#include "Segment.h"
#include "Ray.h"

// コンストラクタ
Segment::Segment(const Vector3 & start, const Vector3 & end) :
	start(start), end(end) {
}

// デフォルトコンストラクタ
Segment::Segment() /*:
	Ray({ 0.0f, 0.0f ,0.0f }, { 0.0f, 0.0f, 0.0f })*/ {
}
