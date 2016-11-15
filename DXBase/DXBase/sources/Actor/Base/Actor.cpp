#include "Actor.h"
#include <algorithm>
#include "../TestPlayer/TestPlayer.h"
#include "../../Input/KeyCode.h"
#include "../../Math/MathHelper.h"
// コンストラクタ
Actor::Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	animation_(-1),
	alpha_(0.0f),
	outPlayerFlag(false),
	resPos(Vector2::Zero),
	veloPlus(Vector2::Zero),
	velo(Vector2::Zero),
	resInv_(Matrix::Identity),
	inv_(Matrix::Identity){
	body_.setPosition({ position_.x, position_.y });
}

// コンストラクタ
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f),
	rotation_(Matrix::Identity),
	dead_(false),
	animation_(-1) {

}


// 更新
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });
	//移動update
	//ActorMove();
	body_.MovePos(Vector2(position_.x, position_.y));
}

void Actor::late_update(float deltaTime) {
	body_.MovePos(Vector2(position_.x, position_.y));
	inv();
	onLateUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.late_update(deltaTime); });
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
Vector2 Actor::getPosition() const {
	return Vector2(position_.x,position_.y);
}

// 回転行列を返す
Matrix Actor::getRotate() const {
	return rotation_;
}

// 変換行列を返す
Matrix Actor::getPose() const {
	return Matrix().Translation(Vector3(position_.x, position_.y));
	//return Matrix(rotation_).Translation(Vector3(position_.x, position_.y));
}

Matrix Actor::inv() {
	if (world_ == nullptr) return Matrix::Identity;
	auto player = world_->findActor("PlayerBody1");
	if(player == nullptr)return Matrix::Identity;
	//Vector2 spring = Spring(Vector2(300, 400),velo);
	resInv_ = Matrix::Invert(player->getPose()) * Matrix::CreateTranslation(Vector3(PLAYER_SCREEN_POSITION.x, PLAYER_SCREEN_POSITION.y));

	Vector2 resPos = Vector2(resInv_.Translation().x, resInv_.Translation().y);
	Vector2 pos = Vector2(inv_.Translation().x, inv_.Translation().y);
	Spring(pos, resPos, velo);
	inv_ = Matrix::CreateTranslation(Vector3(pos.x, pos.y));
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

void Actor::setTransform(Vector2 pos, Matrix rot) {
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

void Actor::onLateUpdate(float deltaTime)
{
}

// 描画
void Actor::onDraw() const {
	body_.draw(inv_); // デバッグ表示
}

// 衝突した
void Actor::onCollide(Actor&) {
	body_.draw(inv_);
	//dead();
}

// 衝突判定
bool Actor::isCollide(Actor& other) {
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
		Vector2(world_->findActor("PlayerBody1")->getPosition().x, world_->findActor("PlayerBody1")->getPosition().y);
	//プレイヤーで一定の範囲外に行ったら今の速度と逆の速度を足してあげる
	if (getName() != "ScroolStopPoint")
	{
		//x軸
		if ((int)player.x != 800 / 2 /*&& world_->ScroolStopFlag().x == FALSE*/)
		{
			resPos.x =- world_->MoveActor().x;
			//x軸移動してます
			moveFlag.x = 1;
		}
		//Y軸
		if ((int)player.y != 600 / 2 /*&& world_->ScroolStopFlag().y == FALSE*/)
		{
			resPos.y =- world_->MoveActor().y;
			//y軸移動してます
			moveFlag.y = 1;
		}
	}
	//ストップスクロール以外
	//if (getName() == "ScroolStopPoint")
	//{
	//	//強制的にスクロール
	//	resPos.x = world_->MoveActor().x;
	//	resPos.y = world_->MoveActor().y;
	//}
	//補間処理
	MathHelper::Spring(veloPlus.x, resPos.x, velo.x, 0.1f, 0.5f, 2.0f);
	MathHelper::Spring(veloPlus.y, resPos.y, velo.y, 0.1f, 0.5f, 2.0f);
	position_ += veloPlus;
}

void Actor::Spring(Vector2& pos ,Vector2& resPos, Vector2& velo,float stiffness, float friction, float mass)const
{
	// バネの伸び具合を計算
	Vector2 stretch = (pos- resPos);
	// バネの力を計算
	Vector2 force = -stiffness * stretch;
	// 加速度を追加
	Vector2 acceleration = force / mass;
	// 移動速度を計算
	velo= friction * (velo + acceleration);

	pos = pos + velo;
}


// end of file
