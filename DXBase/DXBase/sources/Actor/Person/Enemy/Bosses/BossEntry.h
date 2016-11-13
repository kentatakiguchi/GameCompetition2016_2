#ifndef BOSS_ENTRY_H_
#define BOSS_ENTRY_H_

#include "../../../Base/Actor.h"

// ボスの侵入口クラス
class BossEntry : public Actor {
public:
	BossEntry(IWorld* world, const Vector2&  position, const Vector2& addPosition, const float bodyScale);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& actor) override;
	void onMessage(EventMessage event, void*) override;

public:
	// 位置の設定をします
	void setBossPosition(const Vector2& position);
	// 方向を設定します
	void setDirection(const Vector2& direction);
	// ボスの体内に入れるかを設定します
	void setIsEntry(bool isEntry);
	// ボスの体内に入ったかを返します
	bool isEntered();
	// プレイヤーがボスの体内に出たことにします
	void letOut();

private:
	bool isEntry_;			// 体内に入れるか
	bool isEntered_;		// 体内に入ったか
	Vector2 direction_;		// 方向
	Vector2 bossPosition_;	// ボスの位置
	Vector2 addPosition_;	// 追加位置
};

#endif