#include "Actor.h"
#include <algorithm>
#include "../TestPlayer/TestPlayer.h"
#include "../../Input/KeyCode.h"
#include "../../Math/MathHelper.h"
// �R���X�g���N�^
Actor::Actor(IWorld* world, const std::string& name, const Vector3& position, const CollisionBase& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	animation_(-1),
	alpha_(0.0f),
	outPlayerFlag(false),
	resPos(Vector2::Zero),
	veloPlus(Vector2::Zero),
	velo(Vector2::Zero) {
		body_.setPosition({ position_.x, position_.y });
}

// �R���X�g���N�^
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f, 0.0f),
	rotation_(Matrix::Identity),
	dead_(false),
	animation_(-1) {

}


// �X�V
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });
	//�ړ�update
	ActorMove();
}

void Actor::late_update(float deltaTime){
	onLateUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.late_update(deltaTime); });
}

// �`��
void Actor::draw() const {
	onDraw();
	eachChildren([&](const Actor& child) { child.draw(); });
}


// �Փ˔���
void Actor::collide(Actor& other) {
	if (isCollide(other)) {
		onCollide(other);
		other.onCollide(*this);
	}
	eachChildren([&](Actor& child) { child.collide(other); });
}


// ���S���Ă��邩�H
bool Actor::isDead() const {
	return dead_;
}

// ���S����
void Actor::dead() {
	dead_ = true;
}

// ���O��Ԃ�
const std::string& Actor::getName() const {
	return name_;
}

// ���W��Ԃ�
Vector3 Actor::getPosition() const {
	return position_;
}

// ��]�s���Ԃ�
Matrix Actor::getRotate() const {
	return rotation_;
}

// �ϊ��s���Ԃ�
Matrix Actor::getPose() const {
	return Matrix(rotation_).Translation(position_);
}

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// �q�̌���
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

// �q�̏Փ˔���
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// �q�̏Փ˔���
void Actor::collideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->collide(*actor); });
	}
}

// �q�̒ǉ�
void Actor::addChild(const ActorPtr& child) {
	children_.push_front(child);
}

// �q������
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q������ (const�Łj
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q���폜
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// �q���폜
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

// �q������
void Actor::clearChildren() {
	children_.clear();
}

void Actor::setMotion(const unsigned int motion) {
	motion_ = motion;
}

void Actor::setTransform(Vector3 pos, Matrix rot) {
	position_ = pos;
	rotation_ = rot;
}

IWorld* Actor::getWorld() {
	return world_;
}

Animation Actor::getAnim() {
	return animation_;
}

CollisionBase Actor::getBody()
{
	return body_;
}

// ���b�Z�[�W����
void Actor::handleMessage(EventMessage message, void* param) {
	onMessage(message, param);
	eachChildren([&](Actor& child) { child.handleMessage(message, param); });
}

// ���b�Z�[�W����
void Actor::onMessage(EventMessage, void*) {}

// �X�V
void Actor::onUpdate(float) {}

void Actor::onLateUpdate(float deltaTime)
{
}

// �`��
void Actor::onDraw() const {
	body_.draw(); // �f�o�b�O�\��
}

// �Փ˂���
void Actor::onCollide(Actor&) {
	body_.draw();
	//dead();
}

// �Փ˔���
bool Actor::isCollide(Actor& other) {
	body_.MovePos(Vector2( position_.x,position_.y ));
	other.body_.MovePos(Vector2(other.position_.x, other.position_.y));
	return body_.intersects(other.body_);
}
//�A�N�^�[��S���v���C���[�Ɠ���������
void Actor::ActorMove()
{
	//�t���O������
	moveFlag = Vector2::Zero;
	//world�������ĂȂ������烊�^�[��
	if (world_ == nullptr) return;
	//�v���C���[�̍��W���擾
	Vector2 player =
		Vector2(world_->findActor("Player")->getPosition().x, world_->findActor("Player")->getPosition().y);
	//�v���C���[�ň��͈̔͊O�ɍs�����獡�̑��x�Ƌt�̑��x�𑫂��Ă�����
	if (getName() == "Player")
	{
		//x��
		if ((int)player.x != 800 / 2)
		{
			resPos.x = world_->MoveActor().x;
			//x���ړ����Ă܂�
			moveFlag.x = 1;
		}
		//Y��
		if ((int)player.y != 600 / 2)
		{
			resPos.y = world_->MoveActor().y;
			//y���ړ����Ă܂�
			moveFlag.y = 1;
		}
	}
	//�v���C���[�ȊO�̓���
	else
	{
		//x��
		if ((int)player.x != 800 / 2)
		{
			resPos.x = world_->MoveActor().x;
		}
		//Y��
		if ((int)player.y != 600 / 2)
		{
			resPos.y = world_->MoveActor().y;
		}
	}
	//��ԏ���
	MathHelper::Spring(veloPlus.x, resPos.x, velo.x, 0.1f, 0.5f, 2.0f);
	MathHelper::Spring(veloPlus.y, resPos.y, velo.y, 0.1f, 0.5f, 2.0f);
	position_ += Vector3(veloPlus.x,veloPlus.y,0.0f);
}

// end of file
