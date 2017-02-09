#pragma once

#include "DxLib.h"
#include "GameDevice.h"

#include "../Input/InputMgr.h"

class Game{
protected:
	// �R���X�g���N�^
	Game(const char* windowName = "game", int width = 800, int height = 600, float rate = 1.0f, int window = TRUE, float fps = 60.0f):
		width_(width), height_(height), rate_(rate), window_(window), fps_(fps) {
	}

public:
	// ���s
	int run() {
		GameDevice device(width_, height_, rate_, window_, fps_);


		LPCSTR font_path = "./resources/file/nikumaru.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		}
		else {
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		}
		ChangeFont("07�ɂ��܂�t�H���g");
		start();
		// �L�[���������܂Ń��[�v���܂�
		while (isRunning()){
			update();
			draw();

			device.flip();
		}
		end();
		if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
		}
		else {
			MessageBox(NULL, "remove failure", "", MB_OK);
		}

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
	virtual bool isRunning() { return (ProcessMessage() == 0 && ClearDrawScreen() == 0 && InputMgr::GetInstance().IsKeyUp(KeyCode::ESCAPE) == 0); }

private:
	// �R�s�[�֎~
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	// �E�B���h�E�̕�
	int width_;
	// �E�B���h�E�̍���
	int height_;
	// �E�C���h�E�̕`��䗦
	float rate_;
	// �E�C���h�E���[�h���H
	int window_;
	// FPS
	float fps_;
};
