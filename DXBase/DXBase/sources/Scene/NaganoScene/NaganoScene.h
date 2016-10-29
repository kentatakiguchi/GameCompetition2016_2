#pragma once

#include "../Base/IScene.h"
#include "../../Actor/Person/Player/Status/Status.h"
#include <memory>
#include <vector>
#include "../../Math/Math.h"


class World;
class BackGraundManager;
class NaganoScene : public IScene {
public:
	NaganoScene();
	~NaganoScene();
	virtual void start() override;
	virtual void update() override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool isEnd() const override;
	virtual Scene next() const override;
	std::vector<Vector2> getpoint();
private:
	using WorldPtr = std::shared_ptr<World>;
	// ƒ[ƒ‹ƒh
	WorldPtr	world_;

	Status status_;

	BackGraundManager* backManager;

	float time_;
};



