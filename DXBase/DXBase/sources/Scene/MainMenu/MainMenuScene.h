#pragma once

#include "../Base/IScene.h"
#include"../../Math/Vector2.h"
#include"SceneChange.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include "../../Animation/Player/PlayerAnimation2D.h"

class BackGraundManager;

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
	virtual std::string nextName()  override {
		if (nextScene.at(targetPoint) == Scene::GameEnd)return "GameEnd";
		else {
			return "next";
		}
	}
private:
	bool isTitle_;
	bool isDrawAlphaBack_;
	bool isSelectGamePlay_;
	Vector2 gamePlaySlimePos_;
	//�`�F���W����J�E���g
	float alphaSlideCount_;
	//��񂵂�����Ȃ��悤�ɂ���t���O
	bool oneFlag_;
	int slideSize;
	
	int id;
	int targetPoint;
	int sinCount;
	int alphaCou[2];
	int alphadefSpeeds[2];

	float titleBackAlpha_;
	//�`�F���W����o�b�N���
	int backNum_;
	BackGraundManager* backManager;


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
	std::map<int, TextureID> textIDs;
	//�w�i�摜����
	typedef std::vector<TextureID> BackTitles;
	std::vector<BackTitles> titleTexs;

	// �L�����A�j���[�V����
	PlayerAnimation2D mButtyAnim;
	PlayerAnimation2D mRettyAnim;
	// �I�����̍��W
	Vector2 mCursorPos;
};

