#include "MapChip.h"

MapChip::MapChip(IWorld * world, Vector2 & position):
	Actor(world, "MapChip", Vector3(position.x, position.y, 0), CollisionBase(
		Vector2{ position.x,position.y },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }))
{

}

MapChip::MapChip(std::shared_ptr<MapChip> chip,IWorld* world, Vector2 & position)
	:Actor(world, "MapChip", Vector3(position.x, position.y, 0), CollisionBase(
		Vector2{ position.x ,position.y },
		Vector2{ position.x - (CHIPSIZE ),position.y  },
		Vector2{ position.x ,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		))
{

}

MapChip::MapChip(MapChip& chip,IWorld* world, Vector2 & position)
	:Actor(world, "MapChip", Vector3(position.x, position.y, 0), CollisionBase(
		Vector2{ position.x ,position.y  },
		Vector2{ position.x - (CHIPSIZE),position.y },
		Vector2{ position.x,position.y - (CHIPSIZE) },
		Vector2{ position.x - (CHIPSIZE),position.y - (CHIPSIZE) }
		))
{
}

void MapChip::set(Vector2& pos)
{
	body_ = CollisionBase(
		Vector2{ pos.x ,pos.y  },
		Vector2{ pos.x + (CHIPSIZE),pos.y  },
		Vector2{ pos.x ,pos.y + (CHIPSIZE) },
		Vector2{ pos.x + (CHIPSIZE ),pos.y + (CHIPSIZE) });
}

void MapChip::onUpdate(float deltaTime)
{
}

void MapChip::onDraw() const
{
	body_.draw();
}

void MapChip::onCollide(Actor & other)
{
}
