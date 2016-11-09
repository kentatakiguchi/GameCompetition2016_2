#pragma once
#include <vector>
#include "../ResourceLoader/ResourceLoader.h"
#include "../Math/Vector2.h"
#include "../Math/Matrix.h"
const Vector2 texSize = ResourceLoader::GetInstance().GetTextureSize(TextureID::PUYO_TEST_TEX);
const int SplitSize = 8.0f;
struct VertexPos {
	//����
	Vector2 LeftTopPos=Vector2::Zero;
	//����
	Vector2 LeftDownPos = Vector2::Zero;
	//�E��
	Vector2 RightTopPos = Vector2::Zero;
	//�E��
	Vector2 RightDownPos = Vector2::Zero;
};
struct SpringState {
	float amplitude = 0.0f;				           //�U��
	float time=0.0f;						       //�o�ߎ���
	float vibrationTime = 0.0f;                    //�U������܂ł̎���
	float vibrationTimer = 0.0f;                   //�U������܂ł̃J�E���g
	Vector2 position=Vector2::Zero;		           //�U�����钆�S���W
	Vector2 velocity = Vector2(1, 1);              //�U�����Ă�������Ƒ傫��

};


class PuyoTextureK {
public:
	PuyoTextureK(TextureID tex,Vector2 pos,Vector2 scale,float rotate);
	~PuyoTextureK();
	//�����Z�b�g
	void SetPosition(Vector2 pos, Vector2 scale, float rotate);
	//�͂������钸�_(x��y��2�����z��ɓ����Ă��钸�_�̍��W,velocity�͗h�炷�����Ƒ傫��)
	void PuyoAddPower(int x, int y,Vector2 velocity);
	void PuyoUpdate();
	void PuyoDraw();
private:
	void PuyoGraphSplit();
	void PuyoGraphVertex();
	void PuyoVertexSet();
private:
	//���_���
	VertexPos  spriteVertexH[16][16];
	//�C���f�b�N�X���
	int  spriteIndexsH[16][16];
	//���ʂ̒��_���
	SpringState commonVertexH[17][17];
	//���̃e�N�X�`�����
	int textureIndex;
	//���̃e�N�X�`���T�C�Y
	Vector2 textureSize;
	//���[�v�֌W
	int loopX;
	int loopY;
	//�摜�̍��W
	Vector2 mPosition;
	//�摜�̃X�P�[��
	Vector2 mScale;
	//�摜�̉�]
	float mRotate;


	//test
	Vector2 test;
	float time;
	//�o�l�֌W
	Vector2 vib_center_;	//�U�����S
	float angular_freq_;				//�p�U����
	Vector2 phase_;						//�ʑ�
	float spring_constant_;				//�΂˒萔
	float attenuation_constant_;		//�����萔
	float mass_;						//����
	float p_;						//����
	float e_;						//����

};