#include "MiniBossManager.h"
#include "MiniBoss.h"

MiniBossManager::MiniBossManager()
{
}

void MiniBossManager::update(float deltaTime)
{
}

// �~�j�{�X�̒ǉ����s���܂�
void MiniBossManager::addMiniBoss(MiniBoss * miniBoss)
{
	miniBosses_.push_front(miniBoss);
}

// �~�j�{�X�S�̂̍�����Ԃ��������܂�
void MiniBossManager::backToSanity()
{
	for (auto i = miniBosses_.begin(); i != miniBosses_.end(); i++) {
		auto miniBoss = *i;
		miniBoss->backToSanity();
	}
}

// �~�j�{�X�S�̂��{�X�̈ʒu�ɂ��邩��Ԃ��܂�
bool MiniBossManager::isMiniBossAllBP()
{
	for (auto i = miniBosses_.begin(); i != miniBosses_.end(); i++) {
		auto miniBoss = *i;
		if (!miniBoss->isBossPosition()) 
			return false;
	}
	return true;
}

// �~�j�{�X���{�X�����グ��Ԃɂ��܂�
void MiniBossManager::bossLift()
{
	for (auto i = miniBosses_.begin(); i != miniBosses_.end(); i++) {
		auto miniBoss = *i;
		miniBoss->bossLift();
	}
}

// �����グ�I�������
bool MiniBossManager::isLiftEnd()
{
	for (auto i = miniBosses_.begin(); i != miniBosses_.end(); i++) {
		auto miniBoss = *i;
		if (!miniBoss->isLift())
			return false;
	}
	return true;
}

// �����グ�ړ����x�̐ݒ�
void MiniBossManager::LiftMove(const float speed)
{
	for (auto i = miniBosses_.begin(); i != miniBosses_.end(); i++) {
		auto miniBoss = *i;
		miniBoss->setLiftMove(speed);
	}
}
