#include "Segment.h"
#include "Ray.h"

// �R���X�g���N�^
Segment::Segment(const Vector3 & start, const Vector3 & end) :
	start(start), end(end) {
}

// �f�t�H���g�R���X�g���N�^
Segment::Segment() /*:
	Ray({ 0.0f, 0.0f ,0.0f }, { 0.0f, 0.0f, 0.0f })*/ {
}
