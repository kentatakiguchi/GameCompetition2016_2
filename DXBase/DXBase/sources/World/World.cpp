#include "World.h"

#include "../Field/Field.h"
#include "../Define.h"

// �R���X�g���N�^
World::World(SceneDataKeeper* keeper) :
	listener_([](EventMessage, void*) {}),
	deltaTime_(0.0f),
	is_clear_(false),
	isEntered_(false),
	isLetOuted_(false),
	isStopTime_(false),
	isMBossStage_(false),
	mNoPlayerMove(false),itemCount_(0),getCount_(0),
	playerScreenPos_(PLAYER_SCREEN_POSITION),
	keeper_(keeper){
}

// �X�V
void World::update(float deltaTime) {
	//field_->update(deltaTime);
	auto player = findActor("Player");
	if (player != nullptr) {
		inv(playerMat_);
		playerMat_ = player->getPose();
	}
	deltaTime_ = deltaTime;
	if (isStopTime_) deltaTime = 0.0f;
	actors_.update(deltaTime);

	//camera_->update(deltaTime);
	//light_->update(deltaTime);
}

// �`��
void World::draw() const {
	field_->draw(inv_);
	//camera_->draw();
	//light_->draw();
	actors_.draw();
}

// ���b�Z�[�W����
void World::handleMessage(EventMessage message, void* param) {
	// ���[���h�̃��b�Z�[�W����
	listener_(message, param);
	// �A�N�^�[�̃��b�Z�[�W����
	actors_.handleMessage(message, param);
	//camera_->handleMessage(message, param);
	//light_->handleMessage(message, param);
}

// �t�B�[���h�̒ǉ�
void World::addField(const FieldPtr& field) {
	field_ = field;
}

// �J�����̒ǉ�
void World::addCamera(const ActorPtr& camera) {
	camera_ = camera;
}

// ���C�g�̒ǉ�
void World::addLight(const ActorPtr& light) {
	light_ = light;
}

// �A�N�^�[�̒ǉ�
void World::addActor(ActorGroup group, const ActorPtr& actor) {
	actors_.addActor(group, actor);
}

void World::addUIActor(const ActorUIPtr & actor)
{
	actors_.addUIActor(actor);
}
// �A�N�^�[�̌���
ActorPtr World::findActor(const std::string& name) {
	return actors_.findActor(name);
}
//�A�N�^�[����(list�Ԃ�)
std::forward_list<ActorPtr> World::findActors(const ActorGroup group)
{
	return actors_.GetActors(group);
}

// �t�B�[���h�̎擾
FieldPtr World::getField() const {
	return field_;
}


unsigned int World::fieldHandle() const {
	return field_->modelHandle();
}

// ���b�Z�[�W�̑��M
void World::sendMessage(EventMessage message, void* param) {
	handleMessage(message, param);
}

// �C�x���g���X�i�[�̒ǉ�
void World::addEventMessageListener(
	std::function<void(EventMessage, void*)> listener) {
	listener_ = listener;
}

bool World::is_clear() {
	return is_clear_;
}

void World::clear(bool clear) {
	is_clear_ = clear;
}

// �{�X�̌��ɓ���������Ԃ��܂�
bool World::isEntered()
{
	return isEntered_;
}

// �{�X�̌�����E�o��������Ԃ��܂�
bool World::isLetOuted()
{
	return isLetOuted_;
}

// �{�X�̌��̐N���E�o��ݒ肵�܂�
void World::setEntry(const bool isEntry, const bool isLetOut)
{
	isEntered_ = isEntry;
	isLetOuted_ = isLetOut;
}

// �^�C�}���~�܂��Ă��邩��Ԃ��܂�
bool World::isStopTime()
{
	return isStopTime_;
}

// �^�C�}��0�ɂ��邩��ݒ肵�܂�
void World::setIsStopTime(const bool isTime)
{
	isStopTime_ = isTime;
}

// �f���^�^�C�����擾���܂�(���̃^�C���N���X����擾)
float World::getDeltaTime()
{
	return deltaTime_;
}

// ���{�X�̃X�e�[�W���ɓ���������ݒ肵�܂�
void World::setIsMBossStage(bool isStage)
{
	isMBossStage_ = isStage;
}

