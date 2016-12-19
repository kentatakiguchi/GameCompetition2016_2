#include "DeadEnemy.h"
#include "../../../Define.h"

DeadEnemy::DeadEnemy(
	IWorld * world,
	const Vector2 & position,
	const float bodyScale) : 
	Actor(world_, "DeadEnemy", position, 
		std::make_shared<BoundingBox>(Vector2::One * bodyScale / -2.0f, Matrix::Identity, bodyScale, bodyScale, true)),

	timer_(0.0f),
	isGround_(false),
	animation_(EnemyAnimation2D())
{

}

void DeadEnemy::onUpdate(float deltaTime)
{
	// 重力
	if (isGround_) {
		timer_ += deltaTime;
		position_.y += timer_ * 9.8f * (deltaTime * 60.0f);
	}

	//timer_ += deltaTime;

	isGround_ = false;
}

void DeadEnemy::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	// プレイヤー関連のオブジェクトに当たっているなら
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// マップのブロックに当たったら、処理を行う
	if (getFloorName != NULL) {
		groundClamp(actor);
	}
}

void DeadEnemy::onMessage(EventMessage event, void *)
{
}

// 地面の位置に補正します
void DeadEnemy::groundClamp(Actor & actor)
{
	if (actor.body_->width() == 0) return;
	// 正方形同士の計算
	// 自分自身の1f前の中心位置を取得
	auto pos = body_->pre_pos();
	// 相手側の四角形の4点を取得
	auto topLeft = actor.getBody()->points()[0];
	auto topRight = actor.getBody()->points()[1];
	auto bottomLeft = actor.getBody()->points()[2];
	auto bottomRight = actor.getBody()->points()[3];
	// 外積を使って、縦の長さを計算する
	auto top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	auto bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	auto right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	auto left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));

	// Y方向に位置を補間する
	if (left < body_->width() / 2.0f &&
		right < body_->width() / 2.0f) {
		// 上に補間
		if (top > 0) {
			position_.y = topLeft.y - body_->height() / 2.0f;
			// 接地
			isGround_ = true;
			timer_ = 0.0f;
		}
		// 下に補間
		if (bottom > 0)
			position_.y = bottomRight.y + body_->height() / 2.0f;
	}
	// X方向に位置を補間する
	if (top < body_->height() / 2.0f &&
		bottom < body_->height() / 2.0f) {
		// 左に補間
		if (left > 0)
			position_.x = bottomLeft.x - body_->width() / 2.0f;
		// 右に補間
		if (right > 0)
			position_.x = topRight.x + body_->width() / 2.0f;
	}
}

