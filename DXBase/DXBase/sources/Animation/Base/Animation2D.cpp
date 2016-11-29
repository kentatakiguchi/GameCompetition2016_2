#include "Animation2D.h"

using namespace std;

Animation2D::Animation2D() {}

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

void Animation2D::update(float deltaTime) {
	std::vector<int> anim = sprites_[anim_num_];
	id_ = anim[static_cast<int>(timer_) % sprites_[anim_num_].size()];
	//�X�V����
	timer_ += deltaTime * speed_ * 60 / sprites_[anim_num_].size() * 10;
}

void Animation2D::draw(Vector2 position, Vector2 origin, float scale, float degree, Vector3 color) const{
	draw(position, origin, Vector2::One * scale, degree, color);
}

void Animation2D::draw(Vector2 position, Vector2 origin, Vector2 scale, float degree, Vector3 color) const {
	SetDrawBright(color.x, color.y, color.z);
	//�x���@���ʓx�@�ɕϊ�
	float radian = MathHelper::ToRadians(degree);
	DrawRotaGraph3(position.x, position.y, origin.x, origin.y, static_cast<float>(scale.x), static_cast<float>(scale.y), radian, id_, TRUE);
	SetDrawBright(255, 255, 255);
}

Vector2 Animation2D::getSize() {
	int size_x, size_y;
	GetGraphSize(id_, &size_x, &size_y);
	return Vector2(size_x, size_y);
}
