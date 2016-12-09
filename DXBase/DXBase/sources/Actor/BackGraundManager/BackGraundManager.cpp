#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
#include "../../Actor/Person/Player/PlayerBody.h"
#include "../../World/IWorld.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	stageFlag(true),
	mWorld(world)
{
	////�v���C���[�ϊ�
	//mPlayer = dynamic_cast<PlayerBody*>(world->findActor("Player").get());
	mFloor = dynamic_cast<MovelessFloor*>(world->findActor("MovelessFloor").get());
}

BackGraundManager::~BackGraundManager()
{
}

void BackGraundManager::SetBackGraund(TextureID id1, TextureID id2,bool frontGraund)
{
	BackGraundState backState;
	//�T�C�Y��ǉ�
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id1);
	Vector2 size = backState.size;
	//��O�ɕ\�����邩
	backState.frontGraundFlag = frontGraund;
	//�|�W�V�����Ɣԍ���ݒ�
	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id1);
	indexPos.position = Vector2::Zero;
	backState.indexPos.push_back(indexPos);
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id2);
	indexPos.position = Vector2(size.x, 0.0f);
	backState.indexPos.push_back(indexPos);
	//�����
	backStates.push_back(backState);
}

void BackGraundManager::SetTateBackGraund(TextureID id1, TextureID id2)
{
	BackGraundState backState;
	//�T�C�Y��ǉ�
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id1);
	Vector2 size = backState.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id1);
	indexPos.position = Vector2::Zero;
	backState.indexPos.push_back(indexPos);
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id2);
	indexPos.position = Vector2(0.0f, -size.y);
	backState.indexPos.push_back(indexPos);
	//�����
	backStates.push_back(backState);
}

void BackGraundManager::SetTateYokoBackGraund(TextureID id)
{
	//�T�C�Y�擾
	tateYokoState.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = tateYokoState.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);

	indexPos.position = Vector2(size.x, 0.0f);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(-size.x, 0.0f);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, size.y);
	tateYokoState.indexPos.push_back(indexPos);
	indexPos.position = Vector2(-size.x, size.y);
	tateYokoState.indexPos.push_back(indexPos);

}

void BackGraundManager::SetUpBackGraund(TextureID id)
{
	//�T�C�Y��ǉ�
	upBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);

	indexPos.position = Vector2::Zero;
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(0, -size.y);
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, -size.y);
	upBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, 0);
	upBackStates.indexPos.push_back(indexPos);
}

void BackGraundManager::SetDownBackGraund(TextureID id)
{
	//id��ǉ�
	downBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//�T�C�Y��ǉ�
	downBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = upBackStates.size;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);
	indexPos.position = Vector2(Vector2(0, size.y));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(0, size.y * 2));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(size.x, size.y));
	downBackStates.indexPos.push_back(indexPos);
	indexPos.position = Vector2(Vector2(size.x, size.y * 2));
	downBackStates.indexPos.push_back(indexPos);


}

void BackGraundManager::AllDeleteBackGraund()
{
}

