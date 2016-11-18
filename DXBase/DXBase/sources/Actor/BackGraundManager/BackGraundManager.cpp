#include "BackGraundManager.h"
#include "../TestPlayer/TestPlayer.h"
#include "../Person/Player/Player.h"
#include "../../Actor/Person/Player/PlayerBody.h"
#include "../../World/IWorld.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	stageFlag(true),
	mWorld(world)
{
	//������Ȃ�����ꉞ
	for (auto& i : backStates)
		i.positions.clear();
	backStates.clear();
	////�v���C���[�ϊ�
	//mPlayer = dynamic_cast<PlayerBody*>(world->findActor("Player").get());
	mFloor = dynamic_cast<MovelessFloor*>(world->findActor("MovelessFloor").get());
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
	downBackStates.positions.push_back(Vector2(0, size.y * 2));
	downBackStates.positions.push_back(Vector2(size.x, size.y));
	downBackStates.positions.push_back(Vector2(size.x, size.y * 2));
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
	if (backStates.empty()) return;
	//�w�i�K�w�̐����擾
	float layerNum = backStates.size();
	//�n�ʌn
	//�R�s�[���g��Ȃ����߂Ɂ���t���ĎQ�Ƃ���(for����i�̒��g��M��ꍇ�Ɏg��)
	for (auto& i : backStates)
	{
		for (auto& j : i.positions)
		{
			//�v���C���[�x�N�g�����Z
			j += -mFloor->mVelo*(1.0f / layerNum);
			//�n�ʃe�N�X�`���T�C�Y
			Vector2 size = i.size;
			//x���̃��[�v
			if (j.x <= -size.x)
				j.x = size.x + i.size.x + j.x;
			else if (j.x >= size.x)
				j.x = -size.x - i.size.x + j.x;
			//�n�オ�����Ă��邩
			if (j.y <= -size.y)
				stageFlag = false;
			else
				stageFlag = true;

		}
		layerNum--;
	}
	//�n�ʃe�N�X�`���T�C�Y
	Vector2 size = upBackStates.size;
	//��n
	for (auto& i : upBackStates.positions)
	{
		//�v���C���[���x���Z
		i += -mFloor->mVelo*(1.0f / backStates.size());
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
		//�v���C���[���x���Z
		i += -mFloor->mVelo;
		//x���̃��[�v
		if (i.x <= -size.x)
			i.x = size.x + size.x + i.x;
		else if (i.x >= size.x)
			i.x = -size.x - size.x + i.x;
		//Y���̃��[�v(�n�オ�����Ă��Ȃ������ꍇ)
		if (!stageFlag)
		{
			if (i.y <= -size.y)
				i.y = size.y + size.y + i.y;
			else if (i.y >= size.y)
				i.y = -size.y - size.y + i.y;
		}
	}
}

void BackGraundManager::Draw() const
{
	//��̕`��
	for (auto i : upBackStates.positions)
	{
		DrawGraph(i.x, i.y, upBackStates.id, true);
	}
	//�n��̕`��
	for (auto i : backStates)
	{
		for (auto j : i.positions)
		{
			DrawGraph(j.x, j.y, i.id, true);
		}
	}
	//�n���̕`��
	for (auto i : downBackStates.positions)
	{
		DrawGraph(i.x, i.y, downBackStates.id, true);
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
