#include "Animation2D.h"

using namespace std;

Animation2D::Animation2D() :
	type_(ActionType::Right) {
}

void Animation2D::change_param(int anim_num, float speed) {
	//�Đ����x��ύX
	speed_ = speed;
	//�A�j���[�V�����������ꍇ��return
	if (anim_num_ == anim_num)return;
	//�w�肵���A�j���[�V�����ɕύX
	anim_num_ = anim_num;
	//�Đ����Ԃ����Z�b�g
	timer_ = 0;
}

void Animation2D::change_dir_type(int anim_num, ActionType type){
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
	return frame_ == sprites_[anim_num_].size();
}

void Animation2D::update(float deltaTime) {
	frame_ = static_cast<int>(timer_) % sprites_[anim_num_].size();
	id_ = sprites_[anim_num_][frame_];
	//�X�V����
	timer_ += deltaTime * speed_ * 60.0f / sprites_[anim_num_].size() * 10;

	back_to_pre_motion();
}

void Animation2D::draw(Vector2 position, Vector2 origin, float scale, float degree, Vector3 color) const{
	draw(position, origin, Vector2::One * scale, degree, color);
}

void Animation2D::draw(Vector2 position, Vector2 origin, Vector2 scale, float degree, Vector3 color) const {
	SetDrawBright(color.x, color.y, color.z);
	//�x���@���ʓx�@�ɕϊ�
	float radian = MathHelper::ToRadians(degree);
	if (type_ == ActionType::Right)DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE, FALSE);
	if (type_ == ActionType::Left) DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE, TRUE);
	SetDrawBright(255, 255, 255);
}

