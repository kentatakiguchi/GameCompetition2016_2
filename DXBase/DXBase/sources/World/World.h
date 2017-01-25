#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>
#include <vector>
#include "../Actor/Base/ActorGroup.h"

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
	//�N���A����
	virtual bool is_clear()override;
	virtual void clear(bool clear)override;
	// �{�X�̌��ɐN����������Ԃ��܂�
	bool isEntered() override;
	// �{�X�̌�����E�o��������Ԃ��܂�
	bool isLetOuted() override;
	// �{�X�̌��̐N���E�o��ݒ肵�܂�
	void setEntry(const bool isEntry, const bool isLetOut) override;
	virtual void SetScroolJudge(const Vector2& scroolJudge, const Vector2& scroolMinPos, const Vector2& scroolMaxPos) override;
	virtual ScroolJudge GetScroolJudge()override;
	virtual void PlayerNotMove(bool flag) override {
		mNoPlayerMove = flag;
	}
	virtual bool GetPlayerNotMove() override {
		return mNoPlayerMove;
	}
	virtual Matrix GetInv()override {
		return inv_;
		//Matrix mat;
		//mat.Translation(Vector3(mPlayerPos.x, mPlayerPos.y,0.0f));
		//return Matrix::Invert(mat) *
		//	Matrix::CreateTranslation(Vector3(PLAYER_SCREEN_POSITION.x, PLAYER_SCREEN_POSITION.y));
	}
	virtual void SetPlayerPos(Vector2 pos) override
	{
		//�z��̏�����
		InitializeInv(pos);
		mPlayerPos = pos;
	}
	virtual Vector2 GetPlayerPos() override
	{
		return mPlayerPos;
	}
	virtual void CollisitionOffOn(bool col) {
		colOffOn_ = col;
	}
	virtual bool GetCollisitionOffOn() {
		return colOffOn_;
	}

	// IWorld ����Čp������܂���
	virtual void inv() override;

	virtual Vector2 GetInvVelo() override {
		return mVelo;
	}

	virtual Matrix InitializeInv(Vector2 position) override;

	virtual void Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness = 0.1f, float friction = 0.5f, float mass = 2.0f) const override;

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

	bool isEntered_, isLetOuted_;

	ScroolJudge scrool_;
	
	Vector2 mPlayerPos;
	
	bool mNoPlayerMove;
	bool colOffOn_;

public:

	Matrix inv_;
	Matrix resInv_;
	//�␳���ꂽ���x
	Vector2 mVelo;

	//�␳�p���x
	Vector2 velo;
	//1�t���[���O
	Vector2 mPrePos;
	//1�t���[����
	Vector2 mCurPos;
	

};

#endif

