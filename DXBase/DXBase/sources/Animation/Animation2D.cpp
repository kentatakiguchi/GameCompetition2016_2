#include "Animation2D.h"

using namespace std;

Animation2D::Animation2D() {}

Animation2D::Animation2D(int id, int row, int column) :
	id_(id), anim_num_(0), row_(row), column_(column), timer_(0), speed_(1) {
	registSprite();
}

void Animation2D::registSprite() {
	//分割前の画像サイズ
	Vector2 size = getSize();
	//分割した際の個々の画像サイズ
	Vector2 divSize = Vector2(size.x / row_, size.y / column_);
	//配列の確保
	sprites_ = vector<vector<int>>(column_, vector<int>(row_));
	//分割後のidを格納
	for (int i = 0; i < column_; ++i) {
		for (int j = 0; j < row_; ++j) {
			Vector2 src = Vector2(size.x / row_ * j, size.y / column_ * i);
			sprites_[i][j] = DerivationGraph(src.x, src.y, divSize.x, divSize.y, id_);
		}
	}
}

void Animation2D::change(int anim_num, float speed) {
	//再生速度を変更
	speed_ = speed;

	//アニメーションが同じ場合はreturn
	if (anim_num_ == anim_num)return;
	//指定したアニメーションに変更
	anim_num_ = anim_num;
	//再生時間をリセット
	timer_ = 0;
}

void Animation2D::update(float deltaTime) {
	//更新処理
	timer_ += deltaTime * speed_ * 10 / row_;
}

void Animation2D::draw(Vector2 position, Vector2 origin, float scale, float degree) const{
	draw(position, origin, Vector2::One * scale, degree);
}

void Animation2D::draw(Vector2 position, Vector2 origin, Vector2 scale, float degree) const {
	//度数法→弧度法に変換
	float radian = MathHelper::ToRadians(degree);
	DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian,  sprites_[anim_num_][static_cast<int>(timer_) % row_], TRUE);
}

Vector2 Animation2D::getSize() {
	int size_x, size_y;
	GetGraphSize(id_, &size_x, &size_y);
	return Vector2(size_x, size_y);
}
