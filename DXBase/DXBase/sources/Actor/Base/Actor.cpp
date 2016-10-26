#include "Actor.h"
#include <algorithm>
#include "../TestPlayer/TestPlayer.h"
#include "../../Input/KeyCode.h"
// コンストラクタ
Actor::Actor(IWorld* world, const std::string& name, const Vector3& position, const CollisionBase& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	animation_(-1),
	alpha_(0.0f),
	outPlayerFlag(false) {
	body_.setPosition({position_.x, position_.y});
}

// コンストラクタ
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f, 0.0f),
	rotation_(Matrix::Identity),
	dead_(false),
	animation_(-1) {

}


// 更新
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });
	//移動update
	ActorMove();
}

// 描画
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// 衝突判定
void Actor::collide(Actor& other) {
	if (isCollide(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
	eachChildren([&](Actor& child) { child.collide(other); });
}


// 死亡しているか？
bool Actor::isDead() const {
	return dead_;
}

// 死亡する
void Actor::dead() {
	dead_ = true;
}

// 名前を返す
const std::string& Actor::getName() const {
	return name_;
}

// 座標を返す
Vector3 Actor::getPosition() const {
	return position_;
}

// 回転行列を返す
Matrix Actor::getRotate() const {
	return rotation_;
}

// 変換行列を返す
Matrix Actor::getPose() const {
	return Matrix(rotation_).Translation(position_);
}

// 子の検索
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// 子の検索
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

// 子の衝突判定
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// 子の衝突判定
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// 子の追加
void Actor::addChild(const ActorPtr& child) {
	children_.push_front(child);
}

// 子を巡回
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を巡回 (const版）
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// 子を削除
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// 子を削除
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// 子を消去
void Actor::clearChildren() {
	children_.clear();
}

void Actor::setMotion(const unsigned int motion) {
	motion_ = motion;
}

void Actor::setTransform(Vector3 pos, Matrix rot) {
	position_ = pos;
	rotation_ = rot;
}

IWorld* Actor::getWorld() {
	return world_;
}

Animation Actor::getAnim() {
	return animation_;
}

CollisionBase Actor::getBody()
{
	return body_;
}

// メッセージ処理
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

// メッセージ処理
void Actor::onMessage(EventMessage, void*) {}

// 更新
void Actor::onUpdate(float) {}

// 描画
void Actor::onDraw() const {
	body_.draw(); // デバッグ表示
}

// 衝突した
void Actor::onCollide(Actor&) {
	body_.draw();
	//dead();
}

// 衝突判定
bool Actor::isCollide(Actor& other) {
	body_.MovePos(Vector2( position_.x,position_.y ));
	other.body_.MovePos(Vector2(other.position_.x, other.position_.y));
	return body_.intersects(other.body_);
}
//アクターを全部プレイヤーと同期させる
void Actor::ActorMove()
{
	//フラグ初期化
	moveFlag = Vector2::Zero;
	//worldを持ってなかったらリターン
	if (world_ == nullptr) return;
	//プレイヤーの座標を取得
	Vector2 player = 
		Vector2(world_->findActor("Player")->getPosition().x, world_->findActor("Player")->getPosition().y);
	//プレイヤーで一定の範囲外に行ったら今の速度と逆の速度を足してあげる
	if (getName() == "Player")
	{
		//x軸
		if (((int)player.x < 200 || 600 < (int)player.x))
		{
			position_ += Vector3(world_->MoveActor().x, 0.0f, 0.0f);
			//x軸移動してます
			moveFlag.x = 1;
		}
		//Y軸
		if ((int)player.y > 400 || (int)player.y < 100)
		{
			position_ += Vector3(0.0f, world_->MoveActor().y, 0.0f);
			//y軸移動してます
			moveFlag.y = 1;
		}
	}
	//プレイヤー以外の動き
	else
	{
		//x軸
		if ((int)player.x <= 200+ world_->MoveActor().x ||
			(int)player.x>=600+ world_->MoveActor().x)
		{
			position_ += Vector3(world_->MoveActor().x, 0.0f, 0.0f);
		}
		//Y軸
		if ((int)player.y >= 400+ world_->MoveActor().y ||
			(int)player.y <= 100+ world_->MoveActor().y)
		{
			position_ += Vector3(0.0f, world_->MoveActor().y, 0.0f);
		}
	}
}

// end of file
