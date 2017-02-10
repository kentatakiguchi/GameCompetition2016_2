#pragma once

#include "../Math/Vector2.h"
#include "../World/IWorld.h"
#include "PlayerTxt.h"
#include "../Math/MathHelper.h"
#include <memory>
#include <map>
#include "../Actor/Base/Actor.h"
enum TxtEvent
{
	START_EVENT,
	STARGET_EVENT,
	GOOL_EVENT
};
class PlayerFont {

public:

	typedef std::shared_ptr<PlayerTxt> PlayerTxtPtr;
public:
	PlayerFont(IWorld* world, const Vector2& pos);
	~PlayerFont();
	void Update();
	void Draw();
public:
	//�t�H���g���X�^�[�g����
	void StartFont();
	//�t�H���g���`�F���W
	void ChangeFont(TxtEvent txtEvent);
	//�C�x���g��ǉ����� ����: �C�x���gID�@�C�x���g�̃e�L�X�g�t�@�C���p�X �t�@�C���̉��s��
	void AddEvent(TxtEvent txtEvent, char* txtFile, int lineNum);
	bool GetEndFont();
private:

	IWorld* world_;
	//
	Actor* playerB;
	Actor* playerR;
	Actor* bossC;
	//�v���C���[�̍��W
	Vector2 playerPosB;
	Vector2 playerPosR;
	Vector2 bossPosC;
	//�����o���̍��W�����܂�
	Vector2 fontPosB_;
	Vector2 fontPosR_;
	Vector2 fontPosC_;
	//���l
	float alphaB_;
	float alphaR_;
	float alphaC_;
	std::map<TxtEvent, PlayerTxtPtr> eventFonts_;

	//���݂��Ă���C�x���g
	TxtEvent nowEvent_;

	bool isPlayFont_;


	Vector2 textSize_;

};