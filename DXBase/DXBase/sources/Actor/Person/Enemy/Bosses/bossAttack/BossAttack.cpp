#include "BossAttack.h"

BossAttack::BossAttack() :
	hp_(0),
	flinchCount_(0),
	timer_(0.0f),
	floorName_(""),
	isAttackStart_(false),
	isAttackEnd_(true),
	isGround_(false),
	isBottom_(false),
	isUseGravity_(false),
	isWspHit_(false),
	isPrevWspHit_(false),
	isBodyHit_(true),
	isAttackHit_(true),
	isMove_(true),
	position_(Vector2::Zero),
	direction_(Vector2::Zero),
	pPosition_(Vector2::Zero),
	pDirection_(Vector2::Zero),
	pNormDirection_(Vector2::Zero)
{
}

BossAttack::BossAttack(const Vector2 & position) : 
	hp_(100),
	flinchCount_(3),
	timer_(0.0f),
	angle_(0.0f),
	floorName_("a"),
	isAttackStart_(false),
	isAttackEnd_(false),
	isGround_(false),
	isUseGravity_(true),
	isWspHit_(false),
	isPrevWspHit_(false),
	isAttackHit_(false),
	isMove_(false),
	position_(position),
	direction_(Vector2::Left),
	pPosition_(Vector2::One),
	pDirection_(Vector2::One),
	pNormDirection_(Vector2::One)
{
}

BossAttack::~BossAttack()
{
}

// 更新
void BossAttack::update(float deltaTime)
{
	// 攻撃
	attack(deltaTime);
	// 時間の加算
	timer_ += deltaTime;
	floorName_ = "";
}

// 攻撃(デフォルト)
void BossAttack::attack(float deltaTime)
{
}

// 移動した位置を取得します
Vector2 BossAttack::getMovePosition()
{
	return position_;
}

// 攻撃行動のリフレッシュを行います
void BossAttack::Refresh()
{
	timer_ = 0.0f;
	isAttackStart_ = false;
	isAttackEnd_ = false;
	isUseGravity_ = true;
	//direction_ = Vector2::One;
}

// 攻撃が開始したかを返します
bool BossAttack::isAttackStart()
{
	return isAttackStart_;
}

// 攻撃が終了したかを返します
bool BossAttack::isAttackEnd()
{
	return isAttackEnd_;
}

// ボスの心臓の体力を設定します
void BossAttack::setHeartHP(const int hp)
{
	hp_ = hp;
}

// 位置を設定します
void BossAttack::setPosition(const Vector2 & position)
{
	position_ = position;
}

// プレイヤーの位置を設定します
void BossAttack::setPlayerPosition(const Vector2 & position)
{
	pPosition_ = position;
}

// プレイヤーとの方向を設定します
void BossAttack::setPlayerDirection(const Vector2 & direction)
{
	pDirection_ = direction;
}

// プレイヤーとの正規化された方向を設定します
void BossAttack::setPlayerNormalizeDirection(const Vector2 & direction)
{
	pNormDirection_ = direction;
}

// 壁捜索オブジェクトが当たったかを設定します
void BossAttack::setIsWallHit(bool isHit)
{
	isWspHit_ = isHit;
}

//void BossAttack::setDirection(const Vector2 & direction)
//{
//
//}

// 壁移動の方向を取得します
Vector2 BossAttack::getMoveDirection()
{
	return direction_;
}

// 床に触れているかを設定します
void BossAttack::setIsGround(bool isGround)
{
	isGround_ = isGround;
}

// 壁の下側に当たったかを設定します
void BossAttack::setIsBottom(bool isBottom)
{
	isBottom_ = isBottom;
}

// 触れている床の名前を設定します
void BossAttack::setFloorName(const char * name)
{
	floorName_ = name;
}

// 攻撃可能状態かを設定します
void BossAttack::setIsMove(bool isMove)
{
	isMove_ = isMove;
}

// ひるみカウントを返します
int BossAttack::getFlinchCount()
{
	return flinchCount_;
}

// 角度を返します
float BossAttack::getAngle()
{
	return angle_;
}

// 重力を使用するかを返します
bool BossAttack::isUseGravity()
{
	return isUseGravity_;
}

// プレイヤーの攻撃に当たるかを返します
bool BossAttack::isBodyHit()
{
	return isBodyHit_;
}

// プレイヤーに当たるかを返します
bool BossAttack::isAttackHit()
{
	return isAttackHit_;
}
