#ifndef WALL_MOVE_ENEMY_H_
#define WALL_MOVE_ENEMY_H_

#include "../BaseEnemy.h"
#include <vector> // デバッグ

class WallMoveEnemy : public BaseEnemy {
public:
	WallMoveEnemy(IWorld * world, const Vector2& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;
private:
	// 索敵移動です
	void search();
	// 索敵時の行動です
	void searchMove();
	// 壁捜索オブジェクトの位置を追加
	void addWSPPosition();
	// 壁捜索オブジェクトの大きさを追加
	void addWSPScale();

private:
	Vector2 addScale_;

	typedef std::vector<bool> IsGroundContainer;
	IsGroundContainer isGCont;
};

#endif
