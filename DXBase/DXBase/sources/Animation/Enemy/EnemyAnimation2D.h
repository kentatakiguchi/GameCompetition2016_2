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
	// �A�j���[�V�����̒ǉ�
	// (�A�j���[�V������ID, ���\�[�XID, ���̐�, �c�̐�, ���̐��̌���鐔)
	/*void addAnimation(
		EnemyAnimationID id, int res, int size, int row, int column, int surplus);*/
	void addAnimation(
		int id, int res, int size, int row, int column, int surplus = 0);
	// �A�j���[�V�����̕ύX
	/*void changeAnimation(EnemyAnimationID id, float speed = 1.0f);*/
	void changeAnimation(int id, float speed = 1.0f);

	// �A�j���[�V�����̂��I���������Ԃ��܂�
	bool isEndAnimation();

	// �A�j���[�V�����̃e�N�X�`���𔽓]���܂�
	void turnAnimation(int id);
};


#endif
