#ifndef ACTOR_H_
#define ACTOR_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "../../Input/InputMgr.h"
#include "../../Math/Math.h"
#include "../Body/Body.h"
#include "../Body/BoundingBox.h"
#include "../Body/BoundingCapsule.h"
#include "../Body/BoundingCircle.h"
#include "../Body/BoundingSegment.h"
#include"..//Body/CollisionBase.h"
#include "../../Animation/Base/Animation.h"
#include "../../Define.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class Actor {
public:
	// コンストラクタ
	Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body);
	// コンストラクタ
	explicit Actor(const std::string& name = "none");
	// 仮想デストラクタ
	virtual ~Actor() {}
	// 更新
	void update(float deltaTime);
	// 更新
	void late_update(float deltaTime);
	// 描画
	void draw() const;
	// 衝突処理
	void collide(Actor& other);
	// 死亡しているか？
	bool isDead() const;
	// 死亡する
	void dead();
	// 名前を返す
	const std::string& getName() const;
	// 座標を返す
	Vector2 getPosition() const;
	// 回転行列を返す
	Matrix getRotate() const;
	// 変換行列を返す
	Matrix getPose() const;

	Matrix inv();
	// 子の検索
	ActorPtr findCildren(const std::string& name);
	// 子の検索
	ActorPtr findCildren(std::function<bool (const Actor&)> fn);
	// 子同士の衝突
	void collideChildren(Actor& other);
	// 兄弟同士の衝突判定
	void collideSibling();
	// 子の追加
	void addChild(const ActorPtr& child);
	// 子を巡回
	void eachChildren(std::function<void(Actor&)> fn);
	// 子を巡回(const版)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// 子を削除する
	void removeChildren(std::function <bool(Actor&)> fn);
	// 子を削除する
	void removeChildren();
	// 子を消去
	void clearChildren();
	//子を取得
	std::forward_list<ActorPtr> getChildren();
	// モーションの設定
	void setMotion(unsigned int motion);
	// Transformの設定
	void setTransform(Vector2 pos, Matrix rot);
	// Worldの取得
	IWorld* getWorld();
	// アニメーションの取得
	Animation getAnim();
	//Bodyの取得 return:CollisionBase
	CollisionBase getBody();

	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

private:
	// メッセージ処理
	virtual void onMessage(EventMessage message, void* param);
	// 更新
	virtual void onUpdate(float deltaTime);

	virtual void onLateUpdate(float deltaTime) ;

	// 描画
	virtual void onDraw() const;
	// 衝突した
	virtual void onCollide(Actor& other);
public:
	// 衝突判定
	bool isCollide(Actor& other);
	void translate(Vector2& position) {
		body_.translate(position);
	}

private:
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness=0.1f, float friction=0.5f, float mass=2.0f)const;

public:
	// ワールド
	IWorld*				world_;
	// 名前
	std::string			name_;
	// 座標
	Vector2				position_;
	// 回転
	Matrix				rotation_;
	// 衝突判定
	CollisionBase		body_;
	// 死亡フラグ
	bool				dead_;
	// モデルハンドル
	unsigned int		modelHandle_;
	
	Animation			animation_;
	// モーションID
	unsigned int		motion_;

	float				alpha_;

	Matrix inv_;
	Matrix resInv_;
	//補正された速度
	Vector2 mVelo;
private:
	// 子アクター
	std::forward_list<ActorPtr> children_;
	//補正用速度
	Vector2 velo;
	//1フレーム前
	Vector2 mPrePos;
	//1フレーム後
	Vector2 mCurPos;

};

#endif
