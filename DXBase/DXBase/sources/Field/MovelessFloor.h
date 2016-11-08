#pragma once
#ifndef MOVELESS_FLOOR_H_
#define MOVELESS_FLOOR_H_
#include"../Actor/Base/Actor.h"
#include"MapChip.h"
#include"../Define.h"

class MovelessFloor :public MapChip {
public:
	//���MapChip�𐶐�
	MovelessFloor() {}
	//�}�b�v�`�b�v�̐���
	MovelessFloor(IWorld* world, Vector2& position);
	MovelessFloor(std::shared_ptr<MovelessFloor> chip, IWorld* world, Vector2& position);
	MovelessFloor(MovelessFloor& chip, IWorld* world, Vector2& position);
	void set(Vector2& pos);
	MovelessFloor& operator = (std::shared_ptr<MovelessFloor> other) {
		return MovelessFloor(other, world_, Vector2(0, 0));
	};
private:
	void onUpdate(float deltaTime);
	void onDraw() const override;
	void onCollide(Actor& other);
};

#endif // !MAPCHIP_H_