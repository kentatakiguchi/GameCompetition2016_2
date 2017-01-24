#ifndef _ISCENE_H_
#define _ISCENE_H_

#include "DxLib.h"

#include "Scene.h"

#include "../../Game/Time.h"
#include"../Base/SceneDataKeeper.h"
#include"../../Renderer/FontManager.h"
#include"../../Define.h"
#include<vector>

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
	std::string getName() {
		return name_;
	}
	virtual std::string nextName() {
		return "next";
	}
	void setName(std::string name) {
		name_=name;
	}
public:
	bool isEnd_;
	SceneDataKeeper* keeper_;
	std::string name_;
	std::vector<std::string> changeTextList;
	std::vector<std::vector<std::string>> listBase;
	std::vector<Vector2> textPosList;
};

#endif