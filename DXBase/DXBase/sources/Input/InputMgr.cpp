#include "InputMgr.h"
#include "DxLib.h"

InputMgr::InputMgr(){
	RegistKeyCode();
}

InputMgr::~InputMgr(){

}

InputMgr & InputMgr::GetInstance(){
	static InputMgr instance;
	return instance;
}

int InputMgr::GetHitKeyFrameAll()
{
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);

	for (int i = 0; i < MAX_KEY_NUM; i++) {
		if (GetHitKeyStateAll_Key[i] != 0) {
			previous_key_state[i] = current_key_state[i];
			current_key_state[i]++;
		}
		else current_key_state[i] = 0;
	}
	return 0;
}

void InputMgr::RegistKeyCode(){
	KeyName[KeyCode::UP]	 = KEY_INPUT_UP;
	KeyName[KeyCode::DOWN]	 = KEY_INPUT_DOWN;
	KeyName[KeyCode::RIGHT]  = KEY_INPUT_RIGHT;
	KeyName[KeyCode::LEFT]	 = KEY_INPUT_LEFT;
	KeyName[KeyCode::ESCAPE] = KEY_INPUT_ESCAPE;
	KeyName[KeyCode::SPACE]  = KEY_INPUT_SPACE;
	KeyName[KeyCode::RETURN] = KEY_INPUT_RETURN;
	KeyName[KeyCode::A] = KEY_INPUT_A;
	KeyName[KeyCode::B] = KEY_INPUT_B;
	KeyName[KeyCode::C] = KEY_INPUT_C;
	KeyName[KeyCode::D] = KEY_INPUT_D;
	KeyName[KeyCode::E] = KEY_INPUT_E;
	KeyName[KeyCode::F] = KEY_INPUT_F;
	KeyName[KeyCode::G] = KEY_INPUT_G;
	KeyName[KeyCode::H] = KEY_INPUT_H;
	KeyName[KeyCode::I] = KEY_INPUT_I;
	KeyName[KeyCode::J] = KEY_INPUT_J;
	KeyName[KeyCode::K] = KEY_INPUT_K;
	KeyName[KeyCode::L] = KEY_INPUT_L;
	KeyName[KeyCode::M] = KEY_INPUT_M;
	KeyName[KeyCode::N] = KEY_INPUT_N;
	KeyName[KeyCode::O] = KEY_INPUT_O;
	KeyName[KeyCode::P] = KEY_INPUT_P;
	KeyName[KeyCode::Q] = KEY_INPUT_Q;
	KeyName[KeyCode::R] = KEY_INPUT_R;
	KeyName[KeyCode::S] = KEY_INPUT_S;
	KeyName[KeyCode::T] = KEY_INPUT_T;
	KeyName[KeyCode::U] = KEY_INPUT_U;
	KeyName[KeyCode::V] = KEY_INPUT_V;
	KeyName[KeyCode::W] = KEY_INPUT_W;
	KeyName[KeyCode::X] = KEY_INPUT_X;
	KeyName[KeyCode::Y] = KEY_INPUT_Y;
	KeyName[KeyCode::Z] = KEY_INPUT_Z;
	KeyName[KeyCode::L_SHIFT] = KEY_INPUT_LSHIFT;
	KeyName[KeyCode::R_SHIFT] = KEY_INPUT_RSHIFT;

}

bool InputMgr::IsKeyDown(KeyCode handle)
{
	if (previous_key_state[KeyName[handle]] == 0 && current_key_state[KeyName[handle]] == 1)return true;
	return false;
}

bool InputMgr::IsKeyOn(KeyCode handle)
{
	if (previous_key_state[KeyName[handle]] != 0 && current_key_state[KeyName[handle]] != 0)return true;
	return false;
}

bool InputMgr::IsKeyUp(KeyCode handle)
{
	if (previous_key_state[KeyName[handle]] != 0 && current_key_state[KeyName[handle]] == 0)return true;
	return false;
}

bool InputMgr::IsMoving(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (IsKeyDown(up) || IsKeyDown(down) || IsKeyDown(right) || IsKeyDown(left)) {
		return true;
	}
	return false;
}

bool InputMgr::IsStoped(KeyCode up, KeyCode down, KeyCode right, KeyCode left){
	if (!IsKeyOn(up) && !IsKeyOn(down) && !IsKeyOn(right) && !IsKeyOn(left)) {
		return true;
	}
	return false;
}
