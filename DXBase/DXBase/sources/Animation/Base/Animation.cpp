#include "Animation.h"

#include <math.h>

#define ANIM_BLEND_SPEED 0.1f;
#define PLAY_ANIM_SPEED 0.8f;

Animation::Animation(const unsigned int &modelHandle_) :
	modelHandle_(modelHandle_), animBlendRate_(1.0f){

}

void Animation::update(float deltaTime){
	process();
}

void Animation::process(){
	float AnimTotalTime;		// �Đ����Ă���A�j���[�V�����̑�����

	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (animBlendRate_ < 1.0f)
	{
		animBlendRate_ += ANIM_BLEND_SPEED;
		if (animBlendRate_ > 1.0f)
		{
			animBlendRate_ = 1.0f;
		}
	}

	// �Đ����Ă���A�j���[�V�����P�̏���
	if (currAnim_.id_ != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, currAnim_.id_);

		// �Đ����Ԃ�i�߂�
		currAnim_.count_ += PLAY_ANIM_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (currAnim_.count_ >= AnimTotalTime)
		{
			currAnim_.count_ = fmodf(currAnim_.count_, AnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle_, currAnim_.id_, currAnim_.count_);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle_, currAnim_.id_, animBlendRate_);
	}

	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (prevAnim_.id_ != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, prevAnim_.id_);

		// �Đ����Ԃ�i�߂�
		prevAnim_.count_ += PLAY_ANIM_SPEED;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (prevAnim_.count_ > AnimTotalTime)
		{
			prevAnim_.count_ = fmodf(prevAnim_.count_, AnimTotalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle_, prevAnim_.id_, prevAnim_.count_);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle_, prevAnim_.id_, 1.0f - animBlendRate_);
	}
}

void Animation::changeAnim(int id){
	if (id_ == id)return;
	id_ = id;
	// �Đ����̃��[�V�����Q���L����������f�^�b�`����
	if (prevAnim_.id_ != -1){
		MV1DetachAnim(modelHandle_, prevAnim_.id_);
		prevAnim_.id_ = -1;
	}

	// ���܂ōĐ����̃��[�V�����P���������̂̏����Q�Ɉړ�����
	prevAnim_ = currAnim_;

	// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`���āA�A�^�b�`�ԍ���ۑ�����
	currAnim_.id_ = MV1AttachAnim(modelHandle_, id);
	currAnim_.count_ = 0.0f;

	// �u�����h���͍Đ����̃��[�V�����Q���L���ł͂Ȃ��ꍇ�͂P�D�O��( �Đ����̃��[�V�����P���P�O�O���̏�� )�ɂ���
	animBlendRate_ = prevAnim_.id_ == -1 ? 1.0f : 0.0f;
}

bool Animation::isAnimEnd(){
	// �Đ����Ă���A�j���[�V�����̑�����
	float AnimTotalTime = MV1GetAttachAnimTotalTime(modelHandle_, currAnim_.id_);
	return 	currAnim_.count_ >= AnimTotalTime - 1;
}
