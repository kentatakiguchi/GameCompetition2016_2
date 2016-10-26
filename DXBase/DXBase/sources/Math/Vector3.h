#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "DxLib.h"

struct Matrix;

// 3D�x�N�g��
struct Vector3 {
	float	x;	// x����
	float	y;	// y����
	float	z;	// z����

	// �R���X�g���N�^
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	// �x�N�g���̒������v�Z���܂�
	float Length() const;
	// �x�N�g���̒����̕������v�Z���܂�
	float LengthSquared() const;
	// �P�ʃx�N�g�����쐬���܂�
	Vector3& Normalize();

	// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
	static Vector3 Normalize(const Vector3& value);
	// 2�̃x�N�g���̓��ς��v�Z���܂�
	static float Dot(const Vector3& vector1, const Vector3& vector2);
	// 2�̃x�N�g���̊O�ς��v�Z���܂�
	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
	// 2�̃x�N�g���Ԃ̋������v�Z���܂�
	static float Distance(const Vector3& vector1, const Vector3& vector2);
	// 2 �̒����x�N�g���Ԃ̋������v�Z���܂��B 
	static float DistanceSquared(const Vector3& vector1, const Vector3& vector2);
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
	static Vector3 Min(const Vector3& vector1, const Vector3& vector2);
	// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
	static Vector3 Max(const Vector3& vector1, const Vector3& vector2);
	//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	// �w�肳�ꂽ Matrix �ɂ���āAVector3���g�����X�t�H�[�����܂�
	static Vector3 Transform(const Vector3& position, const Matrix& matrix);
	// �w�肳�ꂽ Matrix �ɂ���āA�@���x�N�g�����g�����X�t�H�[�����܂�
	static Vector3 TransformNormal(const Vector3& position, Matrix& matrix);
	//���[�E�s�b�`����x�N�g�����쐬
	static Vector3 CreateFromYawPitch(float yaw, float pitch);
	//�s�b�`���擾
	float Pitch() const;
	//���[���擾
	float Yaw() const;
	//�Q�̃x�N�g���Ԃ̉s�p��Ԃ��܂�
	static float Angle(const Vector3& from, const Vector3& to);
	//�o�l�̕␳
	static void Spring(Vector3& pos, Vector3& resPos, Vector3& velo, float stiffness, float friction, float mass);
	//Dxlib�p�ϊ��֐�
	static VECTOR Vector3ToVECTOR(const Vector3& v);
	
	// �萔
	static const Vector3 Up;			// Vector3( 0,  1,  0)
	static const Vector3 Down;			// Vector3( 0, -1,  0)
	static const Vector3 Left;			// Vector3(-1,  0,  0)
	static const Vector3 Right;			// Vector3( 1,  0,  0)
	static const Vector3 Backward;		// Vector3( 0,  0, -1)
	static const Vector3 Forward;		// Vector3( 0,  0,  1)
	static const Vector3 UnitX;			// Vector3( 1,  0,  0)
	static const Vector3 UnitY;			// Vector3( 0,  1,  0)
	static const Vector3 UnitZ;			// Vector3( 0,  1,  1)
	static const Vector3 One;			// Vector3( 1,  1,  1)
	static const Vector3 Zero;			// Vector3( 0,  0,  0)
};

// �P�����Z�q�I�[�o�[���[�h
Vector3 operator - (const Vector3& v);

// ������Z�q�I�[�o�[���[�h
Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, float s);
Vector3& operator /= (Vector3& v, float s);

// �Q�����Z�q�I�[�o�[���[�h
Vector3 operator + (Vector3 v1, const Vector3& v2);
Vector3 operator - (Vector3 v1, const Vector3& v2);
Vector3 operator * (Vector3 v, float s);
Vector3 operator * (float s, Vector3 v);
Vector3 operator / (Vector3 v, float s);

#endif

// end of file
