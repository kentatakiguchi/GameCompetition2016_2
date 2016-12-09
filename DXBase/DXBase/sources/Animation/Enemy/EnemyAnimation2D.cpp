#include "EnemyAnimation2D.h"

EnemyAnimation2D::EnemyAnimation2D(){}

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
	add_anim(static_cast<int>(id), res, size, row, column, surplus);

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
void EnemyAnimation2D::turnAnimation(int id)
{
	// アクションタイプの取得
	auto type = type_;
	if (type_ == ActionType::Left)
		type = ActionType::Left;
	else type = ActionType::Right;
	change_dir_type(id, type);
}
