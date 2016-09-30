#ifndef _ISCENE_H_
#define _ISCENE_H_

#include "DxLib.h"

#include "Scene.h"

#include "../../Game/Time.h"

//�V�[�����ۃC���^�[�t�F�[�X
class IScene{
public:
	//���z�f�X�g���N�^
	virtual ~IScene(){}
	//������
	virtual void start() = 0;
	//�X�V
	virtual void update() = 0;
	//�`��
	virtual void draw() const = 0;
	//�I���t���O
	virtual bool isEnd() const = 0;
	//���̃V�[��
	virtual Scene next() const = 0;
	//�I��
	virtual void end() = 0;
public:
	bool isEnd_;
};

#endif