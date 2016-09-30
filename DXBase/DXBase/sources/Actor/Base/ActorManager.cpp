#include "ActorManager.h"
#include "ActorGroup.h"

#include "../Body/ShapeType.h"

// �R���X�g���N�^
ActorManager::ActorManager() {
	initialize();
}

// ������
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

// �X�V
void ActorManager::update(float deltaTime) {
	root_.update(deltaTime);
	collide();
	root_.removeChildren();
}

// �`��
void ActorManager::draw() const {
	root_.draw();
}

// �A�N�^�[�̒ǉ�
void ActorManager::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_[group]->addChild(actor);
}

// �A�N�^�[�̌���
ActorPtr ActorManager::findActor(const std::string& name) {
	return root_.findCildren(name);
}

// ���b�Z�[�W����
void ActorManager::handleMessage(EventMessage message, void* param) {
	root_.handleMessage(message, param);
}

// �Փ˔���
void ActorManager::collide() {
	//actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy]);
	actors_[ActorGroup::Player]->collideChildren(*actors_[ActorGroup::Enemy_AttackRange]);
	actors_[ActorGroup::Player_AttackRange]->collideChildren(*actors_[ActorGroup::Enemy]);

}
