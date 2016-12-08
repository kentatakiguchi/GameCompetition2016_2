#ifndef ACTOR_H_
#define ACTOR_H_

#include "DxLib.h"

#include "ActorPtr.h"
#include "../../Input/InputMgr.h"
#include "../../Math/Math.h"
#include "../Body/Body.h"
#include "../Body/BoundingBox.h"
#include "../Body/BoundingCapsule.h"
#include "../Body/BoundingCircle.h"
#include "../Body/BoundingSegment.h"
#include"..//Body/CollisionBase.h"
#include "../../Animation/Base/Animation.h"
#include "../../Define.h"
#include <string>
#include <memory>
#include <functional>
#include <forward_list>

class IWorld;

enum class EventMessage;

class Actor {
public:
	// �R���X�g���N�^
	Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body);
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
	// ��]�s���Ԃ�
	Matrix getRotate() const;
	// �ϊ��s���Ԃ�
	Matrix getPose() const;

	Matrix inv();
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
	// ���[�V�����̐ݒ�
	void setMotion(unsigned int motion);
	// Transform�̐ݒ�
	void setTransform(Vector2 pos, Matrix rot);
	// World�̎擾
	IWorld* getWorld();
	// �A�j���[�V�����̎擾
	Animation getAnim();
	//Body�̎擾 return:CollisionBase
	CollisionBase getBody();

	// ���b�Z�[�W����
	void handleMessage(EventMessage message, void* param);
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
public:
	// �Փ˔���
	bool isCollide(Actor& other);
	void translate(Vector2& position) {
		body_.translate(position);
	}

private:
	void Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness=0.1f, float friction=0.5f, float mass=2.0f)const;

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
	// ���f���n���h��
	unsigned int		modelHandle_;
	
	Animation			animation_;
	// ���[�V����ID
	unsigned int		motion_;

	float				alpha_;

	Matrix inv_;
	Matrix resInv_;
	//�␳���ꂽ���x
	Vector2 mVelo;
private:
	// �q�A�N�^�[
	std::forward_list<ActorPtr> children_;
	//�␳�p���x
	Vector2 velo;
	//1�t���[���O
	Vector2 mPrePos;
	//1�t���[����
	Vector2 mCurPos;

};

#endif
