#ifndef ACTORUI_H_
#define ACTORUI_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "../../Math/Math.h"

class IWorld;

enum class EventMessage;

class ActorUI {
public:
	// �R���X�g���N�^
	ActorUI(IWorld* world, const Vector2& position);
	// ���z�f�X�g���N�^
	virtual ~ActorUI() {}
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// ���S���Ă��邩�H
	bool isDead() const;
	// ���S����
	void dead();

	// �R�s�[�֎~
	ActorUI(const ActorUI& other) = delete;
	ActorUI& operator = (const ActorUI& other) = delete;

private:
	// �X�V
	virtual void onUpdate(float deltaTime);
	// �`��
	virtual void onDraw() const;
public:
	// ���[���h
	IWorld*				world_;
	// ���W
	Vector2				position_;
	// ���S�t���O
	bool				dead_;

	float				alpha_;
};

#endif