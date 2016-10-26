#include "YajimaScene.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../Actor/Person/Enemy/Enemys/WeakEnemy.h"
#include "../../Actor/Person/Enemy/Enemys/FloorTurnEnemy.h"
#include "../../Actor/Person/Enemy/Enemys/PendulumEnemy.h"
#include "../../Actor/Person/Enemy/EnemySpawner.h"
#include "../../ResourceLoader/ResourceLoader.h"

const Vector3 START_POS = Vector3(300, 125, 0);

YajimaScene::YajimaScene() : 
	id(0)
{
	isEnd_ = false;
}

YajimaScene::~YajimaScene()
{
}

void YajimaScene::start()
{
	isEnd_ = false;

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	// グラフィックのロード
	id = LoadGraph("./resources/Player.png");

	world_ = std::make_shared<World>();
	world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector3(10.0f, 10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), START_POS + Vector3(15, 5, 0)));
	world_->addActor(ActorGroup::Enemy, std::make_shared<WeakEnemy>(world_.get(), START_POS + Vector3(15 + 50, 5, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector3(15, 5, 0)));
	//world_->addActor(ActorGroup::Enemy, std::make_shared<PendulumEnemy>(world_.get(), START_POS + Vector3(15, 5, 0)));
}

void YajimaScene::update()
{
	world_->update(Time::GetInstance().deltaTime());
}

void YajimaScene::draw() const
{
	world_->draw();
}

void YajimaScene::end()
{
}

bool YajimaScene::isEnd() const
{
	return isEnd_;
}

Scene YajimaScene::next() const
{
	return Scene::Title;
}
