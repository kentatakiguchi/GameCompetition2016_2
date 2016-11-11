#pragma once
#include "../../Base/ActorUI.h"
#include <vector>
struct GaugeState
{
	int Hp=100; //���̃Q�[�W��HP
	Vector3 Color; //���̃Q�[�W�̐F
	int GaugeNum; //�Q�[�W�ԍ�
};

class BossGaugeUI : public ActorUI {
public:
	BossGaugeUI(IWorld* world, const Vector2& position);
	~BossGaugeUI();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;

public:
	void SetHp(int hp) {
		mResHp = hp;
	}
private:
	Vector2 mPosition;     //���W
	Vector2 textureSize;   //�e�N�X�`���T�C�Y
	float mHp;               //HP
	float mResHp;            //��ԗpHP
	float mGaugeHp;          //�`�ʗpHP
	float mGaugeNum;         //�������Q�[�W�̔ԍ�
	float mTexDivision;    //�e�N�X�`����HP�����������
	std::vector<GaugeState> gauges;  //�Q�[�W�x�N�^�[

	//��Ԋ֌W
	float velo;

};