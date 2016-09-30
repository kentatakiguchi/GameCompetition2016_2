#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/Enemy.h"
#include "../../Actor/Person/Enemy/EnemySpawner.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include <memory>
#include <random>

const Vector3 START_POS = Vector3(2800, 25, 4500);

GamePlayScene::GamePlayScene() : 
	id(0) {
	isEnd_ = false;
}

GamePlayScene::~GamePlayScene(){

}

void GamePlayScene::start() {
	vector.x = 200;
	vector.y = 200;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	world_ = std::make_shared<World>();
	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector3(10.0f, 10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), START_POS));
	//world_->addActor(ActorGroup::Enemy_Spawner, std::make_shared<EnemySpawner>(world_.get(), "./resources/file/test.csv"));

	//for (int i = 0; i < 10; i++) {
	//	world_->addActor(ActorGroup::Enemy, std::make_shared<Enemy>(world_.get(), Vector3::Zero));
	//}

	status_ = Status(10);
}

void GamePlayScene::update() {
	world_->update(Time::GetInstance().deltaTime());

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void GamePlayScene::draw() const {
	//world描画
	world_->draw();

	DrawFormatString(550, 25, GetColor(255, 255, 255), "キャラ移動：方向キー");
	DrawFormatString(550, 50, GetColor(255, 255, 255), "カメラ回転：WASDキー");
	DrawFormatString(550, 75, GetColor(255, 255, 255), "ジャンプ：SPACEキー");
	DrawFormatString(550, 100, GetColor(255, 255, 255), "攻撃1：Zキー");
	DrawFormatString(550, 125, GetColor(255, 255, 255), "攻撃2：Xキー");

	DrawFormatString(550, 550, GetColor(255, 255, 255), "ENTERボタンでリザルトへ");
}

void GamePlayScene::end() {

}

bool GamePlayScene::isEnd() const {
	return isEnd_;
}

Scene GamePlayScene::next() const {
	return Scene::GameOver;
}

