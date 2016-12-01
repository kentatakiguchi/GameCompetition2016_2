#include "GameDevice.h"
#include "../Define.h"

GameDevice::GameDevice(int width, int height, float rate, int windowFlag, float fps, int colorBitDepth){
	SetMainWindowText("Game");
	SetGraphMode(width, height, colorBitDepth);
	ChangeWindowMode(windowFlag);
	SetWindowSizeExtendRate(rate);

	//DXLib初期化処理
	if (DxLib_Init() == -1)DxLib_End();//エラーが起きたら終了
}

GameDevice::~GameDevice(){}

void GameDevice::flip(){
	SetBackgroundColor(0, 0, 0);
	ScreenFlip();
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_BACK);
}
