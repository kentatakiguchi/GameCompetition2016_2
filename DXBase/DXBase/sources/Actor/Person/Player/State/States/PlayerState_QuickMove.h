#pragma once

#include "../Base/IState.h"

class PlayerState_QuickMove : public IState {
public:
	PlayerState_QuickMove();

	// IState ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
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