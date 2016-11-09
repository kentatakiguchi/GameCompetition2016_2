#include "LoadingScene.h"
#include "../../ResourceLoader/ResourceLoader.h"

#include "../../Define.h"

LoadingScene::LoadingScene():
isEnd_(false){
}

LoadingScene::~LoadingScene(){
	ResourceLoader::GetInstance().clearResources();
}

void LoadingScene::start(){
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");

	isEnd_ = false;

	//ResourceLoader::GetInstance().loadModel(ModelID::PLAYER, "./resources/model/player/MotusMan_v2.mv1");
	//ResourceLoader::GetInstance().loadModel(ModelID::ENEMY, "./resources/model/enemy/Enemy.mv1");
	//
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/DesertFortress/sampleStage/SampleStage_DesertFortress.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/DesertFortress/sampleStage/SampleStage_DesertFortress_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/DungeonCreatorKit LITE/sampleStage/Sample_Stage_Dungeon.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/DungeonCreatorKit LITE/sampleStage/Sample_Stage_Dungeon_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/Castle/sampleStage/SampleStage_Castle.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/Castle/sampleStage/SampleStage_Castles_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/CampfirePack/sampleStage/Sample_Stage_Campfire.mqo");
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/CampfirePack/sampleStage/Sample_Stage_Campfire_Collision.mqo");
	
	//ResourceLoader::GetInstance().loadModel(ModelID::STAGE, "./resources/model/stage/field.mqo");
	ResourceLoader::GetInstance().loadModel(ModelID::STAGE_COLL, "./resources/model/stage/field.mqo");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND1_TEX, "./resources/sprite/BackGraund1.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND2_TEX, "./resources/sprite/BackGraund2.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND3_TEX, "./resources/sprite/BackGraund3.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND4_TEX, "./resources/sprite/BackGraund4.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_BOT_TEX, "./resources/sprite/BackGraundBot.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::BACKGRAUND_TOP_TEX, "./resources/sprite/BackGraundTop.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::ENEMY_SAMPLE_TEX, "./resources/sprite/EnemySample.png");
	ResourceLoader::GetInstance().loadTexture(TextureID::PUYO_TEST_TEX, "./resources/sprite/Test2.png");
	//ResourceLoader::GetInstance().loadModel(ModelID::SKYDOME, "./resources/model/skydome/skydome.mqo");

}

void LoadingScene::update(){
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");

	isEnd_ = true;
}

void LoadingScene::draw() const{
	DrawFormatString(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2, GetColor(255, 255, 255), "NowLoading");
}

void LoadingScene::end(){
}

bool LoadingScene::isEnd() const{
	return isEnd_;
}

Scene LoadingScene::next() const{
	return Scene::Title;
}
