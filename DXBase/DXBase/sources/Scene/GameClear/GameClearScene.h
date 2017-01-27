#ifndef GAME_CLEAR_SCENE_H_
#define GAME_CLEAR_SCENE_H_

#include "../Base/IScene.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include"../StageClear/StageClearTextAnm.h"
#include "../../Animation/Player/PlayerAnimation2D.h"

class GameClearScene : public IScene {
public:
	GameClearScene(SceneDataKeeper* keeper);
	~GameClearScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	int id;
	int targetPoint;
	int sinCount;

	int slideSize;

	std::map<int, Scene> nextScene;
	std::map<int, Vector2> textPoses;

	std::map<int, TextureID> textIDs;

	StageClearTextAnm anmer_;

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

	// �L�����A�j���[�V����
	PlayerAnimation2D mButtyAnim;
	PlayerAnimation2D mRettyAnim;
	// �I�����̍��W
	Vector2 mCursorPos;

	std::vector<TextureID> numberTexes_;

};

#endif