#include "Vector2.h"
#include "MathHelper.h"
#include <cmath>
#include <algorithm>

// �萔
const Vector2 Vector2::Up(0.0f, 1.0f);
const Vector2 Vector2::Down(0.0f, -1.0f);
const Vector2 Vector2::Left(-1.0f, 0.0f);
const Vector2 Vector2::Right(1.0f, 0.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

float Vector2::Length() const
{
	return std::sqrt(Dot(*this, *this));
}

float Vector2::LengthSquared() const
{
	return Dot(*this, *this);
}

Vector2& Vector2::Normalize()
{
	const float len = Length();
	if (len != 0.0f) {
		*this /= len;
	}
	return *this;
}

Vector2 & Vector2::Horizontal(){
	this->y *= 0;
	return *this;
}

Vector2 & Vector2::Vertical() {
	this->x *= 0;
	return *this;
}

Vector2 Vector2::Normalize(const Vector2 & value)
{
	return Vector2(value).Normalize();
}

float Vector2::Dot(const Vector2 & vector1, const Vector2 & vector2)
{
	return (vector1.x * vector1.x) + (vector2.y * vector2.y);
}

float Vector2::Cross(const Vector2 & vector1, const Vector2 & vector2)
{
	return  (vector1.x * vector2.y) - (vector1.y * vector2.x);
}

float Vector2::Distance(const Vector2 & vector1, const Vector2 & vector2)
{
	return (vector2 - vector1).Length();
}

float Vector2::DistanceSquared(const Vector2 & vector1, const Vector2 & vector2)
{
	return (vector2 - vector1).LengthSquared();
}

Vector2 Vector2::Lerp(const Vector2 & value1, const Vector2 & value2, float amount)
{
	return Vector2(MathHelper::Lerp(value1.x, value2.x, amount), MathHelper::Lerp(value1.y, value2.y, amount));
}

Vector2 Vector2::Min(const Vector2 & vector1, const Vector2 & vector2)
{
	return Vector2(std::min<float>(vector1.x, vector1.x), std::min<float>(vector1.y, vector2.y));
}

Vector2 Vector2::Max(const Vector2 & vector1, const Vector2 & vector2)
{
	return Vector2(std::max<float>(vector1.x , vector2.x), std::min<float>(vector1.y, vector2.y));
}

Vector2 Vector2::Clamp(const Vector2 & value1, const Vector2& min, const Vector2 & max)
{
	return Vector2(MathHelper::Clamp(value1.x, min.x, max.x), MathHelper::Clamp(value1.y, min.y, max.y));
}

Vector2 Vector2::ClampTarget(const Vector2& pos, const Vector2& target, float length){
	Vector2 vec = pos - target;
	if (vec.Length() > length) return target + vec.Normalize() * length;
	return pos;
}

void Vector2::Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness, float friction, float mass){
	// �o�l�̐L�ы���v�Z
	Vector2 stretch = (pos - resPos);
	// �o�l�̗͂��v�Z
	Vector2 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector2 acceleration = force / mass;
	// �ړ����x���v�Z
	velo = friction * (velo + acceleration);
	// ���W�̍X�V
	pos += velo;
}

Vector2 Vector2::Spring_v(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness, float friction, float mass){
	// �o�l�̐L�ы���v�Z
	Vector2 stretch = (pos - resPos);
	// �o�l�̗͂��v�Z
	Vector2 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector2 acceleration = force / mass;
	// �ړ����x���v�Z
	return friction * (velo + acceleration);
}

VECTOR Vector2::Vector2ToVECTOR(const Vector2 & v)
{
	return VGet(v.x, v.y, 0);
}

Vector2 operator-(const Vector2 & v)
{
	return Vector2(-v.x, -v.y);
}

Vector2 & operator+=(Vector2 & v1, const Vector2 & v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 & operator-=(Vector2 & v1, const Vector2 & v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2 & operator*=(Vector2 & v, float s)
{
	v.x *= s;
	v.y *= s;
	return v;
}

Vector2 & operator/=(Vector2 & v, float s)
{
	v.x /= s;
	v.y /= s;
	return v;
}

Vector2 operator+(Vector2 v1, const Vector2 & v2)
{
	return v1 += v2;
}

Vector2 operator-(Vector2 v1, const Vector2 & v2){
	return v1 -= v2;
}

Vector2 operator*(Vector2 v1, Vector2 v2){
	return Vector2(v1.x * v2.x, v1.y * v2.y);
}

Vector2 operator*(Vector2 v, float s){
	return v *= s;
}

Vector2 operator*(float s, Vector2 v){
	return v *= s;
}

Vector2 operator/(Vector2 v, float s){
	return v /= s;
}
