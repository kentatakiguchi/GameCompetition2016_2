#pragma once
#include "Math/Math.h"

/* �E�C���h�E�n�� */

//// �X�N���[���̃T�C�Y�{��
//const static float		SCREEN_RATE = 200;
// �X�N���[���̃T�C�Y
const static Vector2	SCREEN_SIZE = Vector2(1920, 1080);
// �X�N���[���̃A�X�y�N�g��
const static float		SCREEN_ASPECT = SCREEN_SIZE.x / SCREEN_SIZE.y;
// �E�C���h�E�̕\���{��(�����炭�f�o�b�N���̂�)
const static float		WINDOW_RATE = 0.5f;
// �E�C���h�E���[�h�ɂ��邩���Ȃ���(TRUE : FALSE)
const static int		WINDOW_MODE = TRUE;


//�ǉ�����萔�͎����̖��O�̉��ɏ����Ă��������B
//�������N����\���������̂ň����ɂ͒���

/*** � ***/
const static Vector2	BOSSBODY_POSITION = Vector2(SCREEN_SIZE.x - 96 * 3, SCREEN_SIZE.y + 96 * 10);



/*** �Љ� ***/




/*** �{�� ***/

const static float CHIPSIZE = 96;

const static float TURNLESS_FLOOR_SIZE = 1;

const static float RIGHTLEFTRANGE = 3;

const static float UPDOWNRANGE = 3;


/*** �i�� ***/



/* �v���C���[�p�����[�^�n�� */
//�v���C���[�̃f�t�H���g�̊J�n�ʒu
static const Vector2 START_POS = Vector2(700, 1500);
// �v���C���[�̕\���ʒu
const static Vector2	PLAYER_SCREEN_POSITION = Vector2(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.75f);
// �v���C���[�̈ړ����x
const static float		PLAYER_SPEED = 10.0f;
// �v���C���[�̖{�̂̔��a
const static float		PLAYER_RADIUS = CHIPSIZE * 0.5f;
// �v���C���[�̖{�̂̏Փ˂̔��a
const static float		PLAYER_COLLIDER_RADIUS = PLAYER_RADIUS * 1.25f;
// �v���C���[�̒ʏ�̒���
const static float		PLAYER_MAX_NORMAL_LENGTH = CHIPSIZE * 2;
// �v���C���[���L�т��ꍇ�̍ő�l
const static float		PLAYER_MAX_STRETCH_LENGTH = CHIPSIZE * 4;
// �v���C���[�̔��ˑ��x
const static float		PLAYER_LAUNCH_POWER = 140.0f;
// �v���C���[�̃W�����v���x
const static float		PLAYER_JUMP_POWER = 30.0f;
// �v���C���[�̋����葬�x
const static float		PLAYER_LEANBACK_POWER = 10.0f;
// �v���C���[�̖��G����
const static float		PLAYER_INV_TIME = 3.0f;
// �v���C���[�̎��S�܂ł̎���
const static float		PLAYER_DEAD_LIMIT = 5.0f;







