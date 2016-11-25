#include "BaseBoss.h"
#include "../../../../ResourceLoader/ResourceLoader.h"
#include "../../../Base/ActorGroup.h"
#include "../../../Body/CollisionBase.h"
#include "../../../../Define.h"
#include "BossManager.h"
#include "BossEntry.h"
#include "BossHeart.h"
#include "../FloorSearchPoint.h"
// ボスの体力表示
#include "../../../UIActor/BossGaugeUI/BossGaugeUI.h"

// ボスクラス(ベース予定)
BaseBoss::BaseBoss(IWorld * world, const Vector2 & position, const float bodyScale) :
	Actor(world, "BaseBoss", position,
		CollisionBase(const_cast<Vector2&>(position), bodyScale)),
	dp_(100),
	initDp_(dp_),
	hp_(3),
	flinchCount_(0),
	// initHp_(hp_),
	stateTimer_(0.0f),
	timer_(0.0f),
	deltaTimer_(0.0f),
	isGround_(false),
	isBottomHit_(false),
	isBodyHit_(false),
	isAttackHit_(true),
	isSceneEnd_(true),
	stateString_("待機"),
	// bossManager_(nullptr),
	playerPastPosition_(Vector2::Zero),
	player_(nullptr),
	state_(State::Idel),
	attackState_(AttackState::JumpAttack),
	fspObj_(nullptr),
	entryObj_(nullptr),
	heartObj_(nullptr),
	bossGaugeUI_(nullptr),
	bossManager_(BossManager(position)),
	top_(0.0f), bottom_(0.0f), right_(0.0f), left_(0.0f),
	handle_(CreateFontToHandle("ＭＳ 明朝", 40, 10, DX_FONTTYPE_NORMAL))
{
	// コンテナに追加(攻撃順に追加する)
	asContainer_.push_back(AttackState::JumpAttack);
	asContainer_.push_back(AttackState::WallAttack);
	asContainer_.push_back(AttackState::SpeacialAttack);
	// ボスマネージャー
	/*auto manager = std::make_shared<BossManager>(position);
	bossManager_ = &*manager;*/
	// 床捜索オブジェクト
	auto fspObj = std::make_shared<FloorSearchPoint>(
		world_, position_,
		Vector2(0.0f, bodyScale + 1.0f), 0.1f
		);
	world_->addActor(ActorGroup::Enemy, fspObj);
	fspObj_ = &*fspObj;
	// ボス入口オブジェクト
	auto entryObj = std::make_shared<BossEntry>(
		world_, position_, 
		Vector2(bodyScale / 2.0f, bodyScale / 2.0f),
		bodyScale / 2.0f);
	world_->addActor(ActorGroup::Enemy, entryObj);
	entryObj_ = &*entryObj;
	// ボス心臓オブジェクト
	auto heartHP = 100;
	auto heartObj = std::make_shared<BossHeart>(
		world_, Vector2(position_.x + 128.0f, position_.y -32.0f), heartHP, hp_);
	world_->addActor(ActorGroup::Enemy, heartObj);
	heartObj_ = &*heartObj;
	// ボスの体力ゲージ
	auto bossUI = std::make_shared<BossGaugeUI>(world_, Vector2::Zero);
	world_->addUIActor(bossUI);
	bossGaugeUI_ = bossUI.get();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp() * hp_);
}

BaseBoss::~BaseBoss()
{
}

void BaseBoss::onUpdate(float deltaTime)
{

	clampList_.clear();

	// 補間タイマ(最大値１)の更新
	setTimer(deltaTime);

	// 体力の更新
	hp_ = heartObj_->getBossHp();
	bossGaugeUI_->SetHp(heartObj_->getHeartHp());

	entryObj_->setBossPosition(position_);
	// 状態の更新
	updateState(deltaTime);
	// 接地(仮)
	bossManager_.setIsGround(isGround_);
	bossManager_.setIsBottom(isBottomHit_);

	fspObj_->setPosition(position_);
	/*entryObj_->setBossPosition(position_);*/
	// entryObj_->setDirection(direction_);
	//position_.y = MathHelper::Clamp(position_.y, -1000, 500.0f);

	// bool系
	isGround_ = false;
	isBottomHit_ = false;
}

