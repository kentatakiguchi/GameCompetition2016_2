#include "SampleBoss.h"
#include "Tornado.h"
#include "../../../Base/ActorGroup.h"

SampleBoss::SampleBoss(IWorld * world, const Vector2 & position) : 
	BaseBoss(world, position),
	tornado_(nullptr)
{
}

void SampleBoss::onUpdate(float deltaTime)
{
	// デバッグ
	auto speed = 4.0f;
	auto deltaTimer = deltaTime * 60.0f;
	// 移動
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L))
		position_.x += speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
		position_.x += -speed * deltaTimer;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
		position_.y += -speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::K))
		position_.y += speed * deltaTimer;

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::U)) {
		if (tornado_ != nullptr) {
			tornado_->dead();
			tornado_ = nullptr;
		}

		auto tornado = std::make_shared<Tornado>(
			world_, position_, Vector2(CHIPSIZE * 10, CHIPSIZE));
		world_->addActor(ActorGroup::Enemy, tornado);
		tornado_ = tornado.get();
	}

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::O) && tornado_ != nullptr) {
		tornado_->dead();
		tornado_ = nullptr;
	}
}

void SampleBoss::onDraw() const
{
	BaseBoss::onDraw();

	DrawFormatStringToHandle(50, 350, GetColor(0, 0, 0),
		handle_, "サンプルボスの座標=>X:%d Y:%d", (int)position_.x, (int)position_.y);
	auto position = Vector2::Zero;
	if (tornado_ != nullptr)
		position = tornado_->getPosition();
	DrawFormatStringToHandle(50, 400, GetColor(0, 0, 0),
		handle_, "竜巻の座標=>X:%d Y:%d", (int)position.x, (int)position.y);
	// キー
	DrawFormatStringToHandle(50, 450, GetColor(0, 0, 0),
		handle_, "IJKLキー : 移動");
	DrawFormatStringToHandle(50, 500, GetColor(0, 0, 0),
		handle_, "Uキー : 竜巻オブジェクトの生成(再生成)");
	DrawFormatStringToHandle(50, 550, GetColor(0, 0, 0),
		handle_, "Oキー : 竜巻オブジェクトの削除");
}

void SampleBoss::onCollide(Actor & actor)
{
}

void SampleBoss::onMessage(EventMessage event, void *)
{
}

// 待機状態
void SampleBoss::idel(float deltaTime)
{

}
