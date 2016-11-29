#include "Animation2D.h"

using namespace std;

Animation2D::Animation2D() {}

void Animation2D::change_param(int anim_num, float speed) {
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
	std::vector<int> anim = sprites_[anim_num_];
	id_ = anim[static_cast<int>(timer_) % sprites_[anim_num_].size()];
	//更新処理
	timer_ += deltaTime * speed_ * 60 / sprites_[anim_num_].size() * 10;
}

void Animation2D::draw(Vector2 position, Vector2 origin, float scale, float degree, Vector3 color) const{
	draw(position, origin, Vector2::One * scale, degree, color);
}

void Animation2D::draw(Vector2 position, Vector2 origin, Vector2 scale, float degree, Vector3 color) const {
	SetDrawBright(color.x, color.y, color.z);
	//度数法→弧度法に変換
	float radian = MathHelper::ToRadians(degree);
	DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE);
	SetDrawBright(255, 255, 255);
}

Vector2 Animation2D::getSize() {
	int size_x, size_y;
	GetGraphSize(id_, &size_x, &size_y);
	return Vector2(size_x, size_y);
}
