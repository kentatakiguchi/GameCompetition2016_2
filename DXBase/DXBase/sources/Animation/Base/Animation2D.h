#pragma once

#include <DxLib.h>

#include <unordered_map>
#include <vector>
#include "../../Math/Math.h"
#include "../../Actor/Person/Player/State/Base/ActionType.h"

class Animation2D {
public:
	// �R���X�g���N�^
	Animation2D();
	// �A�j���[�V�����̕ύX(���x�̂ݕύX���\)
	void change_param(int anim_num, float speed = 1.0f);
	// �A�j���[�V�����̕����]��
	void change_dir_type(int anim_num, ActionType type);
	// �A�j���[�V���������ɖ߂�
	void back_to_pre_motion();
	// �A�j���[�V�����̕����]��
	bool end_anim();
	// �X�V����
	void update(float deltaTime);
	// �`��
	// ���W,(��),(�g�嗦),(��]�p�x(�x���@)),
	void draw(Vector2 position, Vector2 origin = Vector2::Zero, float scale = 1, float degree = 0, Vector3 color = Vector3(255, 255, 255)) const;
	// ���W,��,�g�嗦,��]�p�x(�x���@),
	void draw(Vector2 position, Vector2 origin, Vector2 scale, float degree, Vector3 color = Vector3(255, 255, 255)) const;
protected:
	//�����O�̉摜id
	int id_;
	//���݂̃A�j���[�V����
	int anim_num_;
	//
	int frame_;

	int pre_anim_;

	int pre_speed_;

	//�A�j���[�V�����̍Đ�����
	float timer_;
	//�A�j���[�V�����̍Đ����x
	float speed_;
	
	ActionType type_stock_;
	ActionType type_;
	//�������id�i�[�p�������z��
	std::unordered_map<int, std::vector<int>> sprites_;
};