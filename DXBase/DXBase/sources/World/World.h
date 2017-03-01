#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ScrollJudge.h"
#include "../Actor/Base/ActorManager.h"
#include "../Scene/Base/SceneDataKeeper.h"

enum class EventMessage;

class World : public IWorld {
public:
	// �R���X�g���N�^
	World(SceneDataKeeper* keeper);
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
	// �^�C�}���~�܂��Ă��邩��Ԃ��܂�
	bool isStopTime() override;
	// �^�C�}��0�ɂ��邩��ݒ肵�܂�
	void setIsStopTime(const bool isTime) override;
	// �f���^�^�C�����擾���܂�(���̃^�C���N���X����擾)
	float getDeltaTime() override;
	// ���{�X�̃X�e�[�W���ɓ���������ݒ肵�܂�
	void setIsMBossStage(bool isStage) override;
	// ���{�X�̃X�e�[�W���ɓ���������Ԃ��܂�
	bool isMBossStage() override;
	virtual void SetScroolJudge(const Vector2& scroolJudge, const Vector2& scroolMinPos, const Vector2& scroolMaxPos,bool flag=false) override;
	virtual Vector2 GetScreenPlayerPos() override
	{
		return playerScreenPos_;
	}
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
	virtual void inv(const Matrix& mat) override;

	virtual Vector2 GetInvVelo() override {
		return mVelo;
	}
	//�X�N���[����̃v���C���[�̕\���ʒu
	virtual void SetScreenPlayerPos(const Vector2& screenPos) override {
		playerScreenPos_ = screenPos;
	}

	virtual Matrix InitializeInv(Vector2 position) override;
	////���W���w�肷��Ƃ����ɃX�N���[������i���t���[���ĂԂ��Ɓj
	virtual void SetScroolPos(const Vector2& pos) override;
	virtual void Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness = 0.1f, float friction = 0.5f, float mass = 2.0f) const override;

	// �R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

	virtual void addCount(int i = 1)override {
		itemCount_ += i;
		getCount_ += i;
		itemCount_ = max(itemCount_, 0);
		getCount_ = max(getCount_, 0);
	}
	virtual void setCount(int i)override {
		itemCount_ = i;
	}
	virtual void minusCount()override {
		itemCount_ -= getCount_;
	}
	virtual void resetCount()override {
		itemCount_ = 0;
		getCount_ = 0;
	}
	virtual void resetGetCount()override {
		getCount_ = 0;
	}
	virtual int getCount()override {
		return itemCount_;
	}
	virtual int getGetCount()override {
		return getCount_;
	}
	virtual SceneDataKeeper* GetKeeper()override {
		return keeper_;
	}
	virtual std::string getCurrentSceneName() override{
		return currentSceneName_;
	}

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
	// ���ɏo���肵����
	bool isEntered_, isLetOuted_;
	// ���Ԃ��~�߂邩
	bool isStopTime_;
	// ���{�X�̃X�e�[�W����
	bool isMBossStage_;
	// ���݂̎���
	float deltaTime_;

	ScroolJudge scrool_;
	
	Vector2 mPlayerPos;
	
	bool mNoPlayerMove;
	bool colOffOn_;

	Vector2 playerScreenPos_;

	int itemCount_;
	int getCount_;

public:

	Matrix inv_;
	Matrix resInv_;
	//�v���C���[�̃}�g���N�X
	Matrix playerMat_;

	//�␳���ꂽ���x
	Vector2 mVelo;

	//�␳�p���x
	Vector2 velo;
	//1�t���[���O
	Vector2 mPrePos;
	//1�t���[����
	Vector2 mCurPos;
	
	SceneDataKeeper* keeper_;

	std::string currentSceneName_;
};

#endif

