#include "KataokaScene.h"
#include "../../World/World.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include "../../Actor/TestObject/TestObject.h"
#include <memory>
#include <random>
KataokaScene::KataokaScene()
{
	isEnd_ = false;
}

KataokaScene::~KataokaScene()
{
}

void KataokaScene::start()
{
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	world_->addActor(ActorGroup::Player, std::make_shared<TestPlayer>(world_.get(), Vector3::Zero));
	world_->addActor(ActorGroup::Enemy, std::make_shared<TestObject>(world_.get(), Vector3::Zero));
	backManager = new BackGraundManager(world_.get());
	//先にセットされたテクスチャほど奥に描写される
	backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);

}

void KataokaScene::update()
{
	world_->update(Time::GetInstance().deltaTime());
	//背景update
	backManager->Update(Time::GetInstance().deltaTime());
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void KataokaScene::draw() const
{
	//背景draw
	backManager->Draw();
	world_->draw();
}

void KataokaScene::end()
{
	delete backManager;
}

bool KataokaScene::isEnd() const
{
	return isEnd_;
}

Scene KataokaScene::next() const
{
	return Scene::Title;
}
