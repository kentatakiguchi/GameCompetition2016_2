#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>
#include <vector>

enum class EventMessage;

class World : public IWorld {
public:
	// �R���X�g���N�^
	World();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �t�B�[���h�̒ǉ�
	void addField(const FieldPtr& field);
	// �J�����̒ǉ�
	void addCamera(const ActorPtr& camera);
	// ���C�g�̒ǉ�
	void addLight(const ActorPtr& light);

	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) override;
	//UI�A�N�^�[�̒ǉ�
	virtual void addUIActor(const ActorUIPtr& actor) override;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) override;
	//�A�N�^�[�̌���(list�Ԃ�)
	virtual std::forward_list<ActorPtr>findActors(const ActorGroup group) override;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const override;
	virtual unsigned int fieldHandle() const override;

	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr)  override;
	// �C�x���g���X�i�[�̒ǉ�
	void addEventMessageListener(std::function<void(EventMessage, void*)> listener);

	//���x
	virtual Vector2 MoveActor() override;
	//unsigned int fieldHandle();
	virtual Vector2 ScroolStopFlag() override;
	//�N���A����
	virtual bool is_clear()override;
	virtual void clear(bool clear)override;
	virtual void SetScroolJudge(Vector2 scrool = Vector2(1, 1)) override;
	virtual Vector2 GetScroolJudge()override;

	// �R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	// �A�N�^�[�}�l�[�W���[
	ActorManager	actors_;
	// ���C�g
	ActorPtr		light_;
	// �J����
	ActorPtr		camera_;
	// �t�B�[���h
	FieldPtr		field_;
	// �C�x���g���X�i�[
	std::function<void(EventMessage, void*)> listener_;

	bool is_clear_;

	Vector2 scrool_;
};

#endif

