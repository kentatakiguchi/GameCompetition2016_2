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
	~EnemyAnimation2D();
	// �X�V
	void update(float deltaTime) override;
	// �X�V(������update)
	//void onUpdate(float deltaTime);
	// �A�j���[�V�����̒ǉ�
	// (�A�j���[�V������ID, ���\�[�XID, ���̐�, �c�̐�, ���̐��̌���鐔)
	void addAnimation(int id, const std::vector<int>& anims);
	// �A�j���[�V�����̒ǉ�(�T�C�Y��X, Y�w��)
	/*void addAnimation(
		int id, int res, Vector2 size, int row, int column, int surplus = 0);*/
	// �A�j���[�V�����̕ύX
	void changeAnimation(int id, float speed = 1.0f);
	// �A�j���[�V�����̂��I���������Ԃ��܂�
	bool isEndAnimation();
	// �U������A�j���[�V�������s���āA�摜�𔽓]���܂�
	void turnAnimation(int id, float direction);
	// �A�j���[�V������U������A�j���[�V�������s�킸�ɉ摜�𔽓]���܂�
	void changeDirType(float direction);
	// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
	void setIsLoop(bool isLoop);
	//
	void preMotion();

public:
	int prevFrame_;		// 1f�O�̃t���[��
	bool isLoop_;		// ���[�v���邩
	bool isStop_;		// �A�j���[�V�������~�߂邩
	bool isTurn_;		// �U������A�j���[�V������������
};


#endif
