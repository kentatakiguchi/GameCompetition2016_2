#pragma once
#include "../../ResourceLoader/ResourceLoader.h"
#include <list>
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
class TestPlayer;

struct BackGraundState
{
	//�e�N�X�`��id
	int id = 0;
	//�e�N�X�`���T�C�Y
	Vector2 size = Vector2::Zero;
	//2�摜�𒣂邽�߂̍��W
	std::list<Vector2> positions;
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

private:
	//���[���h
	IWorld* mWorld;
	//�v���C���[
	TestPlayer* mPlayer;
	//�n��̔w�i
	std::list<BackGraundState> backStates;
	//��̔w�i
	BackGraundState upBackStates;
	//�n�ʂ̔w�i
	BackGraundState downBackStates;
	//�␳�֌W
	Vector3 restPos;
	Vector3 velo;
};