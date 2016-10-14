#ifndef _YAJIMA_SCENE_H_
#define _YAJIMA_SCENE_H_

#include "../Base/IScene.h"
#include <memory>

class World;

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
	// ÉèÅ[ÉãÉh
	WorldPtr	world_;

	int id;
};

#endif