#include "KataokaScene.h"
#include "../../World/World.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include "../../Actor/TestObject/TestObject.h"
#include "../../Actor/ScroolStop/ScroolStop.h"
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
	// ï`âÊêÊâÊñ Çó†âÊñ Ç…ÉZÉbÉg
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	world_->addActor(ActorGroup::Player, std::make_shared<TestPlayer>(world_.get(), Vector3(800/2,600/2)));
	world_->addActor(ActorGroup::Enemy, std::make_shared<TestObject>(world_.get(), Vector3::Zero));

	world_->addActor(ActorGroup::SCROOLSTOP, std::make_shared<ScroolStop>
		(world_.get(), Vector2(1600, 0), ScroolStop::StopDirection::RIGHT));
	world_->addActor(ActorGroup::SCROOLSTOP, std::make_shared<ScroolStop>
		(world_.get(), Vector2(0,0),ScroolStop::StopDirection::LEFT));
	world_->addActor(ActorGroup::SCROOLSTOP, std::make_shared<ScroolStop>
		(world_.get(), Vector2(0, 0), ScroolStop::StopDirection::TOP));
	world_->addActor(ActorGroup::SCROOLSTOP, std::make_shared<ScroolStop>
		(world_.get(), Vector2(0, 1200), ScroolStop::StopDirection::BOT));

	backManager = new BackGraundManager(world_.get());
	//êÊÇ…ÉZÉbÉgÇ≥ÇÍÇΩÉeÉNÉXÉ`ÉÉÇŸÇ«âúÇ…ï`é Ç≥ÇÍÇÈ
	backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
}

void KataokaScene::update()
{
	world_->update(Time::GetInstance().deltaTime());
	//îwåiupdate
	backManager->Update(Time::GetInstance().deltaTime());
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void KataokaScene::draw() const
{
	//îwåidraw
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
