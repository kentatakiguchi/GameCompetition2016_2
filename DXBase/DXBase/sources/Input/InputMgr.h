#pragma once

#include "KeyCode.h"

#include <unordered_map>
#include <string>
#include"../Math/Vector2.h"

class InputMgr{
private:
	InputMgr();
	~InputMgr();
public:
	static InputMgr& GetInstance();
	//キー入力状態
	int GetHitKeyFrameAll();
	
	void setButton(Buttons targetButton,unsigned int changeButton);

	void RegistKeyCode();

	bool IsKeyDown(KeyCode handle);
	bool IsKeyOn(KeyCode handle);
	bool IsKeyUp(KeyCode handle);
	bool IsButtonDown(Buttons handle);
	bool IsButtonOn(Buttons handle);
	bool IsButtonUp(Buttons handle);

	Vector2 AnalogPadVectorL();
	Vector2 AnalogPadVectorR();
	Vector2 DirectPadVector();
	Vector2 XPadVector();

	Vector2 KeyVector(KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT, KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN);
	Vector2 KeyVector_L(KeyCode right = KeyCode::D, KeyCode left = KeyCode::A, KeyCode up = KeyCode::W, KeyCode down = KeyCode::S);
	Vector2 KeyVector_R(KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT, KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN);

private:
	static const int MAX_KEY_NUM = 256;
	
	unsigned int previous_key_state[MAX_KEY_NUM];
	unsigned int current_key_state[MAX_KEY_NUM];
	unsigned int previous_button_state;
	unsigned int current_button_state;

	//キーコンフィグ用キーデータ
	std::unordered_map<KeyCode, unsigned int> KeyName;
	std::unordered_map<Buttons, unsigned int> ButtonName;
	std::unordered_map<Buttons, KeyCode> ConnectInputName;
};