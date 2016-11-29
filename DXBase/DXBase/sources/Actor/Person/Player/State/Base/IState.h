#pragma once

//#include "StateMgr.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Base/ActorGroup.h"
#include "ActionType.h"

class Actor;

class IState {
public:
	// �X�e�[�g�̗v�f
	struct StateElement {
		int state_;
		ActionType action_type_;

		// �R���X�g���N�^
		StateElement(int state, ActionType action_type = ActionType::None){
			state_ = state;
			action_type_ = action_type;
		}
	};

public:
	// ���z�f�X�g���N�^
	virtual ~IState() {}
	// �S��ԋ��ʂ̏�����
	virtual void common_init(Actor& actor, ActionType type = ActionType::None) = 0;
	// �e��ԓƎ��̏�����
	virtual void unique_init() = 0;
	// ���͏���
	virtual void input() = 0;
	// �X�V����
	virtual void update(float deltaTime) = 0;
	// ��Ԃ̕ύX
	virtual void change(StateElement element) = 0;
	// �I����Ԃ�
	virtual bool isEnd() = 0;
	// ���̃X�e�[�g�̗v�f
	virtual StateElement next() const = 0;
	// �I�����̏���
	virtual void end() = 0;
};
