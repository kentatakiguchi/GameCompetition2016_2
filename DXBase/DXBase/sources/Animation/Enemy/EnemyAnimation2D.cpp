#include "EnemyAnimation2D.h"

EnemyAnimation2D::EnemyAnimation2D() : 
	prevFrame_(0),
	isLoop_(true),
	isStop_(false){}

// �X�V(������update)
void EnemyAnimation2D::onUpdate(float deltaTime)
{
	back_to_pre_motion();
	// �A�j���[�V�����̃^�C�������������A�~�߂�
	if (isStop_)return;

	// �X�V
	//update(deltaTime);

	frame_ = static_cast<int>(timer_) % sprites_[anim_num_].size();
	// ���[�v���Ȃ��Ȃ�
	if (!isLoop_) {
		// �ߋ��̃t���[�������݂̃t���[�������傫���Ȃ�A
		// �t���[�����ő�l�ɂ���
		/*if (prevFrame_ > frame_)
			frame_ = sprites_[anim_num_].size();*/
	}
	id_ = sprites_[anim_num_][frame_];
	timer_ += deltaTime * speed_ * 60.0f / sprites_[anim_num_].size() * 10;
	// ���[�v���Ȃ��Ȃ�
	if (!isLoop_) {
		// �A�j���[�V�����̃^�C�������������A�~�߂�
		if (timer_ >= sprites_[anim_num_].size() - 1) {
			frame_ = sprites_[anim_num_].size() - 1;
			timer_ = sprites_[anim_num_].size() - 1;
			isStop_ = true;
		}
	}

	// ���[�v���̍X�V
	// �t���[���̍X�V
	prevFrame_ = frame_;
}

// �A�j���[�V�����̒ǉ�
void EnemyAnimation2D::addAnimation(
	int id, int res, int size, int row, int column, int surplus)
{
	// �c�����
	//for (int i = 0; i != column; i++) {
	//	// �c���Ō�̗�ƂȂ����ꍇ�́A���ɓ������񐔂����炷
	//	// �c���Ō�̗�܂ŒB���Ă����Ȃ��ꍇ�́A���ɓ������񐔂����炳���ɉ�
	//	for (int j = 0; j != ((i < column - 1) ? row : row - surplus); j++) {
	//		// �؂��鍶��̍��W
	//		Vector2 src = Vector2(size * j, size * i);
	//		// �O���t�B�b�N�̓o�^
	//		int id_ = DerivationGraph(src.x, src.y, size, size, res);
	//		sprites_[id].push_back(id_);
	//	}
	//}
	//type_ = ActionType::Left;
	add_anim(static_cast<int>(id), res, size, row, column, surplus);

}

// �A�j���[�V�����̒ǉ�(�T�C�Y��X, Y�w��)
void EnemyAnimation2D::addAnimation(int id, int res, Vector2 size, int row, int column, int surplus)
{
}

// �A�j���[�V�����̕ύX
void EnemyAnimation2D::changeAnimation(int id, float speed)
{
	// �e�̕ύX���g��
	change_param(id, speed);
}

// �A�j���[�V�����̂��I���������Ԃ��܂�
bool EnemyAnimation2D::isEndAnimation()
{
	return end_anim();
}

// �A�j���[�V�����̃e�N�X�`���𔽓]���܂�
void EnemyAnimation2D::turnAnimation(int id, int direction)
{
	// �A�N�V�����^�C�v�̎擾
	if (direction > 0)
		type_ = ActionType::Left;
	else type_ = ActionType::Right;
	change_dir_type(id, type_);
}

// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
void EnemyAnimation2D::setIsLoop(bool isLoop)
{
	isLoop_ = isLoop;
	if (isLoop_)
		isStop_ = false;
}
