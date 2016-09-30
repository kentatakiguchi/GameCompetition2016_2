#pragma once

#include "StateMgr.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Base/ActorGroup.h"

class Actor;

class IState {
public:
	// ���z�f�X�g���N�^
	virtual ~IState() {}
	//������
	virtual void init(Actor & actor) = 0;
	// �X�V
	virtual void update(Actor & actor, float deltaTime) = 0;
	//��Ԃ̕ύX
	virtual void change(unsigned int nextState) = 0;
	// �I����Ԃ�
	virtual bool isEnd() = 0;

	virtual unsigned int next() const = 0;

	virtual void end() = 0;
};
