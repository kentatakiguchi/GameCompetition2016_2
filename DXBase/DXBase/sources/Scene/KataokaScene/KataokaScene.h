#ifndef _KATAOKA_SCENE_H_
#define _KATAOKA_SCENE_H_

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include "../../Actor/BackGraundManager/BackGraundManager.h"
class World;

class KataokaScene : public IScene {
public:
	KataokaScene();
	~KataokaScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
private:
	VECTOR vector;

	using WorldPtr = std::shared_ptr<World>;
	// ���[���h
	WorldPtr	world_;

	int id;

	Status status_;

	BackGraundManager* backManager;
};

#endif