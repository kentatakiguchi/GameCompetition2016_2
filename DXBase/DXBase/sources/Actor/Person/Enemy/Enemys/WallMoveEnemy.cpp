#include "WallMoveEnemy.h"
#include "../FloorSearchPoint.h"

WallMoveEnemy::WallMoveEnemy(
	IWorld * world,
	const Vector2 & position,
	const Vector2& direction) :
	BaseEnemy(world, position, 64.0f, direction),
	addScale_(4.0f, 4.0f)
	//result_(0)
{
	direction_ = direction;
	// �Ǒ{���I�u�W�F�N�g�̊e�X�e�[�^�X�̒ǉ�
	addWSPPosition();
	addWSPScale();
	// �Ǒ{���I�u�W�F�N�g�̒ǉ�
	createFSP();
	// �d�͂��g��Ȃ� ���� ���G
	isUseGravity_ = false;
	isInvincible_ = true;
	// �A�j���[�V�����̒ǉ�
	addTexPosition_ = Vector2::Zero;
	addAnimation();
	animation_.changeAnimation(ENEMY_WALK);
}

void WallMoveEnemy::onUpdate(float deltaTime)
{
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// �A�j���[�V�����̍X�V
	animation_.update(deltaTime);
	// ��Ԃ̍X�V
	BaseEnemy::updateState(deltaTime);
	// �Ǒ{���I�u�W�F�N�g�̈ʒu�X�V
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		enemyManager_.getWSPObj(i)->setPosition(position_);
	}
	//// �f�o�b�O�\���̂��߂̃��U���g
	//result_ = enemyManager_.eachWSPObj();
}

void WallMoveEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
	// �ǈړ��̕�����ݒ�
	enemyManager_.setIsDirection(isBlockCollideBegin_);
}

void WallMoveEnemy::onMessage(EventMessage event, void *)
{
}

void WallMoveEnemy::search()
{
	// ��ԑJ�ڂ��Ȃ�
	searchMove();
}

void WallMoveEnemy::searchMove()
{
	// ����������
	direction_ = enemyManager_.getWallDirection();
	// �ǈړ�
	position_ += direction_ * speed_ * deltaTimer_;
}

void WallMoveEnemy::addWSPPosition()
{
	// �ʒu�̒ǉ�
	auto addPos = -1;
	// 0
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 1
	fspPositionContainer_.push_back(
		Vector2(0.0f, -(scale_ / 2.0f + addScale_.y / 2.0f) + -addPos));
	// 2
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 3
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) + -addPos, 0.0f));
	// 4
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f - -addPos, 0.0f));
	// 5
	fspPositionContainer_.push_back(
		Vector2(
			-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
	// 6
	fspPositionContainer_.push_back(
		Vector2(0.0f, scale_ / 2.0f + addScale_.y / 2.0f - -addPos));
	// 7
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
}

void WallMoveEnemy::addWSPScale()
{
	auto addScale = 0;
	// 0
	fspScaleContainer_.push_back(addScale_);
	// 1
	fspScaleContainer_.push_back(Vector2(scale_ +  addScale, addScale_.y));
	// 2
	fspScaleContainer_.push_back(addScale_);
	// 3
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_ + addScale));
	// 4
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_ + addScale));
	// 5
	fspScaleContainer_.push_back(addScale_);
	// 6
	fspScaleContainer_.push_back(Vector2(scale_ + addScale, addScale_.y));
	// 7
	fspScaleContainer_.push_back(addScale_);
}

// �A�j���[�V�����̒ǉ����s���܂�
void WallMoveEnemy::addAnimation()
{
	animation_.addAnimation(
		ENEMY_WALK,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_WALLMOVEENEMY_TEX),
		texSize_, 8, 4, 1);
}