bool World::isMBossStage()
{
	return isMBossStage_;
}

void World::SetScroolJudge(const Vector2& scroolJudge,const Vector2& scroolMinPos,const Vector2& scroolMaxPos, bool flag)
{
	scrool_.scroolJudge = scroolJudge;
	scrool_.scroolStopMin = scroolMinPos;
	scrool_.scroolStopMax = scroolMaxPos;
	//if (!flag)
	//	InitializeInv(scroolMinPos);
	//else
	//	InitializeInv(scroolMaxPos);
}

ScroolJudge World::GetScroolJudge() {
	return scrool_;
}

void World::inv(const Matrix& mat) {
	ScroolJudge scrool = GetScroolJudge();
	//1�t���[���O�̍��W
	mPrePos = Vector2(inv_.Translation().x, inv_.Translation().y);
	//�X�N���[���X�g�b�v����
	Matrix playerMat;
	playerMat = mat;

	float clampPosX = MathHelper::Clamp(playerMat.Translation().x, scrool.scroolStopMin.x, scrool.scroolStopMax.x);
	float clampPosY = MathHelper::Clamp(playerMat.Translation().y, scrool.scroolStopMin.y, scrool.scroolStopMax.y);
	if (scrool.scroolJudge.x == 0)
		clampPosX = playerScreenPos_.x;
	if (scrool.scroolJudge.y == 0)
		clampPosY = playerScreenPos_.y;
	playerMat.Translation(Vector3(clampPosX, clampPosY, 0.0f));

	//�s���ׂ��ʒu��ݒ�(matrix��)
	resInv_ = Matrix::Invert(playerMat) *
		Matrix::CreateTranslation(Vector3(playerScreenPos_.x, playerScreenPos_.y));
	//�s���ׂ��ʒu��ݒ�
	Vector2 resPos = Vector2(resInv_.Translation().x, resInv_.Translation().y);
	Vector2 pos = Vector2(inv_.Translation().x, inv_.Translation().y);

	Spring(pos, resPos, velo,0.2f);
	//�␳���ꂽ�ړ��}�g���b�N�X���
	inv_ = Matrix::CreateTranslation(Vector3(
		pos.x*scrool.scroolJudge.x,
		pos.y*scrool.scroolJudge.y,
		0.0f));

	//1�t���[����̍��W
	mCurPos = Vector2(inv_.Translation().x, inv_.Translation().y);
	//�ړ��ʂ��v�Z
	mVelo = mPrePos - mCurPos;
	mVelo = Vector2(mVelo.x*scrool.scroolJudge.x, mVelo.y * scrool.scroolJudge.y);

}

Matrix World::InitializeInv(Vector2 position)
{
	//1�t���[���O�̍��W
	mPrePos = Vector2(inv_.Translation().x, inv_.Translation().y);
	Matrix playerMat;
	ScroolJudge scrool = GetScroolJudge();
	playerMat.Translation(Vector3(position.x, position.y, 0.0f));

	inv_ = Matrix::Invert(playerMat) *
		Matrix::CreateTranslation(Vector3(playerScreenPos_.x, playerScreenPos_.y));
	resInv_ = Matrix::Invert(playerMat) *
		Matrix::CreateTranslation(Vector3(playerScreenPos_.x, playerScreenPos_.y));

	//1�t���[����̍��W
	mCurPos = Vector2(inv_.Translation().x, inv_.Translation().y);
	//�ړ��ʂ��v�Z
	//mVelo = mPrePos - mCurPos;
	return inv_;
}

void World::SetScroolPos(const Vector2 & pos)
{
	playerMat_.Translation(Vector3(pos.x, pos.y, 0));
}

void World::Spring(Vector2 & pos, Vector2 & resPos, Vector2 & velo, float stiffness, float friction, float mass) const
{
	// �o�l�̐L�ы���v�Z
	Vector2 stretch = (pos - resPos);
	// �o�l�̗͂��v�Z
	Vector2 force = -stiffness * stretch;
	// �����x��ǉ�
	Vector2 acceleration = force / mass;
	// �ړ����x���v�Z
	velo = friction * (velo + acceleration);

	pos = pos + velo;
}


