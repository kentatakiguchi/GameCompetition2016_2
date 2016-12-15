#include "EnemyAnimation2D.h"

EnemyAnimation2D::EnemyAnimation2D() : 
	prevFrame_(0),
	isLoop_(true),
	isStop_(false){}

// 更新(自分のupdate)
void EnemyAnimation2D::onUpdate(float deltaTime)
{
	back_to_pre_motion();
	// アニメーションのタイムが一周したら、止める
	if (isStop_)return;

	// 更新
	//update(deltaTime);

	frame_ = static_cast<int>(timer_) % sprites_[anim_num_].size();
	// ループしないなら
	if (!isLoop_) {
		// 過去のフレームが現在のフレームよりも大きいなら、
		// フレームを最大値にする
		/*if (prevFrame_ > frame_)
			frame_ = sprites_[anim_num_].size();*/
	}
	id_ = sprites_[anim_num_][frame_];
	timer_ += deltaTime * speed_ * 60.0f / sprites_[anim_num_].size() * 10;
	// ループしないなら
	if (!isLoop_) {
		// アニメーションのタイムが一周したら、止める
		if (timer_ >= sprites_[anim_num_].size() - 1) {
			frame_ = sprites_[anim_num_].size() - 1;
			timer_ = sprites_[anim_num_].size() - 1;
			isStop_ = true;
		}
	}

	// ループ時の更新
	// フレームの更新
	prevFrame_ = frame_;
}

// アニメーションの追加
void EnemyAnimation2D::addAnimation(
	int id, int res, int size, int row, int column, int surplus)
{
	// 縦から回す
	//for (int i = 0; i != column; i++) {
	//	// 縦が最後の列となった場合は、横に動かす回数を減らす
	//	// 縦が最後の列まで達していいない場合は、横に動かす回数を減らさずに回す
	//	for (int j = 0; j != ((i < column - 1) ? row : row - surplus); j++) {
	//		// 切り取る左上の座標
	//		Vector2 src = Vector2(size * j, size * i);
	//		// グラフィックの登録
	//		int id_ = DerivationGraph(src.x, src.y, size, size, res);
	//		sprites_[id].push_back(id_);
	//	}
	//}
	//type_ = ActionType::Left;
	add_anim(static_cast<int>(id), res, size, row, column, surplus);

}

// アニメーションの追加(サイズのX, Y指定)
void EnemyAnimation2D::addAnimation(int id, int res, Vector2 size, int row, int column, int surplus)
{
}

// アニメーションの変更
void EnemyAnimation2D::changeAnimation(int id, float speed)
{
	// 親の変更を使う
	change_param(id, speed);
}

// アニメーションのが終わったかを返します
bool EnemyAnimation2D::isEndAnimation()
{
	return end_anim();
}

// アニメーションのテクスチャを反転します
void EnemyAnimation2D::turnAnimation(int id, int direction)
{
	// アクションタイプの取得
	if (direction > 0)
		type_ = ActionType::Left;
	else type_ = ActionType::Right;
	change_dir_type(id, type_);
}

// アニメーションをループさせるかを設定します
void EnemyAnimation2D::setIsLoop(bool isLoop)
{
	isLoop_ = isLoop;
	if (isLoop_)
		isStop_ = false;
}
