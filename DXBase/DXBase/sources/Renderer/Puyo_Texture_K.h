#pragma once
#include <vector>
#include <memory>
#include "../ResourceLoader/ResourceLoader.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix.h"
#include "../World/IWorld.h"
#include "../Actor/Base/Actor.h"

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
	float veloNum=0.0f;                                 //��ԗp�o�l
	float resNum=0.0f;                                  //��ԗp����
	float num = 0.0f;
	float power = 0.0f;                            //�������
	//float maxPower = 0.0f;
	float time=0.0f;						       //�o�ߎ���
	//float vibrationTime = 0.0f;                    //�U������܂ł̎���
	//float vibrationTimer = 0.0f;                   //�U������܂ł̃J�E���g
	Vector2 position=Vector2::Zero;		           //�U�����钆�S���W
	Vector2 velocity = Vector2(1, 1);              //�U�����Ă�������Ƒ傫��
	//bool PowerFlag = true;                         //�U�����Ă��ރt���O
	Vector2 springVelocity = Vector2::Zero;
	Vector2 springResPos = Vector2::Zero;
	Vector2 colWallVec = Vector2::Zero;           //�ǂɓ������Ă������
	float colWallPower = 0.0f;                  //�ǂɓ������Ă����
};


class PuyoTextureK {
public:
	//�h�炷�e�N�X�`��ID�ƍ��W�Ƒ傫���Ɖ�]
	PuyoTextureK(IWorld* world,TextureID tex,Vector2 pos,Vector2 scale,float rotate);
	~PuyoTextureK();
	//���W�ƃX�P�[���Ɖ�]���Z�b�g����
	void SetPosition(Vector2 pos, Vector2 scale, float rotate,Vector2 center);
	//�͂������钸�_(pos:�e�N�X�`�����猩���͂���������W,velo:�h�炷�����Ƒ傫��)
	void PuyoAddPower(Vector2 pos,Vector2 velo);
	//�͂����������钸�_�i����ɂɂ��j(pos:�e�N�X�`�����猩���͂���������W,velo:�h�炷�����Ƒ傫��)�����t���[���ĂԂ���
	void PuyoAddPowerDx(Vector2 pos, Vector2 velo);
	//�Љ��ɕ����Ă�������
	void PuyoAddPowerEx(Vector2 pos,Vector2 velo,float power,float eikyo);
	//�S�^�C�}�[���[���ɂ���(�Ղ�Ղ�OFF)
	void PuyoTimerZero();
	//��l���̃|�W�V�������Z�b�g����
	void PuyoPlayerPos(Vector2 pos1, Vector2 pos2, Vector3 color,bool isHold);
	void PuyoUpdate();
	void PuyoDraw();
private:
	void PuyoGraphSplit();
	void PuyoGraphVertex();
	void PuyoVertexSet();
	void PuyoVertexSetInit();
	//����͈Ⴄ
	void PuyoAddPowerDxSub(int x,int y,Vector2 velo,float power,float eikyo);

private:
	IWorld* mWorld;
	//�����蔻��t�����_���
	Actor commonVertexActor[30][30];
	//���_���
	VertexPos  spriteVertexH[30][30];
	//�C���f�b�N�X���
	int  spriteIndexsH[30][30];
	//���ʂ̒��_���
	SpringState commonVertexH[30][30];
	//���ʂ̒��_���i�ړ����Ȃ���j
	SpringState commonVertexHNoMove[32][32];
	//���ʂ̒��_���(�����蔻��Ȃ���)
	SpringState commonVertexHNoCol[32][32];
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
	//�Ԃ��Ă��Ƃ����Ă��̒��S
	Vector2 mCenter;
	//�Ղ��Ă��Ƃ����Ă��̍��W
	Vector2 mPlayerPos1;
	Vector2 mPlayerPos2;
	float time;
	//�J���[
	Vector3 mColor;
	Vector3 mResColor;
	Vector3 mColorVelo;

	std::vector<ActorPtr> puyoCols;
	float mAlpha;
	bool mIsHold;
	


};