#include "Actor.h"
#include <algorithm>
#include "../TestPlayer/TestPlayer.h"
#include "../../Input/KeyCode.h"
#include "../../Math/MathHelper.h"
#include "../../Define.h"
// �R���X�g���N�^
Actor::Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	alpha_(0.0f){
	inv_ = world_->GetInv();
	//inv_ = Matrix::Identity;
	//if(world->findActor("Player")==nullptr)
	//	InitializeInv(world_->GetPlayerPos());
	//else
	//	InitializeInv(world->findActor("Player").get()->getPosition());
	body_.setPosition({ position_.x, position_.y });
}

// �R���X�g���N�^
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f),
	rotation_(Matrix::Identity),
	dead_(false) {
}


// �X�V
void Actor::update(float deltaTime) {
	if (world_ != nullptr) body_.enabled(world_->GetCollisitionOffOn());
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });
	//�ړ�update
	//ActorMove();
	body_.MovePos(position_);
}

void Actor::late_update(float deltaTime) {
	//body_.MovePos(position_);
	//inv();
	if (world_ != nullptr)inv_ = world_->GetInv();
	onLateUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.late_update(deltaTime); });
	body_.MovePos(position_);
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
Vector2 Actor::getPosition() const {
	return position_;
}

Vector2 & Actor::position(){
	return position_;
}

// ��]�s���Ԃ�
Matrix Actor::getRotate() const {
	return rotation_;
}

// �ϊ��s���Ԃ�
Matrix Actor::getPose() const {
	return Matrix().Translation(Vector3(position_.x, position_.y));
	//return Matrix(rotation_).Translation(Vector3(position_.x, position_.y));
}

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren([&](const Actor& actor) { return actor.getName() == name; });
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

std::forward_list<ActorPtr> Actor::getChildren(){
	return children_;
}

void Actor::setMotion(const unsigned int motion) {
	motion_ = motion;
}

void Actor::setTransform(Vector2 pos, Matrix rot) {
	position_ = pos;
	rotation_ = rot;
}

bool Actor::isOutOfRange()const {
	auto player = world_->findActor("Player");
	if (player == nullptr)return true;
	float dis = Vector2::Distance(player->getPosition(), position_);
	if (dis > SCREEN_SIZE.x)return true;
	return false;
}

IWorld* Actor::getWorld() {
	return world_;
}

CollisionBase Actor::getBody(){
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

void Actor::onLateUpdate(float deltaTime){}

// �`��
void Actor::onDraw() const {
	//body_.draw(inv_); // �f�o�b�O�\��
}

// �Փ˂���
void Actor::onCollide(Actor&) {
	//body_.draw(inv_);
	//dead();
}

// �Փ˔���
bool Actor::isCollide(Actor& other) {
	return body_.intersects(other.body_);
}
//void Actor::Spring(Vector2& pos, Vector2& resPos, Vector2& velo, float stiffness, float friction, float mass)const
//{
//	// �o�l�̐L�ы���v�Z
//	Vector2 stretch = (pos - resPos);
//	// �o�l�̗͂��v�Z
//	Vector2 force = -stiffness * stretch;
//	// �����x��ǉ�
//	Vector2 acceleration = force / mass;
//	// �ړ����x���v�Z
//	velo = friction * (velo + acceleration);
//
//	pos = pos + velo;
//}


// end of file
