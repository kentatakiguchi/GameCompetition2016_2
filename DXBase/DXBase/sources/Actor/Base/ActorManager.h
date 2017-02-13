#ifndef ACTOR_MANAGER_H_
#define ACTOR_MANAGER_H_

#include "Actor.h"
#include "ActorUI.h"

#include "ActorPtr.h"

#include <unordered_map>
#include <list>

enum class ActorGroup;
enum class ShapeType;

class ActorManager {
public:
	// �R���X�g���N�^
	ActorManager();
	// ������
	void initialize();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �A�N�^�[�̒ǉ�
	void addActor(ActorGroup group, const ActorPtr& actor);
	//UI�A�N�^�[�̒ǉ�
	void addUIActor(const ActorUIPtr & actor);
	// �A�N�^�[�̌���
	ActorPtr findActor(const std::string& name);
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	//�A�N�^�[���O���[�v�Ŏ擾
	std::forward_list<ActorPtr> GetActors(const ActorGroup group);
	// �R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	// �Փ˔���
	void collide();

	void UiUpdate(float delta);
	void UIDraw()const;
private:
	// ���[�g�m�[�h
	Actor root_;
	// �A�N�^�[�O���[�v
	std::unordered_map<ActorGroup, ActorPtr> actors_;
	//UI�A�N�^�[
	std::list<ActorUIPtr> uiActors_;
};

#endif

// end of file
