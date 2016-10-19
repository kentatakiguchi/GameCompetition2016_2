#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include "Actor.h"
#include <unordered_map>
#include <list>
enum class ActorGroup;
enum class ShapeType;

class ActorManager {
public:
	// コンストラクタ
	ActorManager();
	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// アクターの追加
	void addActor(ActorGroup group, const ActorPtr& actor);
	// アクターの検索
	ActorPtr findActor(const std::string& name);
	// メッセージ処理
	void handleMessage(EventMessage message, void* param);
	// コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// 衝突判定
	void collide();
private:
	// ルートノード
	Actor root_;
	// アクターグループ
	std::unordered_map<ActorGroup, ActorPtr> actors_;
	//速度
	Vector2 velo;
	//using CollideFunc = std::unordered_map < ShapeType, std::function<bool(Collider&, Collider&)> >;
	//std::unordered_map<ShapeType, CollideFunc> collision;

};

#endif

// end of file
