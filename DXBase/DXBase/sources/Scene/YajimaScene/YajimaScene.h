#ifndef _YAJIMA_SCENE_H_
#define _YAJIMA_SCENE_H_

#include "../Base/IScene.h"
#include <memory>

class World;

class BaseBoss;

class YajimaScene : public IScene {
public:
	YajimaScene();
	~YajimaScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;

private:
	using WorldPtr = std::shared_ptr<World>;
	WorldPtr	world_;	// ワールド

	int id;

	BaseBoss* boss_;	// ボス
};

#endif