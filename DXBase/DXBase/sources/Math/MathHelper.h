#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

// �}�X�w���p�[�N���X
class MathHelper {
public:
	// �΂̒l��\���܂��B
	static const float Pi;

	// �l���w�肳�ꂽ�͈͓��ɐ������܂�
	static float Clamp(float value, float min, float max);
	// 2�̒l�̍��̐�Βl���v�Z���܂�
	static float Distance(float n1, float n2);
	// 2�̒l�̊Ԃ���`��Ԃ��܂�
	static float Lerp(float value1, float value2, float amount);
	// ���W�A����x�ɕϊ����܂��B
	static float ToDegrees(float radians);
	// �x�����W�A���ɕϊ����܂��B
	static float ToRadians(float degree);

	static float Sin(float degree);

	static float Cos(float degree);

	static float Tan(float degree);

	static float ASin(float s);

	static float ACos(float c);

	static float ATan(float y, float x);
	// �ϐ��̕������󂯎��
	static int Sign(float value);
	//�o�l�␳
	static void Spring(float & num, float & resNum, float & velo, float stiffness, float friction, float mass);
	static void SpringInt(int & num, int & resNum, int & velo, float stiffness, float friction, float mass);
};

#endif
