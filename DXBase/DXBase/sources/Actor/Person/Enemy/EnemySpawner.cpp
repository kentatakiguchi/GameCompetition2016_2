#include "EnemySpawner.h"

#include "Enemy.h"
#include "../../../World/IWorld.h"
#include "../../Base/ActorGroup.h"
#include"../../Body/CollisionBase.h"
#include "../../../FileReader/CsvReader.h"

EnemySpawner::EnemySpawner(IWorld * world, const std::string& file_name) :
	Actor(world, "EnemySpawner", Vector3::Zero, CollisionBase()) {
	spawn(file_name);
}

EnemySpawner::~EnemySpawner(){
}

void EnemySpawner::spawn(const std::string& file_name){
	CsvReader csv(file_name);
	for (int r = 0; r < csv.rows(); ++r) {
		std::string name = csv.get(r, 0);
		std::string x_s = csv.get(r, 1);
		std::string y_s = csv.get(r, 2);
		std::string z_s = csv.get(r, 3);
		float x = std::stof(x_s);
		float y = std::stof(y_s);
		float z = std::stof(z_s);
		//float x = csv.getf(r, 1);
		//float y = csv.getf(r, 2);
		//float z = csv.getf(r, 3);
		Vector3 pos = Vector3(x, y, z);
		world_->addActor(ActorGroup::Enemy, std::make_shared<Enemy>(world_, pos));
	}
}
