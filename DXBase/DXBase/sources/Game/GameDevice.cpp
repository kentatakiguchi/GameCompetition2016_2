#include "GameDevice.h"
#include "../Define.h"

GameDevice::GameDevice(int width, int height, float rate, int windowFlag, float fps, int colorBitDepth){
	SetMainWindowText("Game");
	SetGraphMode(width, height, colorBitDepth);
	ChangeWindowMode(windowFlag);
	SetWindowSizeExtendRate(rate);

	//DXLib����������
	if (DxLib_Init() == -1)DxLib_End();//�G���[���N������I��
}

GameDevice::~GameDevice(){}

void GameDevice::flip(){
	SetBackgroundColor(0, 0, 0);
	ScreenFlip();
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_BACK);
}
