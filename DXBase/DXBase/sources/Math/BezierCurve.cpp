#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
}

void BezierCurve::set(const Vector2 & start, const Vector2 & end, const std::vector<Vector2>& control, const float & time) {
	start_point_ = start;
	end_point_ = end;
	control_points_ = control;
}

void BezierCurve::draw(const int & point_num) const {
	for (int i = 0; i <= point_num; i++) {
		float t = 1.0f / point_num * i;
		Vector2 pos = get(start_point_, end_point_, control_points_, t);
		DrawPixel(pos.x, pos.y, GetColor(0, 255, 0));
	}
	DrawCircle(start_point_.x, start_point_.y, 5.0f, GetColor(255, 0, 0), TRUE);
	for (int i = 0; i < control_points_.size(); i++) {
		DrawCircle(control_points_[i].x, control_points_[i].y, 5.0f, GetColor(255, 0, 0), TRUE);
	}
	DrawCircle(end_point_.x, end_point_.y, 5.0f, GetColor(255, 0, 0), TRUE);
} 

Vector2 BezierCurve::get(const Vector2 & start, const Vector2 & end, const std::vector<Vector2>& control, const float & time) const {
	float t = MathHelper::Clamp(time, 0, 1);
	std::vector<Vector2> points = all_points(start, end, control);
	return calc_point(points, t);
}

std::vector<Vector2> BezierCurve::all_points(const Vector2 & start, const Vector2 & end, const std::vector<Vector2>& control) const {
	std::vector<Vector2> points = std::vector<Vector2>();
	points.push_back(start);
	for (int i = 0; i < control.size(); i++) points.push_back(control[i]);
	points.push_back(end);
	return points;
}

Vector2 BezierCurve::calc_point(const std::vector<Vector2>& points, const float & t) const{
	Vector2 pos = Vector2::Zero;
	for (int i = 0; i < points.size(); i++) {
		pos += nPasTgl[points.size() - 1][i] * std::pow(1 - t, points.size() - 1 - i) * std::pow(t, i) * points[i];
	}
	return pos;
}