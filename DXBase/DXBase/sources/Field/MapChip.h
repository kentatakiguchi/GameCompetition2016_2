#pragma once
#ifndef MAPCHIP_H_
#define MAPCHIP_H_
#include"../Actor/Base/Actor.h"
#include"../Define.h"

class MapChip :public Actor{
public:
	//空のMapChipを生成
	MapChip(){}
	//マップチップの生成
	MapChip(IWorld* world, Vector2& position);
	MapChip(IWorld* world, Vector2& position, CollisionBase& base);
	MapChip(IWorld* world, Vector2& position,std::string name, CollisionBase& base);
	MapChip(std::shared_ptr<MapChip> chip, IWorld* world, Vector2& position);
	MapChip(MapChip& chip,IWorld* world,Vector2& position);
	virtual void set(Vector2& pos);
	MapChip& operator = (std::shared_ptr<MapChip> other) {
		return MapChip(other,world_, Vector2(0, 0));
	};
private:
	void onUpdate(float deltaTime);
	void onDraw() const override;
	void onCollide(Actor& other);
protected:
	int rotate_;
};

#endif // !MAPCHIP_H_