#pragma once

#include "StateMgr.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Base/ActorGroup.h"

class Actor;

class IState {
public:
	// 仮想デストラクタ
	virtual ~IState() {}
	//初期化
	virtual void init(Actor & actor) = 0;
	// 更新
	virtual void update(Actor & actor, float deltaTime) = 0;
	//状態の変更
	virtual void change(unsigned int nextState) = 0;
	// 終了を返す
	virtual bool isEnd() = 0;

	virtual unsigned int next() const = 0;

	virtual void end() = 0;
};
