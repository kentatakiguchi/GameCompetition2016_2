#include "WallMoveEnemy.h"
#include "../FloorSearchPoint.h"
#include "../../../../ResourceLoader/ResourceLoader.h"

WallMoveEnemy::WallMoveEnemy(IWorld * world, const Vector2 & position) :
	BaseEnemy(world, position, 64.0f),
	addScale_(4.0f, 4.0f),
	result_(0)
{
	// �Ǒ{���I�u�W�F�N�g�̊e�X�e�[�^�X�̒ǉ�
	addWSPPosition();
	addWSPScale();
	// �Ǒ{���I�u�W�F�N�g�̒ǉ�
	createFSP();

	//direction_.y = 0.0f;
	isUseGravity_ = false;
	isInvincible_ = true;

	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		isGCont.push_back(enemyManager_.getWSPObj(i)->isGround());
	}
}

void WallMoveEnemy::onUpdate(float deltaTime)
{
	//BaseEnemy::onUpdate(deltaTime);
	// �f���^�^�C���̒l��ݒ肷��
	setDeltaTime(deltaTime);
	// �G�l�~�[�}�l�[�W���[�̍X�V
	enemyManager_.update(deltaTime);
	// ��Ԃ̍X�V
	BaseEnemy::updateState(deltaTime);
	//updateState(deltaTime);
	// �{���I�u�W�F�N�g�̍X�V
	//updateSearchObjct();

	isGround_ = false;
	//enemyManager_
	for (int i = 0; i != fspScaleContainer_.size(); i++) {
		enemyManager_.getWSPObj(i)->setPosition(position_);
		isGCont[i] = enemyManager_.getWSPObj(i)->isGround();
	}
	result_ = enemyManager_.eachWSPObj();

	//position_ += world_->MoveActor();
}

//void WallMoveEnemy::onDraw() const
//{
//	auto stateChar = stateString_.c_str();
//	// �G�̕\��
//	DrawGraph(
//		position_.x - scale_ / 2.0f, position_.y - scale_ / 2.0f,
//		ResourceLoader::GetInstance().getTextureID(TextureID::ENEMY_SAMPLE_TEX), 0);
//	// �����̕\��
//	/*DrawString(
//		position_.x - scale_, position_.y - 20 - scale_,
//		stateChar, GetColor(255, 255, 255));*/
//
//	//// �f�o�b�O
//	//auto addPos = Vector2::Zero;
//	//for (int i = 0; i != fspScaleContainer_.size(); i++) {
//	//	addPos.y += 25.0f;
//	//	DrawFormatString(
//	//		25, 75 + addPos.y, GetColor(255, 255, 255),
//	//		"�{�b�N�X�ƐG��Ă��邩(%d):%d",
//	//		i,
//	//		isGCont[i]);
//	//}
//	//DrawFormatString(
//	//	25, 350, GetColor(255, 255, 255),
//	//	"�{�b�N�X�ƐG��Ă��邩�̍��v�l:%d",
//	//	result_);
//	//DrawFormatString(
//	//	25, 375, GetColor(255, 255, 255),
//	//	"�{�b�N�X�Ɉ�u�G�ꂽ��:%d",
//	//	(int)isBlockCollideBegin_);
//	//DrawFormatString(
//	//	25, 400, GetColor(255, 255, 255),
//	//	"�{�b�N�X�ɐG��Ă��邩:%d",
//	//	(int)isBlockCollideEnter_);
//
//	/*DrawFormatString(25, 25, GetColor(255, 255, 255), "body x:%d,y:%d", (int)body_.GetBox().component_.point[0].x, (int)body_.GetBox().component_.point[0].y);
//	DrawFormatString(25, 50, GetColor(255, 255, 255), "pos  x:%d,y:%d", (int)position_.x, (int)position_.y);
//	DrawFormatString(25, 75, GetColor(255, 255, 255), "�v���C���[�Ƃ̋���:%d", (int)distance_);*/
//
//	//char lengthChar = static_cast<char>(enemyManager_.getPlayerLength());
//	//DrawString(position_.x + 50, position_.y - 20, &lengthChar, GetColor(255, 255, 255));
//	body_.draw();
//}

void WallMoveEnemy::onCollide(Actor & actor)
{
	BaseEnemy::onCollide(actor);
	// �ǈړ��̕���
	enemyManager_.setIsDirection(isBlockCollideBegin_);
}

