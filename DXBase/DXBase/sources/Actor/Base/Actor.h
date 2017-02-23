#ifndef ACTOR_H_
#define ACTOR_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "HitOpponent.h"
#include "../../Field/FieldPtr.h"
#include "../../Math/Math.h"
#include "../Body/BoundingBox.h"
#include "../Body/BoundingCapsule.h"
#include "../Body/BoundingCircle.h"
#include "../Body/BoundingSegment.h"
#include "../Body/CollisionBase.h"
#include <string>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class Actor {
public:
	// �R���X�g���N�^
	Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body = CollisionBase());
	// �R���X�g���N�^
	explicit Actor(const std::string& name = "none");
	// ���z�f�X�g���N�^
	virtual ~Actor() {}
	// �X�V
	void update(float deltaTime);
	// �X�V
	void late_update(float deltaTime);
	// �`��
	void draw() const;
	// �Փˏ���
	void collide(Actor& other);
	// ���S���Ă��邩�H
	bool isDead() const;
	// ���S����
	void dead();
	// ���O��Ԃ�
	const std::string& getName() const;
	// ���W��Ԃ�
	Vector2 getPosition() const;
	// ���W���擾
	Vector2& position();
	// ��]�s���Ԃ�
	Matrix getRotate() const;
	// �ϊ��s���Ԃ�
	Matrix getPose() const;
	// �q�̌���
	ActorPtr findCildren(const std::string& name);
	// �q�̌���
	ActorPtr findCildren(std::function<bool (const Actor&)> fn);
	// �q���m�̏Փ�
	void collideChildren(Actor& other);
	// �Z�퓯�m�̏Փ˔���
	void collideSibling();
	// �q�̒ǉ�
	void addChild(const ActorPtr& child);
	// �q������
	void eachChildren(std::function<void(Actor&)> fn);
	// �q������(const��)
	void eachChildren(std::function<void(const Actor&)> fn) const;
	// �q���폜����
	void removeChildren(std::function <bool(Actor&)> fn);
	// �q���폜����
	void removeChildren();
	// �q������
	void clearChildren();
	//�q���擾
	std::forward_list<ActorPtr> getChildren();
	// Transform�̐ݒ�
	void setTransform(Vector2 pos, Matrix rot);
	// World�̎擾
	IWorld* getWorld();
	//Body�̎擾 return:CollisionBase
	CollisionBase getBody();
	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
	// �ՓˑΏۂ̎擾
	HitOpponent getOpponent()const;
	// �R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;
private:
	// ���b�Z�[�W����
	virtual void onMessage(EventMessage message, void* param);
	// �X�V
	virtual void onUpdate(float deltaTime);

	virtual void onLateUpdate(float deltaTime) ;

	// �`��
	virtual void onDraw() const;
	// �Փ˂���
	virtual void onCollide(Actor& other);
	// �Փ˂���
	virtual void hitField(const FieldPtr& field);
public:
	// �Փ˔���
	bool isCollide(Actor& other);
	void translate(Vector2& position);
public:
	// ���[���h
	IWorld*				world_;
	// ���O
	std::string			name_;
	// ���W
	Vector2				position_;
	// ��]
	Matrix				rotation_;
	// �Փ˔���
	CollisionBase		body_;
	// ���S�t���O
	bool				dead_;

	float				alpha_;

	Matrix inv_;

	HitOpponent opponent_;

private:
	// �q�A�N�^�[
	std::forward_list<ActorPtr> children_;
};

#endif
