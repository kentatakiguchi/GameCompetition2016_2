#include "WallMoveEnemy.h"
#include "../FloorSearchPoint.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

WallMoveEnemy::WallMoveEnemy(
	IWorld * world,
	const Vector2 & position,
	const Vector2& direction) :
	BaseEnemy(world, position, 64.0f, direction),
	addScale_(4.0f, 4.0f)
	//result_(0)
{
	direction_ = direction;
	// 壁捜索オブジェクトの各ステータスの追加
	addWSPPosition();
	addWSPScale();
	// 壁捜索オブジェクトの追加
	createFSP();
	// 重力を使わない かつ 無敵
	isUseGravity_ = false;
	isInvincible_ = true;

	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		isGCont.push_back(enemyManager_.getWSPObj(i)->isGround());
	}
}

void WallMoveEnemy::onUpdate(float deltaTime)
{
	// デルタタイムの値を設定する
	setDeltaTime(deltaTime);
	// エネミーマネージャーの更新
	enemyManager_.update(deltaTime);
	// 状態の更新
	BaseEnemy::updateState(deltaTime);
	// 壁捜索オブジェクトの位置更新
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		enemyManager_.getWSPObj(i)->setPosition(position_);
		// 壁に当たっているかのコンテナに追加
		isGCont[i] = enemyManager_.getWSPObj(i)->isGround();
	}
	//// デバッグ表示のためのリザルト
	//result_ = enemyManager_.eachWSPObj();
}

void WallMoveEnemy::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// 敵の表示
	DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	//// デバッグ
	/*auto addPos = Vector2::Zero;
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		addPos.y += 50.0f;
		DrawFormatStringToHandle(50, 50 + addPos.y, GetColor(255, 255, 255),
			handle_, "ボックスと触れているか(%d):%d",
			i, isGCont[i]);
	}*/
	//DrawFormatString(
	//	25, 350, GetColor(255, 255, 255),
	//	"ボックスと触れているかの合計値:%d",
	//	result_);
	//DrawFormatString(
	//	25, 375, GetColor(255, 255, 255),
	//	"ボックスに一瞬触れたか:%d",
	//	(int)isBlockCollideBegin_);
	//DrawFormatString(
	//	25, 400, GetColor(255, 255, 255),
	//	"ボックスに触れているか:%d",
	//	(int)isBlockCollideEnter_);

	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "プレイヤーとの距離:%d", (int)distance_);*/

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw(inv_);
}

void WallMoveEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
	// 壁移動の方向を設定
	enemyManager_.setIsDirection(isBlockCollideBegin_);
}

void WallMoveEnemy::onMessage(EventMessage event, void *)
{
}

void WallMoveEnemy::search()
{
	// 状態遷移しない
	searchMove();
}

void WallMoveEnemy::searchMove()
{
	// 方向を入れる
	direction_ = enemyManager_.getWallDirection();
	// 壁移動
	position_ += direction_ * speed_ * deltaTimer_;
}

void WallMoveEnemy::addWSPPosition()
{
	// 位置の追加
	auto addPos = -1;
	// 0
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 1
	fspPositionContainer_.push_back(
		Vector2(0.0f, -(scale_ / 2.0f + addScale_.y / 2.0f) + -addPos));
	// 2
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 3
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) + -addPos, 0.0f));
	// 4
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f - -addPos, 0.0f));
	// 5
	fspPositionContainer_.push_back(
		Vector2(
			-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
	// 6
	fspPositionContainer_.push_back(
		Vector2(0.0f, scale_ / 2.0f + addScale_.y / 2.0f - -addPos));
	// 7
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
}

void WallMoveEnemy::addWSPScale()
{
	auto addScale = 0;
	// 0
	fspScaleContainer_.push_back(addScale_);
	// 1
	fspScaleContainer_.push_back(Vector2(scale_ +  addScale, addScale_.y));
	// 2
	fspScaleContainer_.push_back(addScale_);
	// 3
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_ + addScale));
	// 4
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_ + addScale));
	// 5
	fspScaleContainer_.push_back(addScale_);
	// 6
	fspScaleContainer_.push_back(Vector2(scale_ + addScale, addScale_.y));
	// 7
	fspScaleContainer_.push_back(addScale_);
}
