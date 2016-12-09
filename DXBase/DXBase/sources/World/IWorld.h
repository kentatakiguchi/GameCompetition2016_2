#ifndef IWORLD_H_
#define IWORLD_H_

#include "../Actor/Base/Actor.h"
#include "../Field/FieldPtr.h"
#include <string>
#include <vector>
enum class ActorGroup;
enum class EventMessage;

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
	virtual Vector2 MoveActor() = 0;
	virtual Vector2 ScroolStopFlag() = 0;
	virtual bool is_clear() = 0;
	virtual void clear(bool clear) = 0;

	//�c�X�N���[�����X�N���[�����邩�ǂ���(���� �����ƂɃX�N���[������ꍇ��1�A���Ȃ��ꍇ��0)
	virtual void SetScroolJudge(Vector2 scrool=Vector2(1,1))=0;
	virtual Vector2 GetScroolJudge()=0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;
};

#endif
