#include "WallMoveEnemy.h"
#include "../FloorSearchPoint.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

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

	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		isGCont.push_back(enemyManager_.getWSPObj(i)->isGround());
	}
}

void WallMoveEnemy::onUpdate(float deltaTime)
{
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// ��Ԃ̍X�V
	BaseEnemy::updateState(deltaTime);
	// �Ǒ{���I�u�W�F�N�g�̈ʒu�X�V
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		enemyManager_.getWSPObj(i)->setPosition(position_);
		// �ǂɓ������Ă��邩�̃R���e�i�ɒǉ�
		isGCont[i] = enemyManager_.getWSPObj(i)->isGround();
	}
	//// �f�o�b�O�\���̂��߂̃��U���g
	//result_ = enemyManager_.eachWSPObj();
}

void WallMoveEnemy::onDraw() const
{
	auto vec3Pos = Vector3(position_.x, position_.y, 0.0f);
	vec3Pos = vec3Pos * inv_;
	// �G�̕\��
	DrawGraph(
		vec3Pos.x - scale_ / 2.0f, vec3Pos.y - scale_ / 2.0f,
		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
	//// �f�o�b�O
	/*auto addPos = Vector2::Zero;
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		addPos.y += 50.0f;
		DrawFormatStringToHandle(50, 50 + addPos.y, GetColor(255, 255, 255),
			handle_, "�{�b�N�X�ƐG��Ă��邩(%d):%d",
			i, isGCont[i]);
	}*/
	//DrawFormatString(
	//	25, 350, GetColor(255, 255, 255),
	//	"�{�b�N�X�ƐG��Ă��邩�̍��v�l:%d",
	//	result_);
	//DrawFormatString(
	//	25, 375, GetColor(255, 255, 255),
	//	"�{�b�N�X�Ɉ�u�G�ꂽ��:%d",
	//	(int)isBlockCollideBegin_);
	//DrawFormatString(
	//	25, 400, GetColor(255, 255, 255),
	//	"�{�b�N�X�ɐG��Ă��邩:%d",
	//	(int)isBlockCollideEnter_);

	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
	DrawFormatString(25, 75, GetColor(255, 255, 255), "�v���C���[�Ƃ̋���:%d", (int)distance_);*/

	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
	body_.draw(inv_);
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
