#ifndef _GAME_PLAY_SCENE_H_
#define _GAME_PLAY_SCENE_H_

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include "../../Math/Math.h"

class World;
class BackGraundManager;
class GamePlayScene : public IScene{
public:
	GamePlayScene();
	~GamePlayScene();
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

	Status status_;

	BackGraundManager* backManager;
};

#endif