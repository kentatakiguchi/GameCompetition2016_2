#include "ActorManager.h"
#include "ActorGroup.h"

#include "../Body/ShapeType.h"

// コンストラクタ
ActorManager::ActorManager() {
	initialize();
}

// 初期化
void ActorManager::initialize() {
	actors_[ActorGroup::Player] = std::make_shared<Actor>("PlayerManager");
	actors_[ActorGroup::Player_AttackRange] = std::make_shared<Actor>();
	actors_[ActorGroup::Enemy] = std::make_shared<Actor>("EnemyManager");
	actors_[ActorGroup::Enemy_AttackRange] = std::make_shared<Actor>();
	actors_[ActorGroup::EnemyBullet] = std::make_shared<Actor>();
	actors_[ActorGroup::Enemy_Spawner] = std::make_shared<Actor>();
	actors_[ActorGroup::Effect] = std::make_shared<Actor>();
	root_.clearChildren();
	root_.addChild(actors_[ActorGroup::Effect]);
	root_.addChild(actors_[ActorGroup::EnemyBullet]);
	root_.addChild(actors_[ActorGroup::Player_AttackRange]);
	root_.addChild(actors_[ActorGroup::Enemy]);
	root_.addChild(actors_[ActorGroup::Enemy_AttackRange]);
	root_.addChild(actors_[ActorGroup::Enemy_Spawner]);
	root_.addChild(actors_[ActorGroup::Player]);
}

// 更新
void ActorManager::update(float deltaTime) {
	root_.update(deltaTime);
	collide();
	root_.removeChildren();
}

// 描画
void ActorManager::draw() const {
	root_.draw();
}

// アクターの追加
void ActorManager::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_[group]->addChild(actor);
}

// アクターの検索
ActorPtr ActorManager::findActor(const std::string& name) {
	return root_.findCildren(name);
}

// メッセージ処理
void ActorManager::handleMessage(EventMessage message, void* param) {
	root_.handleMessage(message, param);
}

// 衝突判定
void ActorManager::collide() {
	//actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy_AttackRange]);
	actors_[ActorGroup::Player_AttackRange]->collideChildren(*actors_[ActorGroup::Enemy]);

}
