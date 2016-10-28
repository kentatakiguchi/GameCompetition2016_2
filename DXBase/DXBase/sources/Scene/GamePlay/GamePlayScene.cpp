#include "GamePlayScene.h"
#include "../../World/World.h"
#include "../../Actor/Camera/Camera.h"
#include "../../Actor/Light/Light.h"
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

static const Vector2 START_POS = Vector2(300, 400);

GamePlayScene::GamePlayScene(){
	isEnd_ = false;
}

GamePlayScene::~GamePlayScene(){
}

void GamePlayScene::start() {
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	//world_->addEventMessageListener(
	//	[=](EventMessage msg, void* param) {
	//	handleMessage(msg, param);
	//}
	//);
	//world_->addField(std::make_shared<Field>(ResourceLoader::GetInstance().getModelID(ModelID::STAGE), ResourceLoader::GetInstance().getModelID(ModelID::STAGE_COLL), ResourceLoader::GetInstance().getModelID(ModelID::SKYDOME)));
	world_->addCamera(std::make_shared<Camera>(world_.get()));
	world_->addLight(std::make_shared<Light>(world_.get(), Vector2(10.0f, 10.0f)));
	world_->addActor(ActorGroup::Player, std::make_shared<Player>(world_.get(), START_POS));
	world_->addActor(ActorGroup::Enemy, std::make_shared<FloorTurnEnemy>(world_.get(), START_POS + Vector2(200, -200)));
	world_->addActor(ActorGroup::Enemy, std::make_shared<WallTrunEnemy>(world_.get(), Vector2(250, 325)));

	MapGenerator gener = MapGenerator(world_.get());
	gener.create("test.csv");

	status_ = Status(10);

	backManager = new BackGraundManager(world_.get());
	//��ɃZ�b�g���ꂽ�e�N�X�`���قǉ��ɕ`�ʂ����
	backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
}

void GamePlayScene::update() {
	world_->update(Time::GetInstance().deltaTime());
	backManager->Update(Time::GetInstance().deltaTime());

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void GamePlayScene::draw() const {
	backManager->Draw();
	//world�`��
	world_->draw();

	DrawFormatString(550, 25, GetColor(255, 255, 255), "�L�����ړ��FWASD�L�[ / �����L�[");
	DrawFormatString(550, 50, GetColor(255, 255, 255), "�z���FL_Shift / R_Shift");

	DrawFormatString(550, 550, GetColor(255, 255, 255), "ENTER�{�^���Ń��U���g��");
}

void GamePlayScene::end() {
}

bool GamePlayScene::isEnd() const {
	return isEnd_;
}

Scene GamePlayScene::next() const {
	return Scene::GameOver;
}

