#include "EnemyAnimation2D.h"
#include <random>

EnemyAnimation2D::EnemyAnimation2D() : 
	prevFrame_(0),
	isLoop_(true),
	isStop_(false),
	isTurn_(false),
	isReverse_(false){}

EnemyAnimation2D::~EnemyAnimation2D()
{
	sprites_.clear();
}

void EnemyAnimation2D::update(float deltaTime)
{
	preMotion();
	// �A�j���[�V�����̃^�C�������������A�~�߂�
	if (isStop_)return;
	// �X�V
	if (curr_anim_ >= 15 || curr_anim_ <= -1) return;
	frame_ = static_cast<int>(timer_) % sprites_[curr_anim_].size();
	id_ = sprites_[curr_anim_][frame_];
	auto timer = deltaTime * curr_speed_ * 60.0f / sprites_[curr_anim_].size() * 10;
	// �t�Đ�����Ȃ�΁A�l�𔽓]����
	if (isReverse_)
		timer *= -1.0f;
	timer_ += timer;
	// ���[�v���Ȃ��Ȃ�
	if (!isLoop_) {
		// �A�j���[�V�����̃^�C�������������A�~�߂�
		if (!isReverse_) {
			if (timer_ >= sprites_[curr_anim_].size() - 2) {
				frame_ = static_cast<unsigned int>(sprites_[curr_anim_].size() - 1);
				timer_ = (float)sprites_[curr_anim_].size() - 1;
				isStop_ = true;
			}
		}
		else {
			if (timer_ <= 1) {
				frame_ = 0;
				timer_ = 0;
				isStop_ = true;
			}
		}
	}
	isBeginTurn_ = false;
	if (isTurn_)
		isBeginTurn_ = true;
	isTurn_ = false;
	// ���[�v���̍X�V
	// �t���[���̍X�V
	prevFrame_ = frame_;
}

// �A�j���[�V�����̒ǉ�
void EnemyAnimation2D::addAnimation(int id, const std::vector<int>& anims)
{
	add_anim(id, anims);
}

// �A�j���[�V�����̕ύX
void EnemyAnimation2D::changeAnimation(int id, float speed)
{
	isLoop_ = true;
	isStop_ = false;
	// �e�̕ύX���g��
	change_param(id, speed);
}

// �A�j���[�V�����̂��I���������Ԃ��܂�
bool EnemyAnimation2D::isEndAnimation()
{
	return end_anim();
}

// �U������A�j���[�V�������s���āA�摜�𔽓]���܂�
void EnemyAnimation2D::turnAnimation(int id, float direction)
{
	auto type = ActionType::Right;
	// �A�N�V�����^�C�v�̎擾
	if (direction >= 0)
		type = ActionType::Left;
	change_dir_type(id, type);
}

// �A�j���[�V������U������A�j���[�V�������s�킸�ɉ摜�𔽓]���܂�
void EnemyAnimation2D::changeDirType(float direction)
{
	auto type = ActionType::Right;
	// �A�N�V�����^�C�v�̎擾
	if (direction >= 0)
		type = ActionType::Left;
	if (type_ == type) return;
	type_ = type;
	type_stock_ = type;
	isTurn_ = true;
}

// �A�j���[�V�����̎��Ԃ����������܂�
void EnemyAnimation2D::initAnimeTime()
{
	frame_ = 0;
	timer_ = 0;
}

// �A�j���[�V�����̍Đ����x��ύX���܂�
void EnemyAnimation2D::setSpeed(float speed)
{
	curr_speed_ = norm_speed_ = speed;
}

// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
void EnemyAnimation2D::setIsLoop(bool isLoop)
{
	isLoop_ = isLoop;
	if (isLoop_)
		isStop_ = false;
}

// �t�Đ����邩��ݒ肵�܂�
void EnemyAnimation2D::setIsReverse(bool isReverse)
{
	isReverse_ = isReverse;
	isStop_ = false;
}

void EnemyAnimation2D::preMotion()
{
	if (turn_anim_ != -1 && end_anim())
		isTurn_ = false;
	back_to_pre_motion();
}

void EnemyAnimation2D::stopAnime()
{
	isStop_ = true;
}

// �A�j���[�V�����̃^�C���������_���ɂ��܂�
void EnemyAnimation2D::timeRandom()
{
	// �����̎擾
	std::random_device random;
	// �����Z���k�c�C�X�^�[�@ ��Œ��ׂ�
	// ����Seed�l��n��
	std::mt19937 mt(random());
	// �͈͂̎w��(int�^)
	std::uniform_int_distribution<> rFrame(0, sprites_[curr_anim_].size() - 1);
	//return count(mt);
	frame_ = static_cast<unsigned int>(rFrame(mt));
	timer_ = (float)rFrame(mt);
}

// �A�j���[�V�����̌�����ς�������Ԃ��܂�(1f)
bool EnemyAnimation2D::isBeginTurn()
{
	return isBeginTurn_;
}

// ���݂̍Đ��t���[�����擾���܂�
unsigned int EnemyAnimation2D::getFrame()
{
	return frame_;
}
