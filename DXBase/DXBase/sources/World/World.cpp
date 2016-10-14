#include "World.h"
#include "../Field/Field.h"

// �R���X�g���N�^
World::World() :
	listener_([](EventMessage, void*) {}) {
}

// �X�V
void World::update(float deltaTime) {
	//field_->update(deltaTime);
	actors_.update(deltaTime);
	//camera_->update(deltaTime);
	//light_->update(deltaTime);
}

// �`��
void World::draw() const {
	//field_->draw();
	//camera_->draw();
	//light_->draw();
	actors_.draw();
}

// ���b�Z�[�W����
void World::handleMessage(EventMessage message, void* param) {
	// ���[���h�̃��b�Z�[�W����
	listener_(message, param);
	// �A�N�^�[�̃��b�Z�[�W����
	actors_.handleMessage(message, param);
	//camera_->handleMessage(message, param);
	//light_->handleMessage(message, param);
}
 
// �t�B�[���h�̒ǉ�
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// �J�����̒ǉ�
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ���C�g�̒ǉ�
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

// �A�N�^�[�̒ǉ�
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

// �A�N�^�[�̌���
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}

// �t�B�[���h�̎擾
FieldPtr World::getField() const {
	return field_;
}


unsigned int World::fieldHandle() const{
	return field_->modelHandle();
}

// ���b�Z�[�W�̑��M
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// �C�x���g���X�i�[�̒ǉ�
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}


