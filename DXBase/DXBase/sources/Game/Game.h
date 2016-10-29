#pragma once

#include "DxLib.h"
#include "Time.h"
#include "../Input/InputMgr.h"

class Game{
protected:
	// コンストラクタ
	Game(int width = 800, int height = 600, float rate = 1.0f, int window = TRUE, float fps = 60.0f):
		width_(width), height_(height), rate_(rate), window_(window), fps_(fps) {
	}

public:
	// 実行
	int run() {
		ChangeWindowMode(window_);
		
		SetGraphMode(width_, height_, 32);
		SetWindowSizeExtendRate(rate_);
		//DXLib初期化処理
		if (DxLib_Init() == -1)return -1;//エラーが起きたら終了

		start();

		// キーが押されるまでループします
		while (isRunning()){
			// 画面をクリア
			ClearDrawScreen();

			Time::GetInstance().update();
			InputMgr::GetInstance().GetHitKeyFrameAll();			
			update();
			draw();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();

		}

		end();

		DxLib_End();	//DXLib使用終了処理

		return 0;	//ソフト終了
	}

private:
	// 開始
	virtual void start() {}
	// 更新
	virtual void update() {}
	// 描画
	virtual void draw() {}
	// 終了
	virtual void end() {}
	// 実行中か
	virtual bool isRunning() { return (ProcessMessage() == 0 && InputMgr::GetInstance().IsKeyUp(KeyCode::ESCAPE) == 0); }

private:
	// コピー禁止
	Game(const Game& other) = delete;
	Game& operator = (const Game& other) = delete;

private:
	// ウィンドウの幅
	int width_;
	// ウィンドウの高さ
	int height_;
	// ウインドウの描画比率
	float rate_;
	// ウインドウモードか？
	int window_;
	// FPS
	float fps_;
};
