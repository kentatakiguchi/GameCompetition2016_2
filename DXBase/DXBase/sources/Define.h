#pragma once
#include "Math/Math.h"


//�ǉ�����萔�͎����̖��O�̉��ɏ����Ă��������B
//�������N����\���������̂ň����ɂ͒���

/*** � ***/




/*** �Љ� ***/




/*** �{�� ***/

const static float CHIPSIZE = 32;

const static float TURNLESS_FLOOR_SIZE = 2;



/*** �i�� ***/

/* �E�C���h�E�n�� */

// �X�N���[���̃A�X�y�N�g��
const static Vector2	SCREEN_ASPECT = Vector2(4, 3);
// �X�N���[���̃T�C�Y�{��
const static float		SCREEN_RATE = 200;
// �X�N���[���̃T�C�Y
const static Vector2	SCREEN_SIZE = SCREEN_ASPECT * SCREEN_RATE;
// �E�C���h�E�̕\���{��(�����炭�f�o�b�N���̂�)
const static float		WINDOW_RATE = 1.0f;
// �E�C���h�E���[�h�ɂ��邩���Ȃ���(TRUE : FALSE)
const static int		WINDOW_MODE = TRUE;

/* �v���C���[�p�����[�^�n�� */

// �v���C���[�̈ړ����x
const static float		PLAYER_SPEED = 3.0f;
// �v���C���[�̖{�̂̔��a
const static float		PLAYER_RADIUS = 24.0f;
// �v���C���[�̒ʏ�̒���
const static float		PLAYER_MAX_NORMAL_LENGTH = 50.0f;
// �v���C���[���L�т��ꍇ�̍ő�l
const static float		PLAYER_MAX_STRETCH_LENGTH = 100.0f;
// �v���C���[�̔��ˑ��x
const static float		PLAYER_LAUNCH_POWER = 50.0f;
// �v���C���[�̃W�����v���x
const static float		PLAYER_JUMP_POWER = 10.0f;





