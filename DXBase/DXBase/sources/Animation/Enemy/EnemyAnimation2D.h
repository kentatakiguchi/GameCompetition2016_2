#ifndef ENMEY_ANIMATION2D_H_
#define ENMEY_ANIMATION2D_H_

#include "../Base/Animation2D.h"

#include <unordered_map>

class EnemyAnimation2D : public Animation2D {

public:
	EnemyAnimation2D();
	~EnemyAnimation2D();
	// �X�V
	void update(float deltaTime) override;
	// �A�j���[�V�����̒ǉ�
	// (�A�j���[�V������ID, ���\�[�XID, ���̐�, �c�̐�, ���̐��̌���鐔)
	void addAnimation(int id, const std::vector<int>& anims);
	// �A�j���[�V�����̕ύX
	void changeAnimation(int id, float speed = 1.0f);
	// �A�j���[�V�����̂��I���������Ԃ��܂�
	bool isEndAnimation();
	// �U������A�j���[�V�������s���āA�摜�𔽓]���܂�
	void turnAnimation(int id, float direction);
	// �A�j���[�V������U������A�j���[�V�������s�킸�ɉ摜�𔽓]���܂�
	void changeDirType(float direction);
	// �A�j���[�V�����̎��Ԃ����������܂�
	void initAnimeTime();
	// �A�j���[�V�����̍Đ����x��ύX���܂�
	void setSpeed(float speed);
	// �A�j���[�V���������[�v�����邩��ݒ肵�܂�
	void setIsLoop(bool isLoop);
	// �t�Đ����邩��ݒ肵�܂�
	void setIsReverse(bool isReverse);
	// 
	void preMotion();
	void stopAnime();
	// �A�j���[�V�����̃^�C���������_���ɂ��܂�
	void timeRandom();
	// �A�j���[�V�����̌�����ς�������Ԃ��܂�(1f)
	bool isBeginTurn();
	// ���݂̍Đ��t���[�����擾���܂�
	unsigned int getFrame();

public:
	int prevFrame_;			// 1f�O�̃t���[��
	bool isLoop_;			// ���[�v���邩
	bool isStop_;			// �A�j���[�V�������~�߂邩
	bool isTurn_;			// �U������A�j���[�V������������
	bool isBeginTurn_;		// �U������A�j���[�V������������(1f)
	bool isReverse_;		// �t�Đ����邩
};


#endif
