#pragma once

#include "../PlayerState_Union.h"

class PlayerState_Hold : public PlayerState_Union {
public:
	PlayerState_Hold(const PlayerPtr& player);

	virtual void unique_init() override;

	virtual void update(float deltaTime) override;

	virtual void end() override;
private:
	void move();

private:
	void key_update();
	void pad_update();
}; 
