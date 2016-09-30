#pragma once

#include "../../Base/Actor.h"

class EnemySpawner : public Actor {
public:
	EnemySpawner(IWorld* world, const std::string& file_name);
	virtual ~EnemySpawner();
private:
	void spawn(const std::string& file_name);
};

