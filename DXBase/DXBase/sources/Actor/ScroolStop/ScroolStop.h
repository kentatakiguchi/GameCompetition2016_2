#pragma once
#ifndef SCROOL_STOP_H_
#define SCROOL_STOP_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"




// ƒvƒŒ[ƒ„[
class ScroolStop : public Actor {
public:
	enum StopDirection {
		RIGHT,
		LEFT,
		TOP,
		BOT
	};

public:
	ScroolStop(IWorld* world, const Vector2& position,StopDirection dire);
	~ScroolStop();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;

public:
	Vector2 GetSceneInFlag() {
		return sceneInFlag;
	}
private:
	//‰æ–Ê“à‚É“ü‚Á‚Ä‚¢‚é‚©x²
	Vector2 sceneInFlag;
	//‚Ç‚Ì•ûŒü‚Å~‚ß‚é‚©
	StopDirection mDire;
};

#endif
