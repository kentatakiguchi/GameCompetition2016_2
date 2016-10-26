#pragma once
#ifndef MAPCHIP_H_
#define MAPCHIP_H_
#include"../Actor/Base/Actor.h"

#define CHIPSIZE 32

class MapChip :public Actor{
public:
	//���MapChip�𐶐�
	MapChip(){}
	//�}�b�v�`�b�v�̐���
	MapChip(IWorld* world, Vector2& position);
	MapChip(std::shared_ptr<MapChip> chip, Vector2& position);
	MapChip(MapChip& chip,Vector2& position);
	void set(Vector2& pos);
	MapChip& operator = (std::shared_ptr<MapChip> other) {
		return MapChip(other, Vector2(0, 0));
	};

private:
	virtual void onUpdate(float deltaTime);
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other);
};

#endif // !MAPCHIP_H_


