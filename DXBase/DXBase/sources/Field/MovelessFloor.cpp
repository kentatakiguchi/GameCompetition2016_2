#include "MovelessFloor.h"
#include"../Input/InputMgr.h"

MovelessFloor::MovelessFloor(IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
		Vector2{ position.x,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE ),position.y - (CHIPSIZE) }))
{
}

MovelessFloor::MovelessFloor(std::shared_ptr<MovelessFloor> chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE ),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE ),position.y - (CHIPSIZE) }
		))
{
}

MovelessFloor::MovelessFloor(MovelessFloor & chip, IWorld * world, Vector2 & position) :
	MapChip(world, Vector2(position.x, position.y), CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE ),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE ),position.y - (CHIPSIZE) }
		))
{
}

void MovelessFloor::set(Vector2 & pos)
{
	position_ = pos;
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y },
		Vector2{ pos.x + (CHIPSIZE),pos.y },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE),pos.y + (CHIPSIZE) });
}

void MovelessFloor::onUpdate(float deltaTime)
{
	position_+= InputMgr::GetInstance().AnalogPadVector()/100;
	position_ += InputMgr::GetInstance().DirectPadVector()/100;
	if (InputMgr::GetInstance().IsButtonDown(Buttons::BUTTON_A)) {
		position_ += Vector2(100,0);
	}
}

void MovelessFloor::onDraw() const
{
	body_.draw();
}

void MovelessFloor::onCollide(Actor & other)
{
}
