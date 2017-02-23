#include "BackGraundManager.h"
#include "../Person/Player/Player.h"
#include "../../Actor/Person/Player/PlayerBody.h"
#include "../../World/IWorld.h"
#include "../../Game/Time.h"
#include "../../Define.h"
BackGraundManager::BackGraundManager(IWorld * world) :
	stageFlag(true),
	mWorld(world),
	konohaTimer(0.0f),
	konohaRandTime(1.0f),
	bossCount(60.0f),
	bossTimer(0.0f),
	bossFlag(false),
	bossTurn(true),
	bossTurnCount(0.0f),
	bossTurnTime(0.0f)
{
	////�v���C���[�ϊ�
	//mPlayer = dynamic_cast<PlayerBody*>(world->findActor("Player").get());
	//mFloor = dynamic_cast<Player*>(world->findActor("Player").get());
	//�{�X�A�j���[�V��������
	if (bossFlag) {
		anim = SceneChangeBossAnm();
		childanim = SceneChangeBossAnm(4.0f);
		mChildFlag = rand() % 2;
	}

	bossPos = Vector2(SCREEN_SIZE.x + 128.0f, SCREEN_SIZE.y / 3);
	mBossChilds.push_back(Vector2(-64, -64));
	mBossChilds.push_back(Vector2(-90, 20));
	mBossChilds.push_back(Vector2(-256, 0));
	mBossChilds.push_back(Vector2(-89, 70));
	mBossChilds.push_back(Vector2(-189, -30));
	mBossChilds.push_back(Vector2(-200, 96));
	mBossChilds.push_back(Vector2(-230, -55));
}

BackGraundManager::BackGraundManager() :
	mWorld(nullptr)
{
}

BackGraundManager::~BackGraundManager()
{
}

void BackGraundManager::SetBackGraund(TextureID id1, TextureID id2, float heightY, bool frontGraund, bool stage2, const Vector2& scale)
{
	BackGraundState backState;
	backState.stage2 = stage2;
	//�T�C�Y��ǉ�
	backState.size = ResourceLoader::GetInstance().GetTextureSize(id1)*scale;
	Vector2 size = backState.size;
	//��O�ɕ\�����邩
	backState.frontGraundFlag = frontGraund;
	backState.scale = scale;
	//�|�W�V�����Ɣԍ���ݒ�
	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id1);
	indexPos.position = Vector2(0, heightY*scale.y);
	backState.indexPos.push_back(indexPos);
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id2);
	indexPos.position = Vector2(size.x, heightY*scale.y);
	backState.indexPos.push_back(indexPos);
	//�����
	backStates.push_back(backState);
}

void BackGraundManager::SetTateBackGraund(TextureID id1, TextureID id2, const Vector2& scale)
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

void BackGraundManager::SetUpBackGraund(TextureID id, int layer,bool flag)
{
	BackGraundState state;

	//�T�C�Y��ǉ�
	state.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = state.size;
	state.layer = layer;

	IndexPos indexPos;
	indexPos.index = ResourceLoader::GetInstance().getTextureID(id);
	state.frontGraundFlag = flag;
	indexPos.position = Vector2::Zero;
	state.indexPos.push_back(indexPos);
	indexPos.position = Vector2(0, -size.y);
	state.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, -size.y);
	state.indexPos.push_back(indexPos);
	indexPos.position = Vector2(size.x, 0);
	state.indexPos.push_back(indexPos);

	upBackStates.push_back(state);
}

void BackGraundManager::SetDownBackGraund(TextureID id)
{
	//id��ǉ�
	downBackStates.id = ResourceLoader::GetInstance().getTextureID(id);
	//�T�C�Y��ǉ�
	downBackStates.size = ResourceLoader::GetInstance().GetTextureSize(id);
	Vector2 size = downBackStates.size;

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
	backStates.clear();
}

