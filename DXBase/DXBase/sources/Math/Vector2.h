#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "DxLib.h"

// 2D�x�N�g��
struct Vector2 {
	float	x;	// x����
	float	y;	// y����

	// �R���X�g���N�^
	Vector2(float x = 0.0f, float y = 0.0f);
	// �x�N�g���̒������v�Z���܂�
	float Length() const;
	// �x�N�g���̒����̕������v�Z���܂�
	float LengthSquared() const;
	// �P�ʃx�N�g�����쐬���܂�
	Vector2& Normalize();
	//	�l�̐��������̂ݕԂ��܂�
	Vector2& Horizontal();
	//	�l�̐��������̂ݕԂ��܂�
	Vector2& Vertical();

	// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
	static Vector2 Normalize(const Vector2& value);
	// 2�̃x�N�g���̓��ς��v�Z���܂�
	static float Dot(const Vector2& vector1, const Vector2& vector2);
	// 2�̃x�N�g���̊O�ς��v�Z���܂�
	static float Cross(const Vector2& vector1, const Vector2& vector2);
	// 2�̃x�N�g���Ԃ̋������v�Z���܂�
	static float Distance(const Vector2& vector1, const Vector2& vector2);
	// 2 �̒����x�N�g���Ԃ̋������v�Z���܂��B
	static float DistanceSquared(const Vector2 & vector1, const Vector2 & vector2);
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
	static Vector2 Min(const Vector2& vector1, const Vector2& vector2);
	// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
	static Vector2 Max(const Vector2& vector1, const Vector2& vector2);
	//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	//	�w�肳�ꂽ���W������̋����ȓ��ɐ������܂�
	static Vector2 ClampTarget(const Vector2& pos, const Vector2& target, float length);

	//�o�l�̕␳
	static void Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness = 0.2f, float friction = 0.5f, float mass = 2.0f);
	//�o�l�̕␳
	static Vector2 Spring_v(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness = 0.2f, float friction = 0.5f, float mass = 2.0f);
	//Dxlib�p�ϊ��֐�
	static VECTOR Vector2ToVECTOR(const Vector2& v);

	// �萔
	static const Vector2 Up;			// Vector2( 0,  1)
	static const Vector2 Down;			// Vector2( 0, -1)
	static const Vector2 Left;			// Vector2(-1,  0)
	static const Vector2 Right;			// Vector2( 1,  0)
	static const Vector2 UnitX;			// Vector2( 1,  0)
	static const Vector2 UnitY;			// Vector2( 0,  1)
	static const Vector2 One;			// Vector2( 1,  1)
	static const Vector2 Zero;			// Vector2( 0,  0)
};

// �P�����Z�q�I�[�o�[���[�h
Vector2 operator - (const Vector2& v);

// ������Z�q�I�[�o�[���[�h
Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2& operator *= (Vector2& v, float s);
Vector2& operator /= (Vector2& v, float s);

// �Q�����Z�q�I�[�o�[���[�h
Vector2 operator + (Vector2 v1, const Vector2& v2);
Vector2 operator - (Vector2 v1, const Vector2& v2);
Vector2 operator * (Vector2 v1, Vector2 v2);
Vector2 operator * (Vector2 v, float s);
Vector2 operator * (float s, Vector2 v);
Vector2 operator / (Vector2 v, float s);

#endif

// end of file
