#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(IWorld* world, const Vector3&  position);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// ˆÊ’u‚Ìİ’è
	void setPosition(Vector3 position);
	// •ûŒü‚Ìİ’è
	void setDirection(int direction);
	// “G‚Ì‘å‚«‚³‚ğ“ü‚ê‚Ü‚·
	void setEnemyScale(const Vector2 scale);
	// °‚Æ“–‚½‚Á‚½‚©‚ğ•Ô‚µ‚Ü‚·
	bool isFloor();

private:
	int direction_;			// •ûŒü
	int turnCount_;			// U‚èŒü‚«‰ñ”
	bool isFloor_;
	Vector2 enemyScale_;	// “G‚Ì‘å‚«‚³
	Vector2 vec2Position_;
};

#endif