void BackGraundManager::Update(float deltatime, bool title)
{
	//�؂̗t�A�b�v�f�[�g
	if (!title)
		konohaUpdate();
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
			if (!title) {
				//�v���C���[�x�N�g�����Z
				if (i.stage2)
					j.position -= Vector2((mWorld->GetInvVelo()*(1.0f / layerNum)).x, mWorld->GetInvVelo().y);
				else
					j.position -= mWorld->GetInvVelo()*1.0f / layerNum;
			}
			else {
				j.position -= Vector2(10.0f, 0.0f)*(1.0f / layerNum);
			}
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

	//��n

	for (auto & i : upBackStates) {
		//�n�ʃe�N�X�`���T�C�Y
		Vector2 size = i.size;
		for (auto& j : i.indexPos) {
			//�v���C���[���x���Z(�^�C�g���p������)
			if (!title)
				j.position -= mWorld->GetInvVelo()*(1.0f / i.layer);
			else
				j.position -= Vector2(10, 0)*(1.0f / layerNum);

			//x���̃��[�v
			if (j.position.x <= -size.x)
				j.position.x = size.x + size.x + j.position.x;
			else if (j.position.x >= size.x)
				j.position.x = -size.x - size.x + j.position.x;
			//Y���̃��[�v
			if (j.position.y <= -size.y)
				j.position.y = size.y + size.y + j.position.y;
			else if (j.position.y >= size.y)
				j.position.y = -size.y - size.y + j.position.y;
		}
	}

	//for (auto& i : upBackStates.indexPos)
	//{
	//	//�v���C���[���x���Z(�^�C�g���p������)
	//	if (!title)
	//		i.position -= Vector2((mWorld->GetInvVelo()*(1.0f / upBackStates.layer)).x, mWorld->GetInvVelo().y);
	//	else
	//		i.position -= Vector2(10, 0)*(1.0f / layerNum);
	//	//x���̃��[�v
	//	if (i.position.x <= -size.x)
	//		i.position.x = size.x + size.x + i.position.x;
	//	else if (i.position.x >= size.x)
	//		i.position.x = -size.x - size.x + i.position.x;
	//	if (stageFlag)
	//	{
	//		//Y���̃��[�v
	//		if (i.position.y <= -size.y)
	//			i.position.y = size.y + size.y + i.position.y;
	//		else if (i.position.y >= size.y)
	//			i.position.y = -size.y - size.y + i.position.y;
	//	}
	//}
	//Vector2 size = downBackStates.size;
	////�n���n
	//for (auto& i : downBackStates.indexPos)
	//{
	//	//�v���C���[���x���Z
	//	if (!title)
	//		i.position += -mWorld->GetInvVelo();
	//	//x���̃��[�v
	//	if (i.position.x <= -size.x)
	//		i.position.x = size.x + size.x + i.position.x;
	//	else if (i.position.x >= size.x)
	//		i.position.x = -size.x - size.x + i.position.x;
	//	//Y���̃��[�v(�n�オ�����Ă��Ȃ������ꍇ)
	//	if (!stageFlag)
	//	{
	//		if (i.position.y <= -size.y)
	//			i.position.y = size.y + size.y + i.position.y;
	//		else if (i.position.y >= size.y)
	//			i.position.y = -size.y - size.y + i.position.y;
	//	}
	//}
	if (!title&&bossFlag)
		BossUpdate();
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
			j.position += -mWorld->GetInvVelo()*(1.0f / layerNum);
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
	////�c�ł̃X�N���[���̏ꍇ���w�i��x�����[�v�͂Ȃ�
	//for (auto& i : tateYokoState.indexPos)
	//{
	//	Vector2 size = tateYokoState.size;
	//	//�v���C���[���x���Z
	//	i.position += -mWorld->GetInvVelo();
	//	//Y���̃��[�v(�n�オ�����Ă��Ȃ������ꍇ)
	//	if (i.position.y <= -size.y)
	//		i.position.y = size.y + size.y + i.position.y;
	//	else if (i.position.y >= size.y)
	//		i.position.y = -size.y - size.y + i.position.y;
	//}
}

