#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include <vector>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
#include "../../Field/MovelessFloor.h"
#include "../../Scene/StageClear/SceneChangeBossAnm.h"
class TestPlayer;
class Player;

struct IndexPos 
{
	int index;
	Vector2 position;
};
struct KonohaState {
	Vector2 position = Vector2::Zero;
	Vector2 lerpPosition = Vector2::Zero;
	Vector2 velo = Vector2::Zero;
	int index;
	float lerpTimer = 0.0f;
};
struct BackGraundState
{
	//�e�N�X�`��id
	int id = 0;
	//Actor�̑O�ɕ\�����邩
	bool frontGraundFlag=false;
	//�e�N�X�`���T�C�Y
	Vector2 size = Vector2::Zero;
	//2�摜�𒣂邽�߂̍��W
	std::list<IndexPos> indexPos;
	//�摜�̃X�P�[��
	Vector2 scale = Vector2(1, 1);
	//���C���[
	int layer;
	//stage2��
	bool stage2;

};

class BackGraundManager
{
public:
	BackGraundManager(IWorld* world);
	BackGraundManager();
	~BackGraundManager();
	//�w�i��ݒ肷��i���[�h�����e�N�X�`������j
	void SetBackGraund(TextureID id1, TextureID id2, float heightY = 0.0f, bool frontGraund = false, bool stage2 = false,const Vector2& scale=Vector2(1,1));
	//�c�̔w�i��ݒ肷��i���[�h�����e�N�X�`������j
	void SetTateBackGraund(TextureID id1, TextureID id2, const Vector2& scale=Vector2(1.0f,1.0f));
	//�c�̉��̔w�i��ݒ肷��(���[�h�����e�N�X�`������)
	void SetTateYokoBackGraund(TextureID id1);
	//�w�i�i��j��ݒ肷��i���[�h�����e�N�X�`������j
	void SetUpBackGraund(TextureID id, int layer,bool flag=false);
	//�n�ʂ�ݒ肷��(���[�h�����e�N�X�`������)
	void SetDownBackGraund(TextureID id);

	//�w�i��S������
	void AllDeleteBackGraund();
	//���p�X�N���[��Update
	void Update(float deltatime, bool title = false);
	//�c�p�X�N���[��Update
	void TateUpdate(float deltaTime);

	void Draw(bool title=false) const;

	void BackDraw()const;

	//�o�l
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness = 0.05f, float friction = 0.5f, float mass = 2.0f);
public:
	//���̗t�̏����ݒ�
	void AddKonoha(const TextureID& id);
	//�{�X���o�������ꍇ��true
	void BossFlag(bool flag=false);
private:
	void konohaUpdate();
	//�{�X��Update
	void BossUpdate();
private:
	//���[���h
	IWorld* mWorld;
	//�u���b�N
	Player* mFloor;
	//�n�オ�\������Ă��邩�H
	bool stageFlag;
	//�n��̔w�i
	std::list<BackGraundState> backStates;
	//��̔w�i
	std::list<BackGraundState> upBackStates;
	//�n�ʂ̔w�i
	BackGraundState downBackStates;
	//�c�X�N���[���̉��̔w�i
	BackGraundState tateYokoState;
	//���̂͂�ID
	std::vector<TextureID> konohaIds;
	//���̂̓X�e�[�g
	std::list<KonohaState>konohaStates;
	//���̂̓^�C�}�[
	float konohaTimer;
	//���̂̓����_���^�C��
	float konohaRandTime;
	//�w�i�̃{�X�̃A�j���[�V����
	SceneChangeBossAnm anim;
	//�{�X�̎q���A�j���[�V����
	SceneChangeBossAnm childanim;
	//�{�X�o������
	float bossTimer;
	//�{�X�o�������J�E���g
	float bossCount;
	//�{�X�|�W�V����
	Vector2 bossPos;
	//�{�X���o�����邩�ǂ���
	bool bossFlag;
	//�{�X�̎q���|�W�V����
	std::vector<Vector2> mBossChilds;
	//�q�����o�����邩�t���O
	int mChildFlag;
	//�q���������Ƃ��{�X���U���������
	float bossTurn;
	//�q���������Ƃ��Ƀ{�X���U������Ă��鎞��
	float bossTurnTime;
	float bossTurnCount;
	bool bossTurnFlag;
};