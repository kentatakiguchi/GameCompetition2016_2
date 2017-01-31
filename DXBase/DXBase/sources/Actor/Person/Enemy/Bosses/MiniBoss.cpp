#include "MiniBoss.h"
#include "../../../Base/ActorGroup.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../FloorSearchPoint.h"

MiniBoss::MiniBoss(
	IWorld * world, 
	const Vector2 & position, 
	const float scale) : 
	Actor(world, "MiniRunBoss", position,
		CollisionBase(const_cast<Vector2&>(position), 64.0f * scale)),
	scale_(scale),
	direction_(Vector2::One * -1),
	animation_(EnemyAnimation2D()),
	fspObj_(nullptr)
{
	// 方向を変える
	auto size = (int)(scale * 100);
	if (size % 2 == 1) direction_.x = 1;
	// アニメーションの追加
	int animID = 0;
	animation_.addAnimation(animID,
		ResourceLoader::GetInstance().getAnimationIDs(
			AnimationID::BOSS_WALLATTACK_DASH_TEX));
	animation_.changeAnimation(animID);
	animation_.changeDirType(direction_.x);
	// 床捜索オブジェクト
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(body_.GetCircle().getRadius(), body_.GetCircle().getRadius()), 
		10.0f);
	world_->addActor(ActorGroup::EnemyBullet, fspObj);
	fspObj_ = fspObj.get();
	fspObj_->setDirection(direction_);
}

void MiniBoss::onUpdate(float deltaTime)
{
	animation_.update(deltaTime);

	auto speed = 6.0f;
	position_.y += 9.8f * (deltaTime * 60.0f);
	position_.x += direction_.x * speed * (deltaTime * 60.0f);
	fspObj_->setPosition(position_);
	// 方向を変える
	if (fspObj_->isGround()) {
		direction_.x *= -1;
		animation_.changeDirType(direction_.x);
	}
	fspObj_->setDirection(direction_);
}

void MiniBoss::onDraw() const
{
	auto size = 256;
	animation_.draw(
		position_, 
		Vector2(size / 2, size / 1.5f),
		scale_);
}

void MiniBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();
	//床関連のオブジェクトに当たっているなら
	auto getFloorName = strstr(actorName.c_str(), "Floor");
	// マップのブロックに当たったら、処理を行う
	if (getFloorName != NULL || actorName == "Door") {
		// 位置の補間
		groundClamp(actor);
		return;
	}
}

void MiniBoss::onMessage(EventMessage event, void *)
{
}

//地面の位置に補正します
void MiniBoss::groundClamp(Actor& actor)
{
	if (actor.body_.GetBox().getWidth() == 0) return;
	// 新円と正方形の衝突判定
	// 自分自身の1f前の中心位置を取得
	auto isHit = false;
	auto pos = body_.GetCircle().previousPosition_;
	// 相手側の四角形の4点を取得
	auto topLeft = actor.getBody().GetBox().component_.point[0];
	auto topRight = actor.getBody().GetBox().component_.point[1];
	auto bottomLeft = actor.getBody().GetBox().component_.point[2];
	auto bottomRight = actor.getBody().GetBox().component_.point[3];
	// 外積を使って、縦の長さを計算する
	auto top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	auto bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	auto right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	auto left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));
	// 過去の位置
	// Y方向に位置を補間する
	if (left < 0 &&
		right < 0) {
		// 上に補間
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
		}
	}
	// X方向に位置を補間する
	else if (top < 0 &&
		bottom < 0) {
		// 左に補間
		if (left > 0) {
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
			isHit = true;
		}
		// 右に補間
		if (right > 0) {
			position_.x = topRight.x + body_.GetCircle().getRadius();
			isHit = true;
		}
	}

	if (isHit) return;

	// 現在の判定
	pos = position_;
	// 外積を使って、縦の長さを計算する
	top = Vector2::Cross(
		(topLeft - topRight).Normalize(), (pos - topRight));
	bottom = Vector2::Cross(
		(bottomRight - bottomLeft).Normalize(), (pos - bottomLeft));
	right = Vector2::Cross(
		(topRight - bottomRight).Normalize(), (pos - bottomRight));
	left = Vector2::Cross(
		(bottomLeft - topLeft).Normalize(), (pos - topLeft));
	// Y方向に位置を補間する
	if (left < 0 &&
		right < 0) {
		// 上に補間
		if (top > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
		}
	}
	// X方向に位置を補間する
	if (top < 0 &&
		bottom < 0) {
		// 左に補間
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// 右に補間
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}
}
