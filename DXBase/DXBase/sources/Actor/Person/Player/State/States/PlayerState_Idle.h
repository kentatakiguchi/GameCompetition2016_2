#pragma once

#include "../Base/IState.h"
#include "../Player_EnumState.h"

class PlayerState_Idle : public IState {
public:
	enum class MOTION {
		WALK1,
		WALK2
	};
public:
	PlayerState_Idle();

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