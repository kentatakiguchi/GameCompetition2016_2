#pragma once

#include <DxLib.h>

#include <unordered_map>
#include <vector>
#include "../../Math/Math.h"
#include "../../Actor/Person/Player/State/Base/ActionType.h"

class Animation2D {
public:
	// �R���X�g���N�^
	Animation2D(const ActionType& type = ActionType::Right);
	// �R���X�g���N�^
	virtual ~Animation2D();
	// �X�V����
	virtual void update(float deltaTime);
	// �A�j���[�V�����̏I���t���O
	bool end_anim();
	// �`��
	// ���W,(��),(�g�嗦),(��]�p�x(�x���@)),
	void draw(const Vector2& position, const Vector2& origin = Vector2::Zero, const float& scale = 1, const float& degree = 0, const Vector3& color = Vector3(255, 255, 255)) const;
	// ���W,��,�g�嗦,��]�p�x(�x���@),
	void draw(const Vector2& position, const Vector2& origin = Vector2::Zero, const Vector2& scale = Vector2::One, const float& degree = 0, const Vector3& color = Vector3(255, 255, 255)) const;
	//���]�t��
	void drawTurn(const Vector2& position, const Vector2& origin = Vector2::Zero, const float& scale = 1, const float& degree = 0, const Vector3& color = Vector3(255, 255, 255),bool reversal=false) const;

public:
	void add_anim(const int & id, const std::vector<int>& anims);
	// �A�j���[�V�����̕ύX(���x�̂ݕύX���\)
	void change_param(const int& anim_num, const float& speed = 1.0f);
	// �A�j���[�V�����̕����]��
	void change_dir_type(const int& anim_num, const ActionType& type);
	// �A�j���[�V���������ɖ߂�
	void back_to_pre_motion();
protected:
	//�����O�̉摜id
	int id_;
	//���݂̃A�j���[�V����
	int curr_anim_;
	int norm_anim_;
	int turn_anim_;
	float curr_speed_;
	float norm_speed_;
	float turn_speed_;

	unsigned int frame_;
	//�A�j���[�V�����̍Đ�����
	float timer_;
	
	ActionType type_stock_;
	ActionType type_;
	//�������id�i�[�p�������z��
	std::unordered_map<int, std::vector<int>> sprites_;
};