void BaseBoss::onDraw() const
{
	// デバッグ
	auto stateChar = stateString_.c_str();
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// ボスの表示
	DrawGraph(
		vec3Pos.x - body_.GetCircle().getRadius(),
		vec3Pos.y - body_.GetCircle().getRadius(),
		ResourceLoader::GetInstance().getTextureID(TextureID::BOSS_TEX), 1);
	// 敵の表示
	/*DrawGraph(
		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);*/
	DrawFormatStringToHandle(50, 300, GetColor(255, 255, 255),
		handle_, "ブロックとの位置=>上:%d 下:%d", (int)top_, (int)bottom_);
	DrawFormatStringToHandle(50, 350, GetColor(255, 255, 255),
		handle_, "ブロックとの位置=>右:%d 左:%d", (int)right_, (int)left_);
	// 状態の表示
	DrawString(
		vec3Pos.x, vec3Pos.y - 100,
		stateChar, GetColor(255, 255, 255));
	// 体力の表示
	// 体力の表示
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 150,
		GetColor(255, 255, 255), "体力:%d", hp_);
	DrawFormatString(
		vec3Pos.x, vec3Pos.y - 175,
		GetColor(255, 255, 255), "時間:%d", (int)stateTimer_);
	body_.draw(inv_);
}

void BaseBoss::onCollide(Actor & actor)
{
	auto actorName = actor.getName();

	// ブロックの下側にぶつかったら、落ちるようにする?
	// プログラムを書いて、コメントアウトする

	// マップのブロックに当たったら、処理を行う
	if (actorName == "MovelessFloor") {
		// 位置の補間
		groundClamp(actor);
		return;
	}
	// 空中に浮かぶ床に当たったら、ひるみカウントを加算する
	if (actorName == "BossAreaFloor") {
		// 位置の補間
		if (state_ == State::Attack)
			flinchCount_++;
		groundClamp(actor);
		return;
	}
	// 特定の状態ではプレイヤーに触れても何も起こらないようにする
	if (state_ == State::Flinch || state_ == State::Dead) return;
	// プレイヤーの攻撃範囲に当たった場合の処理
	if (actorName == "Player_AttackCollider") {
		// プレイヤーの攻撃に当たらない場合は返す
		if (!isAttackHit_) return;
		// ダメージ処理
		damage(3);
		return;
	}
	// プレイヤー本体に当たった場合の処理
	if (actorName == "PlayerBody2" || actorName == "PlayerBody1") {
		// プレイヤーに当たらない場合は返す
		if (!isBodyHit_) return;
		// ダメージ処理
		damage(1);
		// もしものためのreturn
		//return;
	}
}

void BaseBoss::onMessage(EventMessage event, void *)
{
}

// シーンを終了させるかを返します
bool BaseBoss::isSceneEnd()
{
	return isSceneEnd_;
}

void BaseBoss::updateState(float deltaTime)
{
	// 現在は使用不可
	// player_ = world_->findActor("Player");
	player_ = world_->findActor("PlayerBody1");

	switch (state_)
	{
	case State::Idel: idel(deltaTime); break;
	case State::Attack: attack(deltaTime); break;
	case State::Flinch: flinch(deltaTime); break;
	case State::Dead: deadMove(deltaTime); break;
	}

	stateTimer_ += deltaTime;
	// 位置の更新
	//position_ = bossManager_->getMovePosition();
}

void BaseBoss::changeState(State state, unsigned int motion)
{
	// 同じ状態なら返す
	if (state_ == state) return;
	state_ = state;
	stateTimer_ = 0.0f;
}

void BaseBoss::changeAttackState(AttackState aState, unsigned int motion)
{
	// 攻撃状態に強制遷移する
	changeState(State::Attack, BOSS_ATTACK);
	attackState_ = aState;
	bossManager_.prevPosition();
}

