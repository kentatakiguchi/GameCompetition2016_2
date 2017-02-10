#pragma once
#include "TxtRead.h"
#include "../Math/Vector2.h"
enum PlayerEnum
{
	BUTTY,
	RETTY,
	COCOCO
};
class PlayerTxt {
public:
	struct TxtState
	{
		std::string txt;
		PlayerEnum speekPlayer;
		bool lineFlag;
	};
	PlayerTxt(char * fileName, int lineNum);
	~PlayerTxt();
	void Update();
	void Draw(const Vector2& pos,float size);

	//�C�x���g���I��������ǂ���
	bool isEndEvent();
	//���ݒ����Ă���v���C���[�擾
	PlayerEnum GetSpeekPlayer();
private:
	//�X�e�[�W�ł���ׂ�S��
	std::vector<TxtState> txts_;
	//�i�񂾉�b�J�E���g
	int speekCount_;
	//�I����b�J�E���g
	int speedEndCount_;
	//�^�C�}�[
	float speekTimer_;
	//�������ǂ�ǂ�o�Ă���J�E���g
	int characterCount_;
	int characterCountLine_;
	//�\���p�e�L�X�g
	std::string drawTxt_;
	//���s�p�\���e�L�X�g
	std::string drawLineTxt_;
	//�O�ɒ����Ă������
	PlayerEnum prePlayer_;
	//���ݒ����Ă���z
	PlayerEnum nowPlayer_;
	//���邩�ǂ���
	bool isSpeekFlag_;
	//����I�������
	bool isSpeekEnd_;
	//������Ԃ̎���
	float nextSpeekTimer_;
	//�S�Ă̒��肪�I��������ǂ���
	bool isAllSpeekEnd_;
};