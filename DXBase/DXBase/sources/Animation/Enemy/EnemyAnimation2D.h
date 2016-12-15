#ifndef ENMEY_ANIMATION2D_H_
#define ENMEY_ANIMATION2D_H_

#include "../Base/Animation2D.h"

#include <unordered_map>

//enum class EnemyAnimationID {
//	Idel,
//	Search,
//	Chase,
//	Attack,
//	Damage,
//	Dead
//};

class EnemyAnimation2D : public Animation2D {
//public:
//	enum class EnemyAnimationID {
//		Idel,
//		Search,
//		Chase,
//		Attack,
//		Damage,
//		Dead
//	};

public:
	EnemyAnimation2D();
	// �X�V(������update)
	void onUpdate(float deltaTime);
	// �A�j���[�V�����̒ǉ�
	// (�A�j���[�V������ID, ���\�[�XID, ���̐�, �c�̐�, ���̐��̌���鐔)
	void addAnimation(
		int id, int res, int size, int row, int column, int surplus = 0);
	// �A�j���[�V�����̒ǉ�(�T�C�Y��X, Y�w��)
	void addAnimation(
		int id, int res, Vector2 size, int row, int column, int surplus = 0);
	// �A�j���[�V�����̕ύX
	void changeAnimation(int id, float speed = 1.0f);
	// �A�j���[�V�����̂��I���������Ԃ��܂�
	bool isEndAnimation();
	// �A�j���[�V�����̃e�N�X�`���𔽓]���܂�
	void turnAnimation(int id, int direction);
	// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
	void setIsLoop(bool isLoop);

public:
	int prevFrame_;		// 1f�O�̃t���[��
	bool isLoop_;		// ���[�v���邩
	bool isStop_;		// �A�j���[�V�������~�߂邩
};


#endif
