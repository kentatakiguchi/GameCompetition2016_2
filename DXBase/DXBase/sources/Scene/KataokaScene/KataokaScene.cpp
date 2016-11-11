#include "KataokaScene.h"
#include "../../World/World.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Person/Player/Player.h"
#include "../../ResourceLoader/ResourceLoader.h"
#include "../../Actor/TestPlayer/TestPlayer.h"
#include "../../Actor/ScroolStop/ScroolStop.h"
#include "../../Actor/UIActor/BossGaugeUI/BossGaugeUI.h"
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
	pos = Vector2::Zero;
	scale = Vector2(1,1);
	rotate = 0;
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	puyo = new PuyoTextureK(TextureID::PUYO_TEST_TEX,pos,scale,rotate);
	world_->addUIActor(std::make_shared<BossGaugeUI>(world_.get(), Vector2(500, 500)));
	//backManager = new BackGraundManager(world_.get());
	////先にセットされたテクスチャほど奥に描写される
	//backManager->SetBackGraund(TextureID::BACKGRAUND4_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND3_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND2_TEX);
	//backManager->SetBackGraund(TextureID::BACKGRAUND1_TEX);

	//backManager->SetUpBackGraund(TextureID::BACKGRAUND_TOP_TEX);
	//backManager->SetDownBackGraund(TextureID::BACKGRAUND_BOT_TEX);
}

void KataokaScene::update()
{
	puyo->PuyoUpdate();

	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::D))
	//	pos.x += 100.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::A))
	//	pos.x -= 100.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::W))
	//	pos.y += 100.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::S))
	//	pos.y -= 100.0f*Time::GetInstance().deltaTime();
	//
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::UP))
	//	scale.y += 10.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::DOWN))
	//	scale.y -= 10.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::LEFT))
	//	scale.x += 10.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::RIGHT))
	//	scale.x -= 10.0f*Time::GetInstance().deltaTime();

	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::G))
	//	rotate += 100.0f*Time::GetInstance().deltaTime();
	//if (InputMgr::GetInstance().IsKeyOn(KeyCode::F))
	//	rotate -= 100.0f*Time::GetInstance().deltaTime();

	////テスト用
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::H))
	//{
	//	puyo->PuyoAddPower(Vector2(0,128), Vector2(2, -2));
	//}
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::J))
	//{
	//	puyo->PuyoAddPower(Vector2(128, 128), Vector2(2, -2));
	//}
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::K))
	//{
	//	puyo->PuyoAddPower(Vector2(128, 0), Vector2(2, -2));
	//}
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::L))
	//{
	//	puyo->PuyoAddPower(Vector2(128, 0), Vector2(2, -2));
	//}

	puyo->SetPosition(pos,scale,rotate);

	world_->update(Time::GetInstance().deltaTime());
	////背景update
	//backManager->Update(Time::GetInstance().deltaTime());
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::RETURN)) isEnd_ = true;
}

void KataokaScene::draw() const
{
	puyo->PuyoDraw();
	////背景draw
	//backManager->Draw();
	world_->draw();
}

void KataokaScene::end()
{
	//delete backManager;
	delete puyo;
}

bool KataokaScene::isEnd() const
{
	return isEnd_;
}

Scene KataokaScene::next() const
{
	return Scene::Title;
}
