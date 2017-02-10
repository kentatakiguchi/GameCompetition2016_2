#ifndef BOSS_STAGE_H_
#define BOSS_STAGE_H_

#include "../Base/IScene.h"
#include <memory>
#include "../../Math/Math.h"
#include"../GamePlay/PauseScreen.h"
#include"../GamePlay/MoveScreen.h"
#include "../../Animation/Base/Animation2D.h"
#include "../../Actor/Door/Door.h"
#include "../../Animation/Base/Animation2D.h"
#include"../../Actor/Item/ItemAnm.h"
#include <list>

class World;
class BackGraundManager;
class BaseBoss;
class StarEffect;

class BossStage : public IScene {
public:
	BossStage(SceneDataKeeper* keeper);
	~BossStage();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
	// ���̈ʒu�̐ݒ�
	void setStartPosition(const Vector2& position);
	// ���̐���
	void createStars();
	// ���̍X�V
	void updateStars();

private:
	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;

	BackGraundManager* backManager;
	BaseBoss* boss_;				// �{�X
	Door* door_;

	Scene nextScene_;

	float deltaTime_;

	bool isStopped_;

	float mIvemtTime;

	PauseScreen pause_;
	MoveScreen move_;

	ActorPtr player;

	Animation2D hatenaAnm_;
	// ���֘A
	int starCount_;
	bool isCreateStar_;
	bool isIdelEnd_;
	std::vector<Vector2> startPositiones_;
	typedef std::list<StarEffect*> StarContainer;
	StarContainer stars_;

	ItemAnm anmer_;
	std::vector<float> rotateRange_;

	int maxStarCount_;
	int myStarCount_;
};

#endif