void BackGraundManager::Update(float deltatime)
{
	//�v�f���������Ȃ�������v���C���[��null�������烊�^�[��
	if (backStates.empty()) return;
	//�w�i�K�w�̐����擾
	float layerNum = backStates.size();
	//�n�ʌn
	//�R�s�[���g��Ȃ����߂Ɂ���t���ĎQ�Ƃ���(for����i�̒��g��M��ꍇ�Ɏg��)
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			//�v���C���[�x�N�g�����Z
			j.position += -mFloor->mVelo*(1.0f / layerNum);
			//�n�ʃe�N�X�`���T�C�Y
			Vector2 size = i.size;
			//x���̃��[�v
			if (j.position.x <= -size.x)
				j.position.x = size.x + i.size.x + j.position.x;
			else if (j.position.x >= size.x)
				j.position.x = -size.x - i.size.x + j.position.x;
			//�n�オ�����Ă��邩
			if (j.position.y <= -size.y)
				stageFlag = false;
			else
				stageFlag = true;

		}
		layerNum--;
	}
	//�n�ʃe�N�X�`���T�C�Y
	Vector2 size = upBackStates.size;
	//��n
	for (auto& i : upBackStates.indexPos)
	{
		//�v���C���[���x���Z
		i.position += -mFloor->mVelo*(1.0f / backStates.size());
		//x���̃��[�v
		if (i.position.x <= -size.x)
			i.position.x = size.x + size.x + i.position.x;
		else if (i.position.x >= size.x)
			i.position.x = -size.x - size.x + i.position.x;
		//Y���̃��[�v
		if (i.position.y <= -size.y)
			i.position.y = size.y + size.y + i.position.y;
		else if (i.position.y >= size.y)
			i.position.y = -size.y - size.y + i.position.y;
	}
	//�n���n
	for (auto& i : downBackStates.indexPos)
	{
		//�v���C���[���x���Z
		i.position += -mFloor->mVelo;
		//x���̃��[�v
		if (i.position.x <= -size.x)
			i.position.x = size.x + size.x + i.position.x;
		else if (i.position.x >= size.x)
			i.position.x = -size.x - size.x + i.position.x;
		//Y���̃��[�v(�n�オ�����Ă��Ȃ������ꍇ)
		if (!stageFlag)
		{
			if (i.position.y <= -size.y)
				i.position.y = size.y + size.y + i.position.y;
			else if (i.position.y >= size.y)
				i.position.y = -size.y - size.y + i.position.y;
		}
	}
}

void BackGraundManager::TateUpdate(float deltaTime)
{
	//�v�f���������Ȃ�������v���C���[��null�������烊�^�[��
	if (backStates.empty()) return;
	//�w�i�K�w�̐����擾
	float layerNum = backStates.size();
	//�n�ʌn
	//�R�s�[���g��Ȃ����߂Ɂ���t���ĎQ�Ƃ���(for����i�̒��g��M��ꍇ�Ɏg��)
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			//�v���C���[�x�N�g�����Z
			j.position += -mFloor->mVelo*(1.0f / layerNum);
			//�n�ʃe�N�X�`���T�C�Y
			Vector2 size = i.size;
			//x���̃��[�v
			if (j.position.y <= -size.y)
				j.position.y = size.y + i.size.y + j.position.y;
			else if (j.position.y >= size.y)
				j.position.y = -size.y - i.size.y + j.position.y;
		}
		layerNum--;
	}
	//�c�ł̃X�N���[���̏ꍇ���w�i��x�����[�v�͂Ȃ�
	for (auto& i : tateYokoState.indexPos)
	{
		Vector2 size = tateYokoState.size;
		//�v���C���[���x���Z
		i.position += -mFloor->mVelo;
		//Y���̃��[�v(�n�オ�����Ă��Ȃ������ꍇ)
		if (i.position.y <= -size.y)
			i.position.y = size.y + size.y + i.position.y;
		else if (i.position.y >= size.y)
			i.position.y = -size.y - size.y + i.position.y;
	}
}

void BackGraundManager::Draw() const
{
	//��̕`��
	for (auto i : upBackStates.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
	//�n��̕`��
	for (auto i : backStates)
	{
		for (auto j : i.indexPos)
		{
			if(!i.frontGraundFlag)
			DrawGraph(j.position.x, j.position.y, j.index, true);
		}
	}
	//�n���̕`��
	for (auto i : downBackStates.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
	//�c���̃X�N���[��
	for (auto i : tateYokoState.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
}

void BackGraundManager::BackDraw() const
{
	//�n��̕`��
	for (auto i : backStates)
	{
		for (auto j : i.indexPos)
		{
			if (i.frontGraundFlag)
				DrawGraph(j.position.x, j.position.y, j.index, true);
		}
	}
}

void BackGraundManager::Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness, float friction, float mass)
{
	// �o�l�̐L�ы���v�Z
	Vector2 stretch = (pos - resPos);
	// �o�l�̗͂��v�Z
	Vector2 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector2 acceleration = force / mass;
	// �ړ����x���v�Z
	velo = friction * (velo + acceleration);

	pos = pos + velo;
}
