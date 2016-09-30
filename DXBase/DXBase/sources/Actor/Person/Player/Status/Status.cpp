#include "Status.h"

#include <string>

Status::Status(){

}

Status::Status(int maxHP){
	params_.hp = maxHP;
	params_.combo = 0;
}

void Status::addDamage(int damage){
	params_.hp -= damage;
}

void Status::addCombo(){
	params_.combo += 1;
}

void Status::draw()const{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HP : %d COMBO : %d", params_.hp, params_.combo);
}
