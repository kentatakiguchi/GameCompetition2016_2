#pragma once

#include <DxLib.h>

#include <vector>
#include "../Math/Math.h"

class Animation2D {
public:
	// �R���X�g���N�^
	Animation2D();
	// �R���X�g���N�^(�摜id,���̕�����,�c�̕�����)
	Animation2D(int id, int row, int column);
	// �摜�𕪊����z��Ɋi�[
	void registSprite();
	// �A�j���[�V�����̕ύX(���x�̂ݕύX���\)
	void change(int anim_num, float speed = 1.0f);
	// �X�V����
	void update(float deltaTime);
	// �`��
	// ���W,(��),(�g�嗦),(��]�p�x(�x���@)),
	void draw(Vector2 position, Vector2 origin = Vector2::Zero, float scale = 1, float degree = 0) const;
	// ���W,��,�g�嗦,��]�p�x(�x���@),
	void draw(Vector2 position, Vector2 origin, Vector2 scale, float degree) const;
private:
	Vector2 getSize();
private:
	//�����O�̉摜id
	int id_;
	//���݂̃A�j���[�V����
	int anim_num_;
	//�s
	int row_;
	//��
	int column_;
	//�A�j���[�V�����̍Đ�����
	float timer_;
	//�A�j���[�V�����̍Đ����x
	float speed_;
	//�������id�i�[�p�������z��
	std::vector<std::vector<int>> sprites_;
};