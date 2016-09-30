#ifndef _GAME_H_
#define _GAME_H_

#include "DxLib.h"
#include "Time.h"
#include "../Input/InputMgr.h"

class Game{
protected:
	// �R���X�g���N�^
	Game(int width = 800, int height = 600, int fullScreen = TRUE, float fps = 60.0f):
		width_(width), 
		height_(height), 
		fullScreen_(fullScreen), 
		fps_(fps) {
		
	}

public:
	// ���s
	int run() {
		ChangeWindowMode(fullScreen_);
		
		SetGraphMode(width_, height_, 32);

		//DXLib����������
		if (DxLib_Init() == -1)return -1;//�G���[���N������I��


		start();

		// �L�[���������܂Ń��[�v���܂�
		while (isRunning()){
			// ��ʂ��N���A
			ClearDrawScreen();

			Time::GetInstance().update();
			InputMgr::GetInstance().GetHitKeyFrameAll();			
			update();
			draw();
			// ����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();

		}

		end();

		DxLib_End();	//DXLib�g�p�I������

		return 0;	//�\�t�g�I��
	}

private:
	// �J�n
	virtual void start() {}
	// �X�V
	virtual void update() {}
	// �`��
	virtual void draw() {}
	// �I��
	virtual void end() {}
	// ���s����
	virtual bool isRunning() { return (ProcessMessage() == 0 && InputMgr::GetInstance().IsKeyUp(KeyCode::ESCAPE) == 0); }

private:
	// �R�s�[�֎~
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	// �E�B���h�E�̕�
	int width_;
	// �E�B���h�E�̍���
	int height_;
	// �t���X�N���[�����H
	int fullScreen_;
	// FPS
	float fps_;
};

#endif