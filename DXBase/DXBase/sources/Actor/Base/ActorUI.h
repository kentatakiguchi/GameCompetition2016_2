#ifndef ACTORUI_H_
#define ACTORUI_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "../../Input/InputMgr.h"
#include "../../Math/Math.h"
#include "../../Animation/Base/Animation.h"
#include "../../Define.h"
#include "../../Math/Vector2.h"
#include "../../World/IWorld.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class ActorUI {
public:
	// コンストラクタ
	ActorUI(IWorld* world, const Vector2& position);
	// 仮想デストラクタ
	virtual ~ActorUI() {}
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 死亡しているか？
	bool isDead() const;
	// 死亡する
	void dead();

	// コピー禁止
	ActorUI(const ActorUI& other) = delete;
	ActorUI& operator = (const ActorUI& other) = delete;

private:
	// 更新
	virtual void onUpdate(float deltaTime);
	// 描画
	virtual void onDraw() const;
public:
	// ワールド
	IWorld*				world_;
	// 座標
	Vector2				position_;
	// 死亡フラグ
	bool				dead_;

	float				alpha_;
};

#endif