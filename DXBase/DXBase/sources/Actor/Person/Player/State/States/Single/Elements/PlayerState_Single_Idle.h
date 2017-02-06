#pragma once

#include "../PlayerState_Single.h"

#include<map>

class PlayerState_Single_Idle : public PlayerState_Single {
public:
	PlayerState_Single_Idle(const Keys& keys);
private:
	virtual void unique_init() override;
	virtual void update(float deltaTime) override;
	virtual void collide(const Actor & other) override;
	virtual void draw()const override;
	virtual void end() override;
	virtual void key_input(float deltaTime) override;
	virtual void pad_input(float deltaTime) override;
private:
	void move(float deltaTime);

	Vector2 target_;

	std::map<int, TextureID> NumIDs;

	TextureID button_R1_;
	TextureID button_L1_;
};

