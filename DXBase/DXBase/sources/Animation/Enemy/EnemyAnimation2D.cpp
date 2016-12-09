#include "EnemyAnimation2D.h"

EnemyAnimation2D::EnemyAnimation2D(){}

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
	add_anim(static_cast<int>(id), res, size, row, column, surplus);

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
void EnemyAnimation2D::turnAnimation(int id)
{
	// �A�N�V�����^�C�v�̎擾
	auto type = type_;
	if (type_ == ActionType::Left)
		type = ActionType::Left;
	else type = ActionType::Right;
	change_dir_type(id, type);
}
