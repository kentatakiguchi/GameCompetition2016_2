#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	le(0.0f)
{
	//������Ȃ�����ꉞ
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	//�v���C���[�ϊ�
	mPlayer = dynamic_cast<TestPlayer*>(world->findActor("Player").get());
}

BackGraundManager::~BackGraundManager()
{
	//������Ȃ�����ꉞ
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
}

void BackGraundManager::SetBackGraund(TextureID id)
{
	BackGraundState backState;
	//id��ǉ�
	backState.id = ResourceLoader::GetInstance().getTextureID(id);
	//�T�C�Y��ǉ�
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = backState.size;
	//�|�W�V�����������(2���w�i�𒣂�t���邽��)
	backState.positions.push_back(Vector2::Zero);
	backState.positions.push_back(Vector2(size.x, 0.0f));
	//�����
	backStates.push_back(backState);
}

void BackGraundManager::SetUpBackGraund(TextureID id)
{
	//id��ǉ�
	upBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//�T�C�Y��ǉ�
	upBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;
	//�|�W�V������4�����(4���w�i�𒣂�t���邽��)
	upBackStates.positions.push_back(Vector2(0, 0));
	upBackStates.positions.push_back(Vector2(0, -size.y));
	upBackStates.positions.push_back(Vector2(size.x, -size.y));
	upBackStates.positions.push_back(Vector2(size.x, 0));

}

void BackGraundManager::SetDownBackGraund(TextureID id)
{

}

void BackGraundManager::AllDeleteBackGraund()
{
	//list�������ׂč폜
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	upBackStates.positions.clear();
}

void BackGraundManager::Update(float deltatime)
{

	//�v�f���������Ȃ�������v���C���[��null�������烊�^�[��
	if (backStates.empty() || mPlayer == nullptr) return;
	//�w�i�K�w�̐����擾
	float layerNum = backStates.size();
	//�R�s�[���g��Ȃ����߂Ɂ���t���ĎQ�Ƃ���(for����i�̒��g��M��ꍇ�Ɏg��)
	Vector2 vec = mPlayer->GetVelo();
	le = vec.Length();
	//�n�ʌn
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//���ɍs���قǒx������
			Vector2 vec = mPlayer->GetVelo()*(1.0f / layerNum);
			float len = vec.Length();
			//�v���C���[�x�N�g�����Z
			j += vec;
			//�n�ʃe�N�X�`���T�C�Y
			Vector2 size = i.size;
			if (j.x <= -size.x)
				j.x = size.x;
			else if (j.x >= size.x)
				j.x = -size.x;
		}
		layerNum--;
	}
	//��̃e�N�X�`���T�C�Y
	Vector2 sizeUp = upBackStates.size;
	//��n
	for (auto& i : upBackStates.positions)
	{
		//��ԉ��̑��x�ƈꏏ�ɂ���
		Vector2 vec = mPlayer->GetVelo()*(1.0f / backStates.size());
		//�v���C���[���x���Z
		i += vec;
		if (i.x <= -sizeUp.x)
			i.x = sizeUp.x;
		else if (i.x >= sizeUp.x)
			i.x = -sizeUp.x;

		if (i.y <= -sizeUp.y)
			i.y = sizeUp.y;
		else if (i.y >= sizeUp.y)
			i.y = -sizeUp.y;
	}

}

void BackGraundManager::Draw() const
{
	for (auto i : upBackStates.positions)
	{
		DrawGraph(i.x, i.y, upBackStates.id, true);
	}
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawGraph(j.x, j.y, i.id, true);
		}
	}
	int count = 0;
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawFormatString(550, 25 + 32*count, GetColor(255, 255, 255), "Position:%f,%f", j.x,j.y);
			count++;
		}
	}
	Vector2 a = mPlayer->GetVelo();
	//DrawFormatString(550, 25 + 32, GetColor(255, 255, 255), "vec:%f,%f", a.x, a.y);
	//DrawFormatString(550, 25, GetColor(255, 255, 255), "lenght:%f", le);

}