void BaseBoss::idel(float deltaTime)
{
	stateString_ = "待機状態";
	// プレイヤーが取得できていれば、エネミーマネージャーに位置などを入れる
	setBMStatus();


	// デバッグ
	auto speed = 4.0f;
	auto deltaTimer = deltaTime * 60.0f;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::L))
		position_.x += speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::J))
		position_.x += -speed * deltaTimer;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::I))
		position_.y += -speed * deltaTimer;
	else if (InputMgr::GetInstance().IsKeyOn(KeyCode::K))
		position_.y += speed * deltaTimer;

	// 一定時間経過で攻撃状態に遷移
	if (stateTimer_ >= 5.0f) {
		// 残り体力で攻撃状態を変える
		// initHp - hp
		changeAttackState(
			asContainer_[asContainer_.size() - hp_], BOSS_ATTACK);
		return;
	}
	// 重力
	if (!isGround_) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}
}

void BaseBoss::attack(float deltaTime)
{
	// 攻撃状態の選択
	switch (attackState_) {
	case AttackState::JumpAttack: jumpAttack(deltaTime); break;
	case AttackState::WallAttack: wallAttack(deltaTime); break;
	case AttackState::SpeacialAttack: specialAttack(deltaTime); break;
	}

	// 攻撃が終了したら、待機状態に遷移
	//if (bossManager_->isAttackEnd()) {
	//	changeState(State::Idel, BOSS_IDLE);
	//	// ボスマネージャーの内部値をリフレッシュ
	//	bossManager_->attackRefresh();
	//}
}

void BaseBoss::flinch(float deltaTime)
{
	stateString_ = "ひるみ";
	entryObj_->setIsEntry(true);
	// 重力
	if (position_.y < FIELD_SIZE.y) {
		position_.y += 9.8f * (1.0f);// * 60.0f);
	}

	// 体内に入っていたら、ハートに入ったことを知らせる
	if (entryObj_->isEntered() && !heartObj_->isLetOut()) {
		// プレイヤーが出てきたら、待機状態にする
		stateTimer_ = 5.0f;
		heartObj_->setIsEntered(true);
	}
	// 体内に入ったら何かする
	if (entryObj_->isEntered()) {
		// プレイヤーを追い出せていないなら返す
		if (!heartObj_->isLetOut()) return;
		// プレイヤーが出てきた
		entryObj_->letOut();
	}
	// 体力が0になったら死亡
	if (hp_ <= 0) 
		changeState(State::Dead, BOSS_DEAD);
	// 一定時間経過で待機状態に遷移
	if (stateTimer_ < 5.0f) return;
	changeState(State::Idel, BOSS_IDLE);
	entryObj_->setIsEntry(false);
	dp_ = initDp_;
}

void BaseBoss::deadMove(float deltaTime)
{
	stateString_ = "死亡";
	// 死亡から一定時間経過なら、シーンを終了させる
	if (stateTimer_ >= 3.0f)
		isSceneEnd_ = true;
	//dead();
}

void BaseBoss::jumpAttack(float deltaTime)
{
	stateString_ = "ジャンプ攻撃";
	// プレイヤー本体に当たらない
	//isBodyHit_ = false;
	// ジャンプ攻撃
	bossManager_.attackMove(ATTACK_JUMPATTACK_NUMBER, deltaTime);
	position_ = bossManager_.getMovePosition();
	// ジャンプ攻撃が終わったら、待機状態にする
	if (bossManager_.isAttackEnd()) {
		changeState(State::Idel, BOSS_IDLE);
		//isBodyHit_ = true;
		bossManager_.attackRefresh();
	}
}

void BaseBoss::wallAttack(float deltaTime)
{
	/*isBodyHit_ = false;
	isAttackHit_ = false;*/
	stateString_ = "壁攻撃";
	// bossManager_.wallAttack(deltaTime);
}

void BaseBoss::specialAttack(float deltaTime)
{
	stateString_ = "スペシャルな攻撃";
	// bossManager_.specialAttack(deltaTime);
}

void BaseBoss::setTimer(float deltaTime)
{
	timer_ = deltaTime * 60.0f;
}

