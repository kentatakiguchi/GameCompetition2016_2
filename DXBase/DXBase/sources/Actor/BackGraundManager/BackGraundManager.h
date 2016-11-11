#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
class TestPlayer;
class Player;

struct BackGraundState
{
	//�e�N�X�`��id
	int id = 0;
	//�e�N�X�`���T�C�Y
	Vector2 size = Vector2::Zero;
	//2�摜�𒣂邽�߂̍��W
	std::list<Vector2> positions;
	//�␳�֌W
	Vector2 resVelo = Vector2::Zero;
	Vector2 springVelo = Vector2::Zero;
	Vector2 velocity = Vector2::Zero;
};

class BackGraundManager
{
public:
	BackGraundManager(IWorld* world);
	~BackGraundManager();
	//�w�i��ݒ肷��i���[�h�����e�N�X�`������j
	void SetBackGraund(TextureID id);
	//�w�i�i��j��ݒ肷��i���[�h�����e�N�X�`������j
	void SetUpBackGraund(TextureID id);
	//�n�ʂ�ݒ肷��(���[�h�����e�N�X�`������)
	void SetDownBackGraund(TextureID id);
	//�w�i��S������
	void AllDeleteBackGraund();
	void Update(float deltatime);
	void Draw() const;

	//�o�l
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness=0.05f, float friction=0.5f, float mass=2.0f);

private:
	//���[���h
	IWorld* mWorld;
	//�v���C���[
	Player* mPlayer;
	//�n�オ�\������Ă��邩�H
	bool stageFlag;
	//�n��̔w�i
	std::list<BackGraundState> backStates;
	//��̔w�i
	BackGraundState upBackStates;
	//�n�ʂ̔w�i
	BackGraundState downBackStates;
	//�␳�֌W
	Vector2 restPos;
	Vector2 velo;
};