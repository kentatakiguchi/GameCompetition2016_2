#pragma once

#include "KeyCode.h"

#include <unordered_map>
#include <string>

class InputMgr{
private:
	InputMgr();
	~InputMgr();
public:
	static InputMgr& GetInstance();
	//�L�[���͏��
	int GetHitKeyFrameAll();

	void RegistKeyCode();

	bool IsKeyDown(KeyCode handle);
	bool IsKeyOn(KeyCode handle);
	bool IsKeyUp(KeyCode handle);

	bool IsMoving(KeyCode up = KeyCode::UP, KeyCode down = KeyCode::DOWN, KeyCode right = KeyCode::RIGHT, KeyCode left = KeyCode::LEFT);
private:
	static const int MAX_KEY_NUM = 256;
	
	unsigned int previous_key_state[MAX_KEY_NUM];
	unsigned int current_key_state[MAX_KEY_NUM];

	//�L�[�R���t�B�O�p�L�[�f�[�^
	std::unordered_map<KeyCode, unsigned int> KeyName;
};