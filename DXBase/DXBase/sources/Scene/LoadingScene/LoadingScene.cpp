#include "LoadingScene.h"
#include "../../ResourceLoader/ResourceLoader.h"

LoadingScene::LoadingScene():
isEnd_(false){
}

LoadingScene::~LoadingScene(){
	ResourceLoader::GetInstance().clearResources();
}

void LoadingScene::start(){
	isEnd_ = false;

	ResourceLoader::GetInstance().loadModel(ModelID::PLAYER, "./resources/model/player/MotusMan_v2.mv1");
	ResourceLoader::GetInstance().loadModel(ModelID::ENEMY, "./resources/model/enemy/Enemy.mv1");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/DesertFortress/sampleStage/SampleStage_DesertFortress.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/DesertFortress/sampleStage/SampleStage_DesertFortress_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/DungeonCreatorKit LITE/sampleStage/Sample_Stage_Dungeon.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/DungeonCreatorKit LITE/sampleStage/Sample_Stage_Dungeon_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/Castle/sampleStage/SampleStage_Castle.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/Castle/sampleStage/SampleStage_Castles_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/CampfirePack/sampleStage/Sample_Stage_Campfire.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/CampfirePack/sampleStage/Sample_Stage_Campfire_Collision.mqo");
	
	ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/field.mqo");
	ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/field.mqo");

	ResourceLoader::GetInstance().loadModel(ModelID::SKYDOME, "./resources/model/skydome/skydome.mqo");

}

void LoadingScene::update(){
	isEnd_ = true;
}

void LoadingScene::draw() const{
}

void LoadingScene::end(){
}

bool LoadingScene::isEnd() const{
	return isEnd_;
}

Scene LoadingScene::next() const{
	return Scene::Title;
}
