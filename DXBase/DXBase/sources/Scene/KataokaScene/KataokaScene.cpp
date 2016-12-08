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
	power = 0.0f;

	pos = Vector2(200,200);
	scale = Vector2(1,1);
	rotate = 0;
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	world_ = std::make_shared<World>();
	//puyo = new PuyoTextureK(TextureID::PUYO_TEST_TEX,pos,scale,rotate);
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

	if (InputMgr::GetInstance().IsKeyOn(KeyCode::D))
		pos.x += 100.0f*Time::GetInstance().deltaTime();
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::A))
		pos.x -= 100.0f*Time::GetInstance().deltaTime();
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::W))
		pos.y += 100.0f*Time::GetInstance().deltaTime();
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::S))
		pos.y -= 100.0f*Time::GetInstance().deltaTime();
	
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

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::T))
	{
		puyo->PuyoAddPower(Vector2::Zero, Vector2(4, -4));
	}


	//テスト用
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::H))
	{
		for (int i = 0; i <= 10; i++)
		{
			puyo->PuyoAddPowerDx(Vector2(272, i*16), Vector2(4, 0));
		}
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
	{	
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				puyo->PuyoAddPowerDx(Vector2(j*16, i * 16), Vector2(-4, -4));
			}
		}
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
	{
		for (int i = 0; i <= 17; i++)
		{
			puyo->PuyoAddPowerDx(Vector2(i * 16,0), Vector2(0, -4));
		}
	}
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::N))
	{
		//puyo->PuyoAddPowerEx(Vector2(500,500).Normalize(),10.0f);
		power += 1000.0f*Time::GetInstance().deltaTime();
	}
	Vector2 vec = InputMgr::GetInstance().AnalogPadVectorL();
	//puyo->PuyoAddPowerEx(vec.Normalize(), vec,power);
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::K))
	//{
	//	puyo->PuyoAddPower(Vector2(128, 0), Vector2(2, -2));
	//}
	//if (InputMgr::GetInstance().IsKeyDown(KeyCode::L))
	//{
	//	puyo->PuyoAddPower(Vector2(128, 0), Vector2(2, -2));
	//}

	//puyo->SetPosition(pos,scale,rotate);

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
	DrawFormatString(550, 25, GetColor(255, 255, 255), "Hキー長押し:力を加え続ける");
	DrawFormatString(550, 50, GetColor(255, 255, 255), "Jキー      :一瞬だけ力を加える");
	DrawFormatString(550, 75, GetColor(255, 255, 255), "Hキー押したままJキーを押すとバグるかも");
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
