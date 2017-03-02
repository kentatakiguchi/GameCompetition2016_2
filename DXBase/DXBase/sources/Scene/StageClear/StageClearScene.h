#ifndef STAGE_CLEAR_SCENE_H_
#define STAGE_CLEAR_SCENE_H_

#include "../Base/IScene.h"
#include<map>
#include"../../ResourceLoader/ResourceLoader.h"
#include"StageClearTextAnm.h"
#include "../../Animation/Player/PlayerAnimation2D.h"
#include "SceneChangeBossAnm.h"
#include"../../World/World.h"
#include"../../Actor/Person/Player/PlayerPtr.h"

class BackGraundManager;

class StageClearScene : public IScene {
public:
	StageClearScene(SceneDataKeeper* keeper);
	~StageClearScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	using WorldPtr = std::shared_ptr<World>;
	// ���[���h(�v���C���[�Ǘ��p)
	WorldPtr	world_;
	//���̃V�[��
	Scene nextScene;
	//�o�ߎ���
	float mIvemtTime;
	//�{�X�̃A�j���[�V����
	SceneChangeBossAnm anmer_;
	//�{�X�̕`��ʒu
	Vector2 bossPosition;
	Vector2 BoardPosition;

	BackGraundManager* backManager;

	std::vector<TextureID> BoardTexes;
	std::vector<TextureID> BlockTexes;

	int backNum_;
	int boardNum_;
	int blockNum_;
	
	int floorPosition_;

	typedef std::vector<TextureID> BackTitles;
	std::vector<BackTitles> titleTexs;

	float speedx;
	float speedy;

	float stopx;

	float bossRotate;

	bool isArrive_;
	bool isFirstIdle;
	bool isFirstJump;
	PlayerPtr player_;
};

#endif