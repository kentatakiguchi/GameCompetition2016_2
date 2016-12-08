#include "Actor.h"
#include <algorithm>
#include "../TestPlayer/TestPlayer.h"
#include "../../Input/KeyCode.h"
#include "../../Math/MathHelper.h"
// �R���X�g���N�^
Actor::Actor(IWorld* world, const std::string& name, const Vector2& position, const CollisionBase& body) :
	world_(world),
	name_(name),
	position_(position),
	rotation_(Matrix::Identity),
	body_(body),
	dead_(false),
	animation_(-1),
	alpha_(0.0f),
	velo(Vector2::Zero),
	resInv_(Matrix::Identity),
	inv_(Matrix::Identity),
	mPrePos(Vector2::Zero),
	mCurPos(Vector2::Zero),
	mVelo(Vector2::Zero){
	body_.setPosition({ position_.x, position_.y });
}

// �R���X�g���N�^
Actor::Actor(const std::string& name) :
	world_(nullptr),
	name_(name),
	position_(0.0f, 0.0f),
	rotation_(Matrix::Identity),
	dead_(false),
	animation_(-1) {

}


// �X�V
void Actor::update(float deltaTime) {
	onUpdate(deltaTime);
	eachChildren([&](Actor& child) { child.update(deltaTime); });
	//�ړ�update
	//ActorMove();
	body_.MovePos(Vector2(position_.x, position_.y));
}

void Actor::late_update(float deltaTime) {
	body_.MovePos(Vector2(position_.x, position_.y));
	inv();
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
Vector2 Actor::getPosition() const {
	return Vector2(position_.x,position_.y);
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

Matrix Actor::inv() {
	if (world_ == nullptr) return Matrix::Identity;
	auto player = world_->findActor("PlayerBody1");
	if(player == nullptr)return Matrix::Identity;
	//1�t���[���O�̍��W
	mPrePos = Vector2(inv_.Translation().x, inv_.Translation().y);
	//�s���ׂ��ʒu��ݒ�(matrix��)
	resInv_ = Matrix::Invert(player->getPose()) *
		Matrix::CreateTranslation(Vector3(PLAYER_SCREEN_POSITION.x, PLAYER_SCREEN_POSITION.y));
	//�s���ׂ��ʒu��ݒ�
	Vector2 resPos = Vector2(resInv_.Translation().x, resInv_.Translation().y);
	Vector2 pos = Vector2(inv_.Translation().x, inv_.Translation().y);
	Spring(pos, resPos, velo);
	//�␳���ꂽ�ړ��}�g���b�N�X���
	inv_ = Matrix::CreateTranslation(Vector3(pos.x, pos.y));
	//1�t���[����̍��W
	mCurPos = Vector2(inv_.Translation().x, inv_.Translation().y);
	//�ړ��ʂ��v�Z
	mVelo = mPrePos - mCurPos;
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

std::forward_list<ActorPtr> Actor::getChildren()
{
	return children_;
}

void Actor::setMotion(const unsigned int motion) {
	motion_ = motion;
}

void Actor::setTransform(Vector2 pos, Matrix rot) {
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
	body_.draw(inv_); // �f�o�b�O�\��
}

// �Փ˂���
void Actor::onCollide(Actor&) {
	body_.draw(inv_);
	//dead();
}

// �Փ˔���
bool Actor::isCollide(Actor& other) {
	return body_.intersects(other.body_);
}
void Actor::Spring(Vector2& pos ,Vector2& resPos, Vector2& velo,float stiffness, float friction, float mass)const
{
	// �o�l�̐L�ы���v�Z
	Vector2 stretch = (pos- resPos);
	// �o�l�̗͂��v�Z
	Vector2 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector2 acceleration = force / mass;
	// �ړ����x���v�Z
	velo= friction * (velo + acceleration);

	pos = pos + velo;
}


// end of file
