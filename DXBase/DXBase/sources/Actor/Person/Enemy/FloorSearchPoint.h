#ifndef FLOOR_SEARCH_POINT_H_
#define FLOOR_SEARCH_POINT_H_

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"

class FloorSearchPoint : public Actor {
public:
	FloorSearchPoint(IWorld* world,const Vector3& pointPosition , const Vector3&  collidePosition);
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;
	// ˆÊ’u‚Ìİ’è
	void setPosition(Vector3 position);
	// •ûŒü‚Ìİ’è(X)
	void setDirectionX(int direction);
	// •ûŒü‚Ìİ’è(Y)
	void setDirectionY(int direction);
	// “G‚Ì‘å‚«‚³‚ğ“ü‚ê‚Ü‚·
	void setEnemyScale(const Vector2 scale);
	// °‚Æ“–‚½‚Á‚½‚©‚ğ•Ô‚µ‚Ü‚·
	bool isFloor();
	bool isGround();

private:
	int turnCount_;			// U‚èŒü‚«‰ñ”
	bool isFloor_;
	bool isGround_;
	Vector2 direction_;			// •ûŒü
	Vector2 enemyScale_;	// “G‚Ì‘å‚«‚³
	Vector3 pointPosition_;
};

#endif