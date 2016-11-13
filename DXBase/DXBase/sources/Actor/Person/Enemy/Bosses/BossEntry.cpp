#include "BossEntry.h"

BossEntry::BossEntry(
	IWorld * world,
	const Vector2 & position,
	const Vector2 & addPosition,
	const float bodyScale) :
	Actor(world, "BossEntry", position + addPosition,
		CollisionBase(
			const_cast<Vector2&>(position) + 
			const_cast<Vector2&>(addPosition),
			bodyScale)),
	isEntry_(false),
	isEntered_(false),
	direction_(1.0f, -1.0f),
	bossPosition_(position),
	addPosition_(addPosition)
{
}

void BossEntry::onUpdate(float deltaTime)
{
	auto addPos = Vector2(
		addPosition_.x * direction_.x,
		addPosition_.y * direction_.y);
	position_ = bossPosition_ + addPos;
}

void BossEntry::onDraw() const
{
	body_.draw(inv_);
	// 表示
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	DrawString(
		vec3Pos.x, vec3Pos.y,
		"ボスの口です", GetColor(255, 255, 255));
}

void BossEntry::onCollide(Actor & actor)
{
	// 中に入れる状態のみ当たる
	if (!isEntry_) return;
	if (actor.getName() == "PlayerBody1" || actor.getName() == "PlayerBody2") {
		// プレイヤーの位置を変更

		isEntered_ = true;
	}
}

void BossEntry::onMessage(EventMessage event, void *)
{
}

// 位置の設定をします
void BossEntry::setBossPosition(const Vector2 & position)
{
	bossPosition_ = position;
}

// 方向を設定します
void BossEntry::setDirection(const Vector2 & direction)
{
	direction_ = direction;
}

// ボスの体内に入れるかを設定します
void BossEntry::setIsEntry(bool isEntry)
{
	isEntry_ = isEntry;
}

// ボスの体内に入ったかを返します
bool BossEntry::isEntered()
{
	return isEntered_;
}

// プレイヤーがボスの体内に出たことにします
void BossEntry::letOut()
{
	isEntry_ = false;
	isEntered_ = false;
}
