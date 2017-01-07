#include "EnemyAnimation2D.h"

EnemyAnimation2D::EnemyAnimation2D() : 
	prevFrame_(0),
	isLoop_(true),
	isStop_(false),
	isTurn_(false){}

EnemyAnimation2D::~EnemyAnimation2D()
{
	sprites_.clear();
}

void EnemyAnimation2D::update(float deltaTime)
{
	// back_to_pre_motion();
	preMotion();
	// �A�j���[�V�����̃^�C�������������A�~�߂�
	if (isStop_)return;

	// �X�V
	if (curr_anim_ >= 15 || curr_anim_ <= -1) return;
	frame_ = static_cast<int>(timer_) % sprites_[curr_anim_].size();
	//// ���[�v���Ȃ��Ȃ�
	//if (!isLoop_) {
	//	// �ߋ��̃t���[�������݂̃t���[�������傫���Ȃ�A
	//	// �t���[�����ő�l�ɂ���
	//	/*if (prevFrame_ > frame_)
	//	frame_ = sprites_[anim_num_].size();*/
	//}
	id_ = sprites_[curr_anim_][frame_];
	timer_ += deltaTime * curr_speed_ * 60.0f / sprites_[curr_anim_].size() * 10;
	// ���[�v���Ȃ��Ȃ�
	if (!isLoop_) {
		// �A�j���[�V�����̃^�C�������������A�~�߂�
		if (timer_ >= sprites_[curr_anim_].size() - 2) {
			frame_ = sprites_[curr_anim_].size() - 1;
			timer_ = sprites_[curr_anim_].size() - 1;
			isStop_ = true;
		}
	}

	// ���[�v���̍X�V
	// �t���[���̍X�V
	prevFrame_ = frame_;
}

// �X�V(������update)
//void EnemyAnimation2D::onUpdate(float deltaTime)
//{
//	
//}

// �A�j���[�V�����̒ǉ�
void EnemyAnimation2D::addAnimation(int id, const std::vector<int>& anims)
{
	add_anim(id, anims);

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

	//add_anim(static_cast<int>(id), res, size, row, column, surplus);

}

// �A�j���[�V�����̒ǉ�(�T�C�Y��X, Y�w��)
//void EnemyAnimation2D::addAnimation(int id, int res, Vector2 size, int row, int column, int surplus)
//{
//	for (int i = 0; i < column; ++i) {
//		for (int j = 0; j < ((i < column - 1) ? row : row - surplus); ++j) {
//			// �؂��鍶��̍��W
//			Vector2 src = Vector2(j * size.x, i * size.y);
//			sprites_[id].push_back(DerivationGraph(src.x, src.y, size.x, size.y, res));
//		}
//	}
//}

// �A�j���[�V�����̕ύX
void EnemyAnimation2D::changeAnimation(int id, float speed)
{
	/*if (id >= 15 || id <= -1)
		id = 0;*/
	isLoop_ = true;
	isStop_ = false;
	// �e�̕ύX���g��
	change_param(id, speed);
	
	//curr_anim_ = id;
}

// �A�j���[�V�����̂��I���������Ԃ��܂�
bool EnemyAnimation2D::isEndAnimation()
{
	return end_anim();
}

// �U������A�j���[�V�������s���āA�摜�𔽓]���܂�
void EnemyAnimation2D::turnAnimation(int id, float direction)
{
	/*isLoop_ = true;
	isStop_ = false;*/
	//if (isTurn_) return;
	auto type = ActionType::Right;
	// �A�N�V�����^�C�v�̎擾
	if (direction >= 0)
		type = ActionType::Left;
	change_dir_type(id, type);
	isTurn_ = true;
}

// �A�j���[�V������U������A�j���[�V�������s�킸�ɉ摜�𔽓]���܂�
void EnemyAnimation2D::changeDirType(float direction)
{
	auto type = ActionType::Right;
	// �A�N�V�����^�C�v�̎擾
	if (direction >= 0)
		type = ActionType::Left;
	type_ = type;
	type_stock_ = type;
}

// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
void EnemyAnimation2D::setIsLoop(bool isLoop)
{
	isLoop_ = isLoop;
	if (isLoop_)
		isStop_ = false;
}

void EnemyAnimation2D::preMotion()
{
	if (turn_anim_ != -1 && end_anim())
		isTurn_ = false;
	back_to_pre_motion();
}
