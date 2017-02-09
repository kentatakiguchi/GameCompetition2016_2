#include "BossGaugeUI.h"
#include "../../../ResourceLoader/ResourceLoader.h"
#include "../../../Input/InputMgr.h"
#include "../../../Game/Time.h"
#include "../../../Math/Math.h"
BossGaugeUI::BossGaugeUI(IWorld* world, const Vector2& position) :
	ActorUI(world, position),
	velo(0),
	mHp(250),
	mResHp(mHp),
	mGaugeHp(100){
	//�Q�[�W�����Z�b�g
	GaugeState state;
	state.Color = Vector3(255, 255, 255);
	state.Hp = 100.0f;
	state.GaugeNum = 0;
	gauges.push_back(state);
	state.Color = Vector3(255, 255, 0);
	state.Hp = 100.0f;
	state.GaugeNum = 1;
	gauges.push_back(state);
	state.Color = Vector3(0, 255, 0);
	state.Hp = 100.0f;
	state.GaugeNum = 2;
	gauges.push_back(state);
	state.Color = Vector3(0, 255, 255);
	state.Hp = 100.0f;
	state.GaugeNum = 3;
	gauges.push_back(state);

	//�g�p����Q�[�W������
	mGaugeNum = (int)((mHp + 1000.0f) / 100.0f) % 10;
	//�e�N�X�`���T�C�Y
	textureSize = ResourceLoader::GetInstance().GetTextureSize(TextureID::BOSS_GAUGE_IN_TEX);
	//����
	mTexDivision = textureSize.x / 100.0f;
}

BossGaugeUI::~BossGaugeUI()
{
}

void BossGaugeUI::onUpdate(float deltaTime)
{
	//�N�����v
	mResHp = MathHelper::Clamp(mResHp, 0.0f, 300.0f);
	//���
	MathHelper::Spring(mHp, mResHp, velo, 0.3f, 0.5f, 2.0f);
	mGaugeNum = ((int)(mHp + 1000) / 100) % 10;
	mGaugeHp = ((((int)(mHp + 100) / 10) % 10) * 10) +
		((int)mHp % 10);
	//�z��O�Q�Ɩh�~
	if (mGaugeNum < 3)
	{
		//��Ԃ̍ۂ����ꍇ������̂ł���h�~
		for (auto& i : gauges)
		{
			if (gauges[mGaugeNum + 1].GaugeNum == i.GaugeNum)
				i.Hp = mGaugeHp;
			else if (i.GaugeNum>gauges[mGaugeNum + 1].GaugeNum)
				i.Hp = 0;
			else
				i.Hp = 100;
		}
	}
}

void BossGaugeUI::onDraw() const
{
	//�Q�[�W�O
	DrawGraph(position_.x, position_.y, ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_GAUGE_OUT_TEX), TRUE);
	//�Q�[�W��
	for (auto i : gauges){
		SetDrawBright(i.Color.x, i.Color.y, i.Color.z);
		DrawRectGraphF(position_.x, position_.y, 0, 0, i.Hp*mTexDivision, textureSize.y,
		ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_GAUGE_IN_TEX), TRUE, FALSE);
		SetDrawBright(255, 255, 255);
	}
	//DrawFormatString(200, 550, GetColor(255, 255, 255), "Hp:%f",mHp);
}
