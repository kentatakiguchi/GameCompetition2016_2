#pragma once

#include "../Base/IScene.h"
#include <memory>
class World;
class BackGraundManager;
class BonusStage : public IScene {
public:
	BonusStage(SceneDataKeeper* keeper);
	~BonusStage();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;

	BackGraundManager* backManager;
	Scene nextScene_;
	Vector2 creditSize_;
	Vector2 creditPos_;

	Vector2 kiriTexSize_;
	int point_;
	int bonusPoint_;

	float pointTime_;

	float resultAlpha_;

	bool isResult_;
};

