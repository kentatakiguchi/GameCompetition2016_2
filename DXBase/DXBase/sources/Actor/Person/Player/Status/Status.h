#pragma once

#include <DxLib.h>

class Status {
public:
	struct Params{
		int hp;
		int combo;
	};
	Status();
	Status(int maxHP);
	void addDamage(int damage);
	void addCombo();
	void draw() const;
public:
	Params params_;

};