#include "Animation2D.h"

using namespace std;

Animation2D::Animation2D() :
	type_(ActionType::Right),
	anim_num_(-1),
	frame_(-1),
	pre_anim_(-1),
	pre_speed_(1),
	timer_(0),
	speed_(1){
}

void Animation2D::add_anim(const int & id, const int & res, const int & size, const int & row, const int & column, const int & surplus){
	for (int i = 0; i < column; ++i) {
		for (int j = 0; j < ((i < column - 1) ? row : row - surplus); ++j) {
			// 切り取る左上の座標
			Vector2 src = Vector2(j, i) * size;
			sprites_[id].push_back(DerivationGraph(src.x, src.y, size, size, res));
		}
	}
}

void Animation2D::change_param(const int& anim_num, const float& speed) {
	//再生速度を変更
	speed_ = speed;
	//アニメーションが同じ場合はreturn
	if (anim_num_ == anim_num)return;
	//指定したアニメーションに変更
	anim_num_ = anim_num;
	//再生時間をリセット
	timer_ = 0;
}

void Animation2D::change_dir_type(const int& anim_num, const ActionType& type){
	if (type_ == type)return;
	pre_anim_ = anim_num_;
	pre_speed_ = speed_;
	type_stock_ = type;
	change_param(anim_num, 1.0f);
}

void Animation2D::back_to_pre_motion(){
	if (pre_anim_ != -1 && end_anim()) {
		change_param(pre_anim_, pre_speed_);
		pre_anim_ = -1;
		type_ = type_stock_;
	}
}

bool Animation2D::end_anim(){
	return frame_ == sprites_[anim_num_].size() - 1;
}

void Animation2D::update(float deltaTime) {
	frame_ = static_cast<int>(timer_) % sprites_[anim_num_].size();
	id_ = sprites_[anim_num_][frame_];
	//更新処理
	timer_ += deltaTime * speed_ * 60.0f / sprites_[anim_num_].size() * 10;

	back_to_pre_motion();
}

void Animation2D::draw(const Vector2& position, const Vector2& origin, const float& scale, const float& degree, const Vector3& color) const{
	draw(position, origin, Vector2::One * scale, degree, color);
}

void Animation2D::draw(const Vector2& position, const Vector2& origin, const Vector2& scale, const float& degree, const Vector3& color) const {
	SetDrawBright(color.x, color.y, color.z);
	//度数法→弧度法に変換
	float radian = MathHelper::ToRadians(degree);
	if (type_ == ActionType::Right)DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE, FALSE);
	if (type_ == ActionType::Left) DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE, TRUE);
	SetDrawBright(255, 255, 255);
}

