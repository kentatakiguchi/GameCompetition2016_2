#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/Base/ActorPtr.h"
#include "../Field/FieldPtr.h"
#include <string>
#include <forward_list>

enum class ActorGroup;
enum class EventMessage;

struct Vector2;
struct Matrix;
struct ScroolJudge;

class SceneDataKeeper;

// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	//UI�A�N�^�[�̒ǉ�
	virtual void addUIActor(const ActorUIPtr& actor) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �t�B�[���h�̎擾
	virtual FieldPtr getField() const = 0;
	virtual unsigned int fieldHandle() const = 0;
	//�A�N�^�[�̌���(list�Ԃ�)
	virtual std::forward_list<ActorPtr> findActors(const ActorGroup group) = 0;
	virtual bool is_clear() = 0;
	virtual void clear(bool clear) = 0;
	// �{�X�̌��ɐN����������Ԃ��܂�
	virtual bool isEntered() = 0;
	// �{�X�̌�����E�o��������Ԃ��܂�
	virtual bool isLetOuted() = 0;
	// �{�X�̌��̐N���E�o��ݒ肵�܂�
	virtual void setEntry(const bool isEntry, const bool isLetOut) = 0;
	// �^�C�}���~�܂��Ă��邩��Ԃ��܂�
	virtual bool isStopTime() = 0;
	// �^�C�}��0�ɂ��邩��ݒ肵�܂�
	virtual void setIsStopTime(const bool isTime) = 0;
	// �f���^�^�C�����擾���܂�(���̃^�C���N���X����擾)
	virtual float getDeltaTime() = 0;
	// ���{�X�̃X�e�[�W���ɓ���������ݒ肵�܂�
	virtual void setIsMBossStage(bool isStage) = 0;
	// ���{�X�̃X�e�[�W���ɓ���������Ԃ��܂�
	virtual bool isMBossStage() = 0;
	virtual void SetPlayerPos(Vector2 pos) = 0;
	// �c�X�N���[�����X�N���[�����邩�ǂ���(���� �����ƂɃX�N���[������ꍇ��1�A���Ȃ��ꍇ��0)
	virtual void SetScroolJudge(const Vector2& scroolJudge, const Vector2& scroolMinPos, const Vector2& scroolMaxPos, bool flag = false) =0;
	virtual ScroolJudge GetScroolJudge()=0;
	// �v���C���[�̑���s�\�ɂ��邩�ǂ���
	virtual void PlayerNotMove(bool flag) = 0;
	// �v���C���[�̑���s�\�ɂ��邩�ǂ������擾
	virtual bool GetPlayerNotMove() = 0;
	// ��ʏ�̃v���C���[�̍��W
	virtual Vector2 GetScreenPlayerPos()=0;
	// �f�[�^�L�[�p�[�̎擾
	virtual SceneDataKeeper* GetKeeper() = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
	//
	virtual Vector2 GetPlayerPos() = 0;
	virtual Matrix GetInv() = 0;

	//�S�����蔻���؂邩�ǂ��� true:on false:off
	virtual void CollisitionOffOn(bool col)=0;
	virtual bool GetCollisitionOffOn()=0;

	virtual void inv(const Matrix& mat) = 0;
	//

	//���W���w�肷��Ƃ����ɃX�N���[������i���t���[���ĂԂ��Ɓj
	virtual void SetScroolPos(const Vector2& pos)=0;

	virtual Vector2 GetInvVelo() = 0;
	//
	virtual void SetScreenPlayerPos(const Vector2& screenPos) = 0;
	virtual Matrix InitializeInv(Vector2 position) = 0;

	virtual void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness = 0.1f, float friction = 0.5f, float mass = 2.0f)const = 0;

	virtual void addCount(int i = 1) = 0;
	virtual void setCount(int i) = 0;
	virtual void minusCount() = 0;
	virtual void resetCount() = 0;
	virtual void resetGetCount() = 0;
	virtual int getCount() = 0;
	virtual int getGetCount() = 0;
	virtual std::string getCurrentSceneName() = 0;

};

#endif
