#include "NaganoScene.h"
#include "../../World/World.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
//#include "../../Actor/Person/Enemy/Enemy.h"
//#include "../../Actor/Person/Enemy/EnemySpawner.h"
#include "../../ResourceLoader/ResourceLoader.h"

#include "../../Actor/Person/Enemy/Enemys/FloorTurnEnemy.h"
#include "../../Actor/Person/Enemy/Enemys/WallTurnEnemy.h"
#include "../../Field/MapGenerator.h"
#include "../../Actor/BackGraundManager/BackGraundManager.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include <memory>
#include <random>

//static const Vector2 START_POS = Vector2(300, 400);

NaganoScene::NaganoScene() {
	isEnd_ = false;
}

NaganoScene::~NaganoScene() {
}

void NaganoScene::start() {
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	//world_->addCamera(std::make_shared<Camera>(world_.get()));
	//world_->addLight(std::make_shared<Light>(world_.get(), Vector2(10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), START_POS));
	world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector2(200, -200)));
	world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_.get(), Vector2(250, 325)));

	MapGenerator gener = MapGenerator(world_.get());
	gener.create("resources/file/test2.csv");

	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	//backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);



	spring_constant_ = 10.0f;
	attenuation_constant_ = 0.5f;
	mass_ = 0.3f;
	angular_freq_ = std::sqrtf(spring_constant_ / mass_);
	p_ = attenuation_constant_ / 2 / mass_;
	e_ = 2.7f;
	time_ = 0;

	amplitude_ = 20 * 3;

	phase_ = position_;
}

void NaganoScene::update() {
	world_->update(Time::GetInstance().deltaTime());
	//backManager->Update(Time::GetInstance().deltaTime());

	time_ += Time::GetInstance().deltaTime();

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void NaganoScene::draw() const {
	//backManager->Draw();
	//world描画
	world_->draw();



	DrawFormatString(550, 25, GetColor(255, 255, 255), "キャラ移動：WASDキー / 方向キー");
	DrawFormatString(550, 50, GetColor(255, 255, 255), "吸着：L_Shift / R_Shift");
	DrawFormatString(550, 500, GetColor(255, 255, 255), "NaganoScene");
}

void NaganoScene::end() {
}

bool NaganoScene::isEnd() const {
	return isEnd_;
}

Scene NaganoScene::next() const {
	return Scene::GameOver;
}

std::vector<Vector2> NaganoScene::getpoint()
{
	//vector
	return std::vector<Vector2>();
}

