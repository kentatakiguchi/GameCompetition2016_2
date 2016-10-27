#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
BackGraundManager::BackGraundManager(IWorld * world):
	stageFlag(true)
{
	//������Ȃ�����ꉞ
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	//�v���C���[�ϊ�
	mPlayer = dynamic_cast<Player*>(world->findActor("Player").get());
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
	//id��ǉ�
	downBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//�T�C�Y��ǉ�
	downBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;
	//�|�W�V������4�����(4���w�i�𒣂�t���邽��)
	downBackStates.positions.push_back(Vector2(0, size.y));
	downBackStates.positions.push_back(Vector2(0, size.y*2));
	downBackStates.positions.push_back(Vector2(size.x, size.y));
	downBackStates.positions.push_back(Vector2(size.x, size.y*2));
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
	//�ړ����邩�ǂ����t���O
	Vector2 moveFlag = mPlayer->GetMoveFlag();
	//�n�ʌn
	//�R�s�[���g��Ȃ����߂Ɂ���t���ĎQ�Ƃ���(for����i�̒��g��M��ꍇ�Ɏg��)
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//���ɍs���قǒx������
			Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / layerNum);
			//�ړ�����ꍇflag�ɂ�1���A�ړ����Ȃ��ꍇflag�ɂ�0��
			vec = Vector2(vec.x*moveFlag.x, vec.y*moveFlag.y);
			//�v���C���[�x�N�g�����Z
			j += vec;
			//�n�ʃe�N�X�`���T�C�Y
			Vector2 size = i.size;
			//x���̃��[�v
			if (j.x <= -size.x)
				j.x = size.x + i.size.x + j.x;
			else if (j.x >= size.x)
				j.x = -size.x - i.size.x + j.x;
		}
		layerNum--;
	}
	//�n�ʃe�N�X�`���T�C�Y
	Vector2 size = upBackStates.size;
	//��n
	for (auto& i : upBackStates.positions)
	{
		//��ԉ��̑��x�ƈꏏ�ɂ���
		Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / backStates.size());
		//�ړ�����ꍇflag�ɂ�1���A�ړ����Ȃ��ꍇflag�ɂ�0��
		vec = Vector2(vec.x*moveFlag.x, vec.y*moveFlag.y);
		//�v���C���[���x���Z
		i += vec;
		//x���̃��[�v
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y���̃��[�v
		if (i.y <= -size.y)
			i.y = size.y + size.y + i.y;
		else if (i.y >= size.y)
			i.y = -size.y - size.y + i.y;
	}
	//�n���n
	for (auto& i : downBackStates.positions)
	{
		//��ԉ��̑��x�ƈꏏ�ɂ���
		Vector2 vec = mPlayer->GetSpringVelo()*(1.0f / backStates.size());
		//�v���C���[���x���Z
		i += vec;
		//x���̃��[�v
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y���̃��[�v
		if (i.y <= -size.y)
			i.y = size.y + size.y + i.y;
		else if (i.y >= size.y)
			i.y = -size.y - size.y + i.y;
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
	//for (auto i : downBackStates.positions)
	//{
	//	DrawGraph(i.x, i.y, downBackStates.id, true);
	//}
}