void WallMoveEnemy::onMessage(EventMessage event, void *)
{
}

void WallMoveEnemy::search()
{
	searchMove();
}

void WallMoveEnemy::searchMove()
{
	/*auto direction = direction_;
	direction.y = 0.0f;*/
	/*if (enemyManager_.wallMove().x != Vector2::Zero.x &&
		enemyManager_.wallMove().y != Vector2::Zero.y)
		direction = enemyManager_.wallMove();*/

	//direction_ = enemyManager_.wallMove();
	//position_ += enemyManager_.wallMove() * speed_;
	if (InputMgr::GetInstance().IsKeyOn(KeyCode::Z))
		return;
	position_ += enemyManager_.getWallDirection() * speed_ * deltaTimer_;
}

void WallMoveEnemy::addWSPPosition()
{
	// �ʒu�̒ǉ�
	// auto addPos = 5;
	auto addPos = 1;
	// 0
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 1
	/*fspPositionContainer_.push_back(
		Vector2(0.0f, -(scale_ / 2.0f + addScale_.y / 2.0f)));*/
	fspPositionContainer_.push_back(
		Vector2(0.0f, -(scale_ / 2.0f + addScale_.y / 2.0f) + addPos));
	// 2
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			-(scale_ / 2.0f + addScale_.y / 2.0f) - addPos));
	// 3
	/*fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f), 0.0f));*/
	fspPositionContainer_.push_back(
		Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) + addPos, 0.0f));
	// 4
	/*fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f, 0.0f));*/
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f - addPos, 0.0f));
	// 5
	fspPositionContainer_.push_back(
		Vector2(
			-(scale_ / 2.0f + addScale_.x / 2.0f) - addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
	// 6
	/*fspPositionContainer_.push_back(
		Vector2(0.0f, scale_ / 2.0f + addScale_.y / 2.0f));*/
	fspPositionContainer_.push_back(
		Vector2(0.0f, scale_ / 2.0f + addScale_.y / 2.0f -addPos));
	// 7
	fspPositionContainer_.push_back(
		Vector2(scale_ / 2.0f + addScale_.x / 2.0f + addPos,
			scale_ / 2.0f + addScale_.y / 2.0f + addPos));
	//// 0
	//fspPositionContainer_.push_back(
	//	Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) - add,
	//		-(scale_ / 2.0f + addScale_.y / 2.0f) - add));
	//// 1
	//fspPositionContainer_.push_back(
	//	Vector2(0.0f, -(scale_ / 2.0f + addScale_.y / 2.0f) - add));
	//// 2
	//fspPositionContainer_.push_back(
	//	Vector2(scale_ / 2.0f + addScale_.x / 2.0f + add,
	//		-(scale_ / 2.0f +addScale_.y / 2.0f) -add));
	//// 3
	//fspPositionContainer_.push_back(
	//	Vector2(-(scale_ / 2.0f + addScale_.x / 2.0f) -add, 0.0f));
	//// 4
	//fspPositionContainer_.push_back(
	//	Vector2(scale_ / 2.0f + addScale_.x / 2.0f +add, 0.0f));
	//// 5
	//fspPositionContainer_.push_back(
	//	Vector2(
	//		-(scale_ / 2.0f + addScale_.x / 2.0f) - add,
	//		scale_ / 2.0f + addScale_.y / 2.0f +add));
	//// 6
	//fspPositionContainer_.push_back(
	//	Vector2(0.0f, scale_ / 2.0f + addScale_.y / 2.0f +add));
	//// 7
	//fspPositionContainer_.push_back(
	//	Vector2(scale_ / 2.0f + addScale_.x / 2.0f +add,
	//		scale_ / 2.0f + addScale_.y / 2.0f +add));
}

void WallMoveEnemy::addWSPScale()
{
	// 0
	fspScaleContainer_.push_back(addScale_);
	// 1
	fspScaleContainer_.push_back(Vector2(scale_, addScale_.y));
	// 2
	fspScaleContainer_.push_back(addScale_);
	// 3
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_));
	// 4
	fspScaleContainer_.push_back(Vector2(addScale_.x, scale_));
	// 5
	fspScaleContainer_.push_back(addScale_);
	// 6
	fspScaleContainer_.push_back(Vector2(scale_, addScale_.y));
	// 7
	fspScaleContainer_.push_back(addScale_);
}
