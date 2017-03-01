#ifndef STAR_EFFECT_MANAGER_H_
#define STAR_EFFECT_MANAGER_H_

//#include "DxLib.h"
#include "../../Math/Math.h"
#include <vector>
#include <list>

class IWorld;
class StarEffect;

class StarEffectManager {
public:
	StarEffectManager();
	StarEffectManager(IWorld* world);
	~StarEffectManager() {}
	void initialeze();
	void update();
	void end();

public:
	// ���̈ʒu�̐ݒ�
	void setStartPosition(const Vector2& position, const float addPositionX);
	// ���̉��o���I����������Ԃ��܂�
	bool isEffectEnd();

private:
	// ���̐���
	void createStars();
	// ���̍X�V
	void updateStars();
	// ���𓮂����܂�
	void moveStars();

private:
	// ���֘A
	int starCount_;						// ���̐�����
	bool isCreateStar_;					// ���𐶐�������
	bool isIdelEnd_;					// �ҋ@��Ԃ��I�����Ă��邩
	bool isPowerUpCreate_;				// �G�t�F�N�g�𐶐�������
	bool isEffectEnd_;					// ���o���I��������
	IWorld* world_;						// ���[���h
	// ���̐����ʒu�R���e�i
	std::vector<Vector2> startPositiones_;
	// ���i�[�R���e�i
	typedef std::list<StarEffect*> StarContainer;
	StarContainer stars_;
};


#endif