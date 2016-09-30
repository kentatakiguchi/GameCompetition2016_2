#pragma once

#include "../Base/IState.h"

class PlayerState_Damage : public IState {
public:
	PlayerState_Damage();

	// IState ����Čp������܂���
	virtual void init(Actor & actor) override;

	virtual void update(Actor & actor, float deltaTime) override;

	virtual void change(unsigned int nextState) override;

	virtual bool isEnd() override;

	virtual unsigned int next() const override;

	virtual void end() override;
private:
	unsigned int nextState_;
	bool isEndRequest;
};