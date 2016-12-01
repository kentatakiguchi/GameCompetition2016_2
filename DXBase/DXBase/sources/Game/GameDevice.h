#ifndef _GAME_DEVICE_H_
#define _GAME_DEVICE_H_

#include "DxLib.h"

class GameDevice{
public:
	GameDevice(int width, int height, float rate, int windowFlag, float fps, int colorBitDepth = 32);
	~GameDevice();
	//�o�b�t�@���t���b�v
	void flip();
private:
	// �R�s�[�֎~
	GameDevice(const GameDevice& other) = delete;
	GameDevice& operator = (const GameDevice& other) = delete;
};

#endif