// ボスマネージャーのステータスの設定
void BaseBoss::setBMStatus()
{
	if (player_ != nullptr) {
		bossManager_.setPlayerPosition(player_->getPosition());
		bossManager_.setPosition(position_);
		// 方向を入れる
		auto direction = bossManager_.getPlayerDirection();
		// 戻す y = -1.0fに
		// direction.y = -1.0f;
		direction.y = 1.0f;
		entryObj_->setDirection(direction);
	}
}

// 指定した値のダメージ量を加算します
void BaseBoss::damage(const int damage)
{
	dp_ -= damage;
	// 耐久値が0になったら、ひるむ
	if (dp_ <= 0) {
		changeState(State::Flinch, BOSS_FLINCH);
		// 衝突するかどうかの bool を全てtrueにする
		isBodyHit_ = true;
		isAttackHit_ = true;
		setBMStatus();
		body_.enabled(false);
	}
}

//地面の位置に補正します
void BaseBoss::groundClamp(Actor& actor)
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

	top_ = top;
	bottom_ = bottom;
	right_ = right;
	left_ = left;
	// 過去の位置
	// Y方向に位置を補間する
	if (left < 0 &&
		right < 0) {
		// 上に補間
		if (top > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// 接地
			isGround_ = true;
			isHit = true;
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 3) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// ブロックの下側に当たった
			isBottomHit_ = true;
			isHit = true;
		}
	}
	// X方向に位置を補間する
	if (top < 0 &&
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
		if (top > -actor.getBody().GetBox().getHeight() / 2.0f + 1.0f) {
			position_.y = topLeft.y - body_.GetCircle().getRadius();
			// 接地
			isGround_ = true;
		}
		// 下に補間
		if (bottom > -actor.getBody().GetBox().getHeight() / 2.0f + 1.0f) {
			position_.y = bottomRight.y + body_.GetCircle().getRadius();
			// ブロックの下側に当たった
			isBottomHit_ = true;
		}
	}
	// X方向に位置を補間する
	if (top < 0 &&
		bottom < 0) {
		// 左に補間
		if (left > -actor.getBody().GetBox().getWidth() / 2.0f + 1.0f)
			position_.x = bottomLeft.x - body_.GetCircle().getRadius();
		// 右に補間
		if (right > -actor.getBody().GetBox().getWidth() / 2.0f + 1.0f)
			position_.x = topRight.x + body_.GetCircle().getRadius();
	}

	// 60
	// 160
	//// 左に補間
	//if (left > -14)
	//	position_.x = bottomLeft.x - body_.GetCircle().getRadius();
	//// 右に補間
	//if (right > -body_.GetCircle().getRadius())
	//	position_.x = topRight.x + body_.GetCircle().getRadius();

	/*if (top >= 0 && left <= 0 && right <= 0) {
		position_.y = t_left.y - PLAYER_RADIUS;
	}
	if (bottom >= 0 && left <= 0 && right <= 0) {
		position_.y = b_right.y + PLAYER_RADIUS;
	}
	if (right >= 0 && top <= 0 && bottom <= 0) {
		position_.x = t_right.x + PLAYER_RADIUS;
	}
	if (left >= 0 && top <= 0 && bottom <= 0) {
		position_.x = b_left.x - PLAYER_RADIUS;
	}
	if (left <= 0 && right <= 0 && top <= 0 && bottom <= 0) {
		position_ = center + (pos - center).Normalize() * (t_left - center).Length();
	}*/

	//float r2 = body_.GetCircle().getRadius() * body_.GetCircle().getRadius();
	//Vector2 topV = topRight - topLeft;
	//Vector2 v1 = position_ - topLeft;
	//float t = Vector2::Dot(topV, v1) / Vector2::Dot(topV, topV);
	//Vector2 vn =t * topV;
	//// Vector2 vn = v1 - t * v;
	////if (0 < t && t < 1 && vn.LengthSquared() <= r2) {
	////	// pc = p1 + v * t + r * Vector2.Normalize(vn); // 中心を移動
	////	position_ = topLeft + topV * t + body_.GetCircle().getRadius() *
	////		Vector2::Normalize(vn);
	////}
	//top_ = vn.Length();
}