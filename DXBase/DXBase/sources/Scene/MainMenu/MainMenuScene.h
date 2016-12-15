#pragma once

#include "../Base/IScene.h"
#include"../../Math/Vector2.h"
#include"SceneChange.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"


class MainMenuScene : public IScene {
public:
	MainMenuScene(SceneDataKeeper* keeper);
	~MainMenuScene();
	virtual void start() override;
	virtual void update() override;
	void slideText(int targettext);
	void moveText(int targettext);
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	bool isTitle_;

	int slideSize;
	
	int id;
	int targetPoint;
	int sinCount;
	int alphaCou[2];
	int alphadefSpeeds[2];

	std::map<int,Vector2> textPoses;
	std::map<int,Scene> nextScene;
	std::map<int, Vector2> lastPoses;

	std::map<int, Vector2> shotPos;
	std::map<int, int> defposlist;
	std::map<int, Vector2> setPoses;
	std::map<int, int> boundCou;
	std::map<int, bool> isPoint;
	std::map<int, bool> isShotArrive;
	std::map<int, bool> isArrive;

	std::map<int, int> titleBackStageNum;
	//�w�i��ύX���鎞�Ԃ�ݒ肷��
	std::map<int, float> titleBackChangeTime;
	//�e�ԍ��ŕ\�������摜��ID���Z�b�g���Ă���
	std::map<int, TextureID> baseTitleBackID;
	//���݂̔w�i�摜��ID
	std::vector<TextureID> currentTitleBackID;
	//�w�i�摜��ύX����^�C�~���O�����߂�
	std::map<int, bool> changeBackChecker;
	//�w�i�摜�̈ړ�������߂�
	std::vector<int> changeTargetChecker;

};

