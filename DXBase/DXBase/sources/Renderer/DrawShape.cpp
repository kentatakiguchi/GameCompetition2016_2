#include "DrawShape.h"

#include "../Math/Math.h"

#include <algorithm>

void DrawShape::Oval(const Vector2 & main_pos, const Vector2 & sub_pos, const int & height, const float& max)
{
	Vector2 vec = (main_pos - sub_pos).Normalize();
	Vector2 sign = Vector2(MathHelper::Sign(vec.x), MathHelper::Sign(vec.y));
	vec *= sign.x;
	float angle = Vector3::Angle(Vector3::Right * sign.x, Vector3(vec.x, vec.y, 0)) * sign.y;

	Vector2 center = (main_pos + sub_pos) / 2;

	float dis = Vector2::Distance(main_pos, sub_pos);

	float a = 0;
	if (dis > max) a = dis;
	else a = max;

	float b = height;

	for (int i = 0; i < dis * 4; i++) {
		float x = i - dis * 2;
		float y = std::sqrt(b * b * (1 - ((x * x) / (a * a))));

		Vector3 pos_p = Vector3(x, y) * Matrix::CreateFromAxisAngle(Vector3::Forward, angle) + Vector3(center.x, center.y);
		Vector3 pos_n = Vector3(x, -y) * Matrix::CreateFromAxisAngle(Vector3::Forward, angle) + Vector3(center.x, center.y);

		DrawPixel(pos_p.x, pos_p.y, GetColor(0, 255, 0));
		DrawPixel(pos_n.x, pos_n.y, GetColor(0, 255, 0));
	}
}