void BackGraundManager::Draw(bool title) const
{
	int wari = 1;
	if (title) wari = 2;

	//��̕`��
	int count = 0;
	for (auto& i : upBackStates)
	{
		count++;
		if (!i.frontGraundFlag) {
			for (auto& j : i.indexPos)
			{
				DrawGraph(j.position.x, j.position.y, j.index, true);
				if (count == 1 && bossFlag) {
					if (mChildFlag == 1) {
						for (const auto& i : mBossChilds) {
							childanim.draw_e(bossPos + i, Vector2::Zero, 0.2f, 0.0f);
						}
						anim.drawTurn(bossPos, Vector2::Zero, 0.75f, 0.0f, Vector3(255, 255, 255), bossTurnFlag);
					}
					else
						anim.draw_e(bossPos, Vector2::Zero, 0.75f, 0.0f);
				}
			}
		}
	}
	//�n��̕`��
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			if (!i.frontGraundFlag)
				DrawRotaGraph(j.position.x + i.size.x / 2, j.position.y + i.size.y/wari, i.scale.x, 0, j.index, true);
		}
	}
	for (auto& i : upBackStates) {
		if (i.frontGraundFlag) {
			for (auto& j : i.indexPos) {
				DrawGraph(j.position.x, j.position.y, j.index, true);
			}
		}
	}

	////�n���̕`��
	//for (auto& i : downBackStates.indexPos)
	//{
	//	DrawGraph(i.position.x, i.position.y, i.index, true);
	//}
	//�c���̃X�N���[��
	for (auto& i : tateYokoState.indexPos)
	{
		DrawGraph(i.position.x, i.position.y, i.index, true);
	}
}

void BackGraundManager::BackDraw() const
{
	//�؂̗t�̕`��
	for (auto& i : konohaStates) {
		DrawGraph(i.position.x + i.lerpPosition.x, i.position.y + i.lerpPosition.y, i.index, true);
	}

	//�n��̕`��
	for (auto& i : backStates)
	{
		for (auto& j : i.indexPos)
		{
			if (i.frontGraundFlag)
				DrawRotaGraph(j.position.x + i.size.x / 2, j.position.y + i.size.y, i.scale.x, 0, j.index, true);
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

void BackGraundManager::AddKonoha(const TextureID& id)
{
	konohaIds.push_back(id);
}

void BackGraundManager::BossFlag(bool flag)
{
	bossFlag = flag;
}

void BackGraundManager::konohaUpdate()
{
	//�؂̗t�̋���
	if (konohaIds.empty()) return;
	konohaTimer += Time::GetInstance().deltaTime();
	if (konohaTimer >= konohaRandTime) {
		//���̗t�̏o���ʒu��ݒ�
		int randNum = rand() % konohaIds.size();
		int randPosX = rand() % (int)(SCREEN_SIZE.x + 2048.0f);
		int randPosY = rand() % 256;
		konohaRandTime = rand() % 3;
		randPosX -= 1024.0f;
		randPosY -= 128.0f;
		//�؂̗t�X�e�[�^�X�ɑ��
		KonohaState state;
		state.index = ResourceLoader::GetInstance().getTextureID(konohaIds[randNum]);
		state.position = Vector2(randPosX, randPosY);
		konohaStates.push_back(state);
		konohaTimer = 0.0f;
	}



	for (auto& i : konohaStates) {
		i.lerpTimer += 0.5f*Time::GetInstance().deltaTime();
		i.velo.y += 7.0f; Time::GetInstance().deltaTime();
		i.velo -= mWorld->GetInvVelo();
		float x = MathHelper::Lerp(-128, 128, MathHelper::Sin(MathHelper::Lerp(0, 180, i.lerpTimer)));
		float y = MathHelper::Lerp(-128, 64, MathHelper::Sin(MathHelper::Lerp(0, 180, i.lerpTimer)));
		i.lerpPosition = Vector2(x, y) + i.velo;
	}
}

void BackGraundManager::BossUpdate()
{
	bossTimer += Time::GetInstance().deltaTime();

	bossPos.x += 170.0f*Time::GetInstance().deltaTime();
	anim.Turn();
	anim.setIdle();
	childanim.Turn();
	childanim.setIdle();
	if (bossPos.x >= SCREEN_SIZE.x + 256.0f && (bossTimer >= bossCount)) {
		bossPos.x = -128.0f;
		mChildFlag = rand() % 3;
		bossTurnTime = GetRand(3) + 5;
		bossTimer = 0.0f;
		bossTurnCount = 0.0f;
	}

	bossTurnFlag = true;
	if (bossTimer >= bossTurnTime) {
		bossTurnCount += Time::GetInstance().deltaTime();
		bossTurnFlag = false;
		if (bossTurnCount >= 4.0f) {
			bossTurnFlag = true;
		}
	}

	bossPos += -mWorld->GetInvVelo() / 20.0f;

	anim.update_e(Time::GetInstance().deltaTime());
	childanim.update_e(Time::GetInstance().deltaTime()*3.0f